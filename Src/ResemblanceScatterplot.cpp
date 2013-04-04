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

#include "ResemblanceScatterplot.hpp"

#include "PlotPicker.hpp"
#include "Log.hpp"
#include "DetachedPlotDlg.hpp"
#include "Properties.hpp"
#include "LinearRegression.hpp"

ResemblanceScatterplot::ResemblanceScatterplot(QwtPlot* plot): m_plot(plot), m_plotPicker(new PlotPicker(plot)), m_bShowBestFitLine(true)
{
	// initialize plot
	m_plot->setCanvasBackground(Qt::white);
	m_plot->setCanvasLineWidth(0);
	m_plot->axisWidget(QwtPlot::xBottom)->setAutoFillBackground(true);
	m_plot->axisWidget(QwtPlot::yLeft)->setAutoFillBackground(true);
	m_plot->axisWidget(QwtPlot::xBottom)->setPalette(Qt::white);
	m_plot->axisWidget(QwtPlot::yLeft)->setPalette(Qt::white);

	// connect signals to slots
	m_plot->setContextMenuPolicy(Qt::CustomContextMenu);
	QObject::connect(m_plot, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(PopupMenu(const QPoint &)));
}

void ResemblanceScatterplot::Plot(const Matrix& xMatrix, const Matrix& yMatrix, const QStringList& sampleNames,
																		const QString& xMeasureLabel, const QString& yMeasureLabel,
																		uint size, bool bShowBestFitLine)
{
	m_xMatrix = xMatrix;
	m_yMatrix = yMatrix;
	m_sampleNames = sampleNames;
	m_xMeasureLabel = xMeasureLabel;
	m_yMeasureLabel = yMeasureLabel;
	m_size = size;
	m_bShowBestFitLine = bShowBestFitLine;

	Plot(m_plot);
}

void ResemblanceScatterplot::Plot(QwtPlot* plot)
{
	if(m_xMatrix.size() == 0 || m_yMatrix.size() == 0)
		return;
	
	plot->detachItems();

	QwtSymbol* symbol = new QwtSymbol(QwtSymbol::Ellipse, QBrush(QColor(127,127,127)), QPen(Qt::black),	QSize(m_size,m_size));

	double minX = INT_MAX;
	double maxX = -INT_MAX;
	double minY = INT_MAX;
	double maxY = -INT_MAX;
	QList<double> x;
	QList<double> y;
	for(int r = 0; r < m_xMatrix.size(); ++r)
	{
		for(int c = r+1; c < m_xMatrix[0].size(); ++c)
		{
			QwtPlotMarker* pt = new QwtPlotMarker();
			double distX = m_xMatrix.at(r).at(c);
			double distY = m_yMatrix.at(r).at(c);

			pt->setRenderHint(QwtPlotItem::RenderAntialiased);
			pt->setValue(distX, distY);
			pt->setSymbol(symbol);
			pt->setTitle(m_sampleNames.at(r) + " : " + m_sampleNames.at(c));
			pt->attach(plot);

			if(distX > maxX)
				maxX = distX;
			if(distX < minX)
				minX = distX;

			if(distY > maxY)
				maxY = distY;
			if(distY < minY)
				minY = distY;

			x.append(distX);
			y.append(distY);
		}
	}

	double xLengthOffset = 0.05*(maxX - minX);
	double yLengthOffset = 0.05*(maxY - minY);
	plot->setAxisScale(QwtPlot::xBottom, 0, 1.0);
	plot->setAxisScale(QwtPlot::xTop, 0, 1.0);
	plot->setAxisScale(QwtPlot::yLeft, 0, 1.0);
	plot->setAxisScale(QwtPlot::yRight, 0, 1.0);

	// *** Set axes labels
	QFont font = plot->axisFont(QwtPlot::xBottom);
	QwtText xAxisLabel;	
	xAxisLabel.setFont(font);
	xAxisLabel.setText(m_xMeasureLabel);
	plot->setAxisTitle(QwtPlot::xBottom, xAxisLabel);

	QwtText yAxisLabel;	
	yAxisLabel.setFont(font);
	yAxisLabel.setText(m_yMeasureLabel);
	plot->setAxisTitle(QwtPlot::yLeft, yAxisLabel);

	// *** Perform linear regression and report results
	LinearRegression linearRegression;
	LinearRegression::RESULTS results;
	linearRegression.LeastSquaresEstimate(x, y, results);

	QwtPlotMarker* rSqrdLabel = new QwtPlotMarker();
	QString label = "R" + QString(char(178)) + " = " + QString::number(results.cod, 'g', 3) + "\n";
	label += "y = " + QString::number(results.slope, 'g', 3) + "x + " + QString::number(results.offset, 'g', 3);
	rSqrdLabel->setLabel(label);
	rSqrdLabel->setLabelAlignment(Qt::AlignRight|Qt::AlignVCenter);
	rSqrdLabel->setValue(0.02, 0.96);

	rSqrdLabel->attach(plot);

	// *** Plot best-fit line
	QwtPlotCurve* bestFitLine = new QwtPlotCurve();
	bestFitLine->setStyle(QwtPlotCurve::Lines);
	
	QVector<QPointF> data;
	data << QPointF(0.0, results.offset) << QPointF(1.0, results.slope + results.offset);
	bestFitLine->setSamples(data);

	bestFitLine->setVisible(m_bShowBestFitLine);
	bestFitLine->attach(plot);

	plot->replot();
}

void ResemblanceScatterplot::UpdateMarkers(int size)
{
	m_size = size;

	const QwtPlotItemList& itmList = m_plot->itemList();
	for(QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); ++it)
	{
		if((*it)->rtti() == QwtPlotMarker::Rtti_PlotMarker)
		{
			QwtPlotMarker* pt = (QwtPlotMarker*)(*it);

			if(pt->label().text() == "")	// make sure we have a marker and not a label
			{
				QwtSymbol* symbol = new QwtSymbol(QwtSymbol::Ellipse, QBrush(QColor(127,127,127)), QPen(Qt::black),	QSize(m_size,m_size));
				pt->setSymbol(symbol);
			}
		}
		else if((*it)->rtti() == QwtPlotItem::Rtti_PlotCurve)
		{
			QwtPlotCurve* curve = (QwtPlotCurve*)(*it);

			curve->setVisible(m_bShowBestFitLine);
		}
	}

	m_plot->replot();
}


void ResemblanceScatterplot::PopupMenu(const QPoint & pos)
{
	if(sender()->isWidgetType())
	{
		QMenu menu;
		QAction *action= menu.addAction("Send to detached window...");
		QObject::connect(action, SIGNAL(triggered()), this, SLOT(SendToDetachedWindow()));

		menu.exec(m_plot->mapToGlobal(pos));
	}
}

void ResemblanceScatterplot::SendToDetachedWindow()
{
	DetachedPlotDlg* dlg = new DetachedPlotDlg(false);
	dlg->SetBackgroundColor(Properties::Inst().GetBackgroundColor());
	Clone(dlg->GetPlot());
	dlg->show();
}

void ResemblanceScatterplot::Clone(QwtPlot* plot)
{
	plot->axisWidget(QwtPlot::xBottom)->setAutoFillBackground(true);
	plot->axisWidget(QwtPlot::yLeft)->setAutoFillBackground(true);
	plot->axisWidget(QwtPlot::xBottom)->setPalette(Properties::Inst().GetBackgroundColor());
	plot->axisWidget(QwtPlot::yLeft)->setPalette(Properties::Inst().GetBackgroundColor());
	plot->setCanvasBackground(Properties::Inst().GetBackgroundColor());
	plot->setCanvasLineWidth(0);

	Plot(plot);
}

void ResemblanceScatterplot::SetBackgroundColor(const QColor& color)
{
	m_plot->axisWidget(QwtPlot::xBottom)->setPalette(color);
	m_plot->axisWidget(QwtPlot::yLeft)->setPalette(color);

	m_plot->setCanvasBackground(color);

	m_plot->replot();
}