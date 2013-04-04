//=======================================================================
// Author: Donovan Parks
//
// Copyright 2009 Donovan Parks
//
// This file is part of Chameleon.
//
// Chameleon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Chameleon is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Chameleon. If not, see <http://www.gnu.org/licenses/>.
//=======================================================================

#include "stdafx.h"

#include "OrdinationPlots.hpp"

#include "Log.hpp"

#include "OrdinationPlot.hpp"
#include "OrdinationPoint.hpp"
#include "OrdinationSelection.hpp"

#include "PlotPicker.hpp"

#include "Legends.hpp"
#include "Samples.hpp"

#include "DetachedPlotDlg.hpp"

#include "Properties.hpp"

OrdinationPlots::OrdinationPlots(const QList<OrdinationPlot*>& plots, LegendsPtr legends)
	: m_plots(plots), m_legends(legends), m_bShowSampleNames(false), m_bApplySelectionTransparency(false)
{
	// initialize plots
	for(int i = 0; i < m_plots.size(); ++i)
	{
		m_plots.at(i)->setCanvasBackground(Qt::white);
		m_plots.at(i)->setCanvasLineWidth(0);
		m_plots.at(i)->axisWidget(QwtPlot::xBottom)->setAutoFillBackground(true);
		m_plots.at(i)->axisWidget(QwtPlot::yLeft)->setAutoFillBackground(true);
		m_plots.at(i)->axisWidget(QwtPlot::xBottom)->setPalette(Qt::white);
		m_plots.at(i)->axisWidget(QwtPlot::yLeft)->setPalette(Qt::white);

		QFont font = plots.at(0)->axisFont(QwtPlot::xBottom);
		QwtText xAxisLabel;
		xAxisLabel.setFont(font);
		if(i == 0 || i == 2)
			xAxisLabel.setText("PC1 (% variation)");
		else if(i == 1)
			xAxisLabel.setText("PC3 (% variation)");
		else
			xAxisLabel.setText("Principal component");
		
		m_plots.at(i)->setAxisTitle(QwtPlot::xBottom, xAxisLabel);

		QwtText yAxisLabel;
		yAxisLabel.setFont(font);
		if(i == 0 || i == 1)
			yAxisLabel.setText("PC2 (% variation)");
		else if(i == 2)
			yAxisLabel.setText("PC3 (% variation)");
		else
			yAxisLabel.setText("Explained variation");
		m_plots.at(i)->setAxisTitle(QwtPlot::yLeft, yAxisLabel);

		// connect signals to slots
		m_plots.at(i)->setContextMenuPolicy(Qt::CustomContextMenu);
		QObject::connect(m_plots.at(i), SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(PopupMenu(const QPoint &)));
	}

	m_plots.at(3)->canvas()->setCursor(Qt::ArrowCursor);

	QObject::connect(m_plots.at(0), SIGNAL(Resized()), this, SLOT(SetAxes()));

	m_axes.resize(3);
}

void OrdinationPlots::SetSamples(SamplesPtr samples)
{
	m_samples = samples;

	for(uint i = 0; i < 3; ++i)
	{
		OrdinationSelection* ordinationSelection = new OrdinationSelection(m_plots.at(i)->canvas(), m_samples);
		QObject::connect(ordinationSelection, SIGNAL(SelectionSetChanged()), this, SLOT(UpdateMarkers()));
	}
}

void OrdinationPlots::SetData(const Matrix& embedding, const QVector<double>& variance, const QVector<double>& sumVariance, Matrix neighbourhoodGraph) 
{ 
	m_embedding = embedding;
	m_variance = variance;
	m_sumVariance = sumVariance;
	m_neighbourhoodGraph = neighbourhoodGraph;

	m_xAxis.clear();
	for(int i = 0; i < m_variance.size(); ++i)
		m_xAxis.append(i+1);
}

void OrdinationPlots::Plot()
{
	if(m_embedding.size() == 0)
		return;

	// ** Plot first 3 principal components and scree plot
	Plot(m_plots.at(0), 0, 1);
	Plot(m_plots.at(1), 2, 1);
	Plot(m_plots.at(2), 0, 2);
	ScreePlot(m_plots.at(3));

	// ** Get extents of all axes
	for(int i = 0; i < qMin<int>(3, m_embedding.at(0).size()); ++i)
	{
		float minPt = (float)INT_MAX;
		float maxPt = (float)-INT_MAX;
		for(int ptIndex = 0; ptIndex < m_embedding.size(); ++ptIndex)
		{
			float pt = m_embedding.at(ptIndex).at(i);
			
			if(pt > maxPt)
				maxPt = pt;
			if(pt < minPt)
				minPt = pt;
		}

		float lengthOffset = 0.05*(maxPt - minPt);

		m_axes[i].setMinValue(minPt-lengthOffset);
		m_axes[i].setMaxValue(maxPt+lengthOffset);
	}

	// ** Set axes of all plots
	SetAxes();
}

void OrdinationPlots::Plot(QwtPlot* plot, uint component1, uint component2)
{
	if(m_embedding.size() == 0)
		return;
	
	plot->detachItems();	

	QSet<uint> activeSampleIds = m_samples->GetActiveSampleIds();
	QSet<uint> selectedSampleIds = m_samples->GetSelectedSampleIds();

	if(m_embedding.size() <= (int)component1 
			|| m_embedding.size() <= (int)component2
			|| m_embedding.size() != activeSampleIds.size())
	{
		// either there is only 2 samples so some plots are invalid,
		// or the active set is in the process of being modified so
		// we should hold off regenerating this plot
		return;
	}

	// plot ordination points
	uint ptIndex = 0;
	QVector<QPointF> embeddedPts;
	foreach(uint sampleId, activeSampleIds)
	{
		QwtSymbol::Style shape = m_samples->GetSample(sampleId).GetShape();
		QColor color = m_samples->GetSample(sampleId).GetColor();
		uint size = m_samples->GetSample(sampleId).GetSize();

		QString label = "";
		if(m_bShowSampleNames)
			label = m_samples->GetSample(sampleId).GetName();

		OrdinationPoint* pt = new OrdinationPoint(sampleId);
		double x = m_embedding.at(ptIndex).at(component1);
		double y = m_embedding.at(ptIndex).at(component2);
		pt->SetMarker(x, y, label, shape, color, size, 
											m_samples->GetSample(sampleId).IsVisible(),
											selectedSampleIds.contains(sampleId), 
											m_samples->GetSample(sampleId).IsGuaranteedVisible());
		pt->attach(plot);

		if(sampleId == 0 || sampleId == 1)
			embeddedPts.push_back(QPointF(x,y));
		ptIndex++;
	}

	// draw origin lines
	for(int i = 0; i < m_plots.size()-1; ++i)
	{
		QwtPlotMarker* mY = new QwtPlotMarker();
		mY->setLineStyle(QwtPlotMarker::HLine);
		mY->setLinePen(QPen(Qt::gray, 0, Qt::DashLine));
		mY->setYValue(0.0);	
		mY->setZ(-1.0);
		mY->attach(plot);

		QwtPlotMarker* mX = new QwtPlotMarker();
		mX->setLineStyle(QwtPlotMarker::VLine);
		mX->setLinePen(QPen(Qt::gray, 0, Qt::DashLine));
		mX->setXValue(0);
		mX->setZ(-1.0);
		mX->attach(plot);
	}

	// draw neighbourhood graph
	QList<uint> activeSampleIdList = activeSampleIds.toList();
	for(int i = 0; i < m_neighbourhoodGraph.size(); ++i)
	{
		if(!m_samples->GetSample(activeSampleIdList.at(i)).IsVisible())
			continue;

		for(int j = 0; j < i; ++j)
		{
			if(i == j)
				continue;

			if(!m_samples->GetSample(activeSampleIdList.at(j)).IsVisible())
				continue;

			if(m_neighbourhoodGraph[i][j] < INFINITE)
			{
				QVector<double> x;
				QVector<double> y;
				x.append(m_embedding.at(i).at(component1));
				y.append(m_embedding.at(i).at(component2));
				x.append(m_embedding.at(j).at(component1));
				y.append(m_embedding.at(j).at(component2));

				QwtPlotCurve* line = new QwtPlotCurve();
				line->setSamples(x, y);
				line->setStyle(QwtPlotCurve::Lines);
				line->setRenderHint(QwtPlotCurve::RenderAntialiased, true);
				line->setPen(QPen(QColor(216, 216, 216)));
				line->setZ(-1.0);
				line->attach(plot);
			}
		}
	}

	// set axes labels
	if(m_variance.size() != 0)
	{
		QFont font = plot->axisFont(QwtPlot::xBottom);
		QwtText xAxisLabel;	
		xAxisLabel.setFont(font);
		if(component1 == 0)
			xAxisLabel.setText(QString("PC1 (%1% variation)").arg(m_variance.at(0)*100, 0, 'g', 3));
		else if(component1 == 2)
			xAxisLabel.setText(QString("PC3 (%1% variation)").arg(m_variance.at(2)*100, 0, 'g', 3));

		plot->setAxisTitle(QwtPlot::xBottom, xAxisLabel);

		QwtText yAxisLabel;	
		yAxisLabel.setFont(font);
		if(component2 == 1)
			yAxisLabel.setText(QString("PC2 (%1% variation)").arg(m_variance.at(1)*100, 0, 'g', 3));
		else if(component2 == 2)
			yAxisLabel.setText(QString("PC3 (%1% variation)").arg(m_variance.at(2)*100, 0, 'g', 3));

		plot->setAxisTitle(QwtPlot::yLeft, yAxisLabel);
	}
	else
	{
			QFont font = plot->axisFont(QwtPlot::xBottom);
		QwtText xAxisLabel;	
		xAxisLabel.setFont(font);
		if(component1 == 0)
			xAxisLabel.setText("nmds 1");
		else if(component1 == 2)
			xAxisLabel.setText("nmds 3");

		plot->setAxisTitle(QwtPlot::xBottom, xAxisLabel);

		QwtText yAxisLabel;	
		yAxisLabel.setFont(font);
		if(component2 == 1)
			yAxisLabel.setText("nmds 2");
		else if(component2 == 2)
			yAxisLabel.setText("nmds 3");

		plot->setAxisTitle(QwtPlot::yLeft, yAxisLabel);	
	}
}

void OrdinationPlots::SetAxes()
{
	QSize canvasSize = m_plots.at(0)->canvas()->contentsRect().size();

	// calculate length per pixel that will allow data to be visible in all plots
	float plot1X = m_axes.at(0).width() / canvasSize.width();
	float plot1Y = m_axes.at(1).width() / canvasSize.height();
	float plot2X = m_axes.at(2).width() / canvasSize.width();
	float plot3Y = m_axes.at(2).width() / canvasSize.height();

	float lengthPerPixel = qMax<float>(plot1X, plot1Y);
	lengthPerPixel = qMax<float>(lengthPerPixel, plot2X);
	lengthPerPixel = qMax<float>(lengthPerPixel, plot3Y);

	// set all axes to have the same length per pixel
	float lengthAdjust = 0.5 * (lengthPerPixel*canvasSize.width() - m_axes.at(0).width());
	m_plots[0]->setAxisScale(QwtPlot::xBottom, m_axes.at(0).minValue() - lengthAdjust, m_axes.at(0).maxValue() + lengthAdjust);

	lengthAdjust = 0.5 * (lengthPerPixel*canvasSize.height() - m_axes.at(1).width());
	m_plots[0]->setAxisScale(QwtPlot::yLeft, m_axes.at(1).minValue() - lengthAdjust, m_axes.at(1).maxValue() + lengthAdjust);

	lengthAdjust = 0.5 * (lengthPerPixel*canvasSize.width() - m_axes.at(2).width());
	m_plots[1]->setAxisScale(QwtPlot::xBottom, m_axes.at(2).minValue() - lengthAdjust, m_axes.at(2).maxValue() + lengthAdjust);

	lengthAdjust = 0.5 * (lengthPerPixel*canvasSize.height() - m_axes.at(1).width());
	m_plots[1]->setAxisScale(QwtPlot::yLeft, m_axes.at(1).minValue() - lengthAdjust, m_axes.at(1).maxValue() + lengthAdjust);

	lengthAdjust = 0.5 * (lengthPerPixel*canvasSize.width() - m_axes.at(0).width());
	m_plots[2]->setAxisScale(QwtPlot::xBottom, m_axes.at(0).minValue() - lengthAdjust, m_axes.at(0).maxValue() + lengthAdjust);

	lengthAdjust = 0.5 * (lengthPerPixel*canvasSize.height() - m_axes.at(2).width());
	m_plots[2]->setAxisScale(QwtPlot::yLeft, m_axes.at(2).minValue() - lengthAdjust, m_axes.at(2).maxValue() + lengthAdjust);

	for(uint i = 0; i < 3; ++i)
		m_plots[i]->replot();
}

void OrdinationPlots::UpdateMarkers(const QVector<QPointF>& selectedPts)
{
	UpdateMarkers();
}

void OrdinationPlots::UpdateMarkers()
{
	if(m_embedding.size() == 0)
		return;

	UpdateMarkers(m_plots.at(0));
	UpdateMarkers(m_plots.at(1));
	UpdateMarkers(m_plots.at(2));
}

void OrdinationPlots::UpdateMarkers(QwtPlot* plot)
{
	QSet<uint> selectedSampleIds = m_samples->GetSelectedSampleIds();

	const QwtPlotItemList& itmList = plot->itemList();
	QList<OrdinationPoint*> ordinationPts;
	for(QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); ++it)
	{
		if((*it)->rtti() == OrdinationPoint::Rtti_OrdinationPoint)
		{
			OrdinationPoint* pt = (OrdinationPoint*)(*it);
			ordinationPts.append(pt);
		}
	}

	foreach(OrdinationPoint* pt, ordinationPts)
	{
		uint sampleId = pt->GetSampleId();

		QwtSymbol::Style shape = m_samples->GetSample(sampleId).GetShape();
		QColor color = m_samples->GetSample(sampleId).GetColor();
		uint size = m_samples->GetSample(sampleId).GetSize();

		QString label = "";
		if(m_bShowSampleNames)
			label = m_samples->GetSample(sampleId).GetName();

		if(m_bApplySelectionTransparency && selectedSampleIds.size() > 0)
		{
			// make non-selected items more transparent
			if(!selectedSampleIds.contains(sampleId))
				color.setAlpha(Properties::Inst().GetSelectionOpacity());
		}

		pt->SetVisualProperties(label, shape, color, size, 
															m_samples->GetSample(sampleId).IsVisible(),
															selectedSampleIds.contains(sampleId), 
															m_samples->GetSample(sampleId).IsGuaranteedVisible());
	}

	plot->replot();
}

void OrdinationPlots::ScreePlot(QwtPlot* plot)
{
	if(m_embedding.size() == 0 || m_variance.size() == 0)
	{
		plot->setVisible(false);
		return;
	}

	plot->detachItems();
	plot->setVisible(true);

	// Vertical lines at each PC
	for(int i = 0; i < m_embedding.size(); ++i)
	{
		QwtPlotMarker *mX = new QwtPlotMarker();
    mX->setLineStyle(QwtPlotMarker::VLine);
    mX->setLinePen(QPen(Qt::gray, 0, Qt::DashLine));
    mX->setXValue(i+1);
		mX->setZ(-1.0);
    mX->attach(plot);
	}

	// Variance of each PC
	QwtPlotCurve* variancePlot = new QwtPlotCurve("Variance");
  variancePlot->setRenderHint(QwtPlotItem::RenderAntialiased);
	variancePlot->setStyle(QwtPlotCurve::Lines);
	variancePlot->setPen(QPen(Qt::black));
	variancePlot->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, QBrush(QColor(192, 192, 192)), QPen(Qt::black), QSize(10,10)));
	variancePlot->setSamples(m_xAxis, m_variance);
  variancePlot->attach(plot);

	// Accumulated variance of PCs 
	QwtPlotCurve* sumVariancePlot = new QwtPlotCurve("Total variance");
  sumVariancePlot->setRenderHint(QwtPlotItem::RenderAntialiased);
	sumVariancePlot->setStyle(QwtPlotCurve::Lines);
	sumVariancePlot->setPen(QPen(Qt::black));
	sumVariancePlot->setSymbol(new QwtSymbol(QwtSymbol::Ellipse, QBrush(QColor(64,64,64)), QPen(Qt::black), QSize(10,10)));
	sumVariancePlot->setSamples(m_xAxis, m_sumVariance);
  sumVariancePlot->attach(plot);

	// *** Set axes labels
	QFont font = plot->axisFont(QwtPlot::xBottom);
	QwtText xAxisLabel;	
	xAxisLabel.setFont(font);
	xAxisLabel.setText("Principal component");		
	plot->setAxisTitle(QwtPlot::xBottom, xAxisLabel);

	QwtText yAxisLabel;
	yAxisLabel.setFont(font);
	yAxisLabel.setText("Explained variation");
	plot->setAxisTitle(QwtPlot::yLeft, yAxisLabel);

	plot->replot();
}

void OrdinationPlots::PopupMenu(const QPoint & pos)
{
	if(sender()->isWidgetType())
	{
		QwtPlot* plot = (QwtPlot*)sender();

		uint plotIndex;
		for(int i = 0; i < m_plots.size(); ++i)
		{
			if(plot == m_plots.at(i))
			{
				plotIndex = i;
				break;
			}
		}

		QMenu menu;
		QAction *action= menu.addAction("Send to detached window...");
		action->setData(QVariant(plotIndex));
		QObject::connect(action, SIGNAL(triggered()), this, SLOT(SendToDetachedWindow()));

		menu.exec(plot->mapToGlobal(pos));
	}
}

void OrdinationPlots::SendToDetachedWindow()
{
	QAction* plotSender = (QAction*)sender();

	uint plotIndex = plotSender->data().toInt();

	DetachedPlotDlg* dlg = new DetachedPlotDlg(plotIndex != 3);
	dlg->SetBackgroundColor(Properties::Inst().GetBackgroundColor());
	Clone(dlg->GetPlot(), plotIndex);
	dlg->show();
}

void OrdinationPlots::Clone(QwtPlot* plot, uint plotIndex)
{
	plot->axisWidget(QwtPlot::xBottom)->setAutoFillBackground(true);
	plot->axisWidget(QwtPlot::yLeft)->setAutoFillBackground(true);
	plot->axisWidget(QwtPlot::xBottom)->setPalette(Properties::Inst().GetBackgroundColor());
	plot->axisWidget(QwtPlot::yLeft)->setPalette(Properties::Inst().GetBackgroundColor());
	plot->setCanvasBackground(Properties::Inst().GetBackgroundColor());
	plot->setCanvasLineWidth(0);

	if(plotIndex == 0)
	{
		Plot(plot, 0, 1);
		plot->setAxisScaleDiv(QwtPlot::xBottom, *m_plots.at(0)->axisScaleDiv(QwtPlot::xBottom));
		plot->setAxisScaleDiv(QwtPlot::yLeft, *m_plots.at(0)->axisScaleDiv(QwtPlot::yLeft));
	}
	else if(plotIndex == 1)
	{
		Plot(plot, 2 ,1);
		plot->setAxisScaleDiv(QwtPlot::xBottom, *m_plots.at(1)->axisScaleDiv(QwtPlot::xBottom));
		plot->setAxisScaleDiv(QwtPlot::yLeft, *m_plots.at(1)->axisScaleDiv(QwtPlot::yLeft));
	}
	else if(plotIndex == 2)
	{
		Plot(plot, 0, 2);
		plot->setAxisScaleDiv(QwtPlot::xBottom, *m_plots.at(2)->axisScaleDiv(QwtPlot::xBottom));
		plot->setAxisScaleDiv(QwtPlot::yLeft, *m_plots.at(2)->axisScaleDiv(QwtPlot::yLeft));
	}
	else
		ScreePlot(plot);
}

void OrdinationPlots::SetBackgroundColor(const QColor& color)
{
	for(int i = 0; i < m_plots.size(); ++i)
	{
		m_plots.at(i)->axisWidget(QwtPlot::xBottom)->setPalette(color);
		m_plots.at(i)->axisWidget(QwtPlot::yLeft)->setPalette(color);

		m_plots.at(i)->setCanvasBackground(color);

		m_plots.at(i)->replot();
	}
}