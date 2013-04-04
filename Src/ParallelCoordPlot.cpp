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

#include "ParallelCoordPlot.hpp"
#include "Legends.hpp"

#include "Samples.hpp"

#include "DetachedPlotDlg.hpp"
#include "ParallelCoordCurve.hpp"
#include "ParallelCoordSelection.hpp"
#include "Properties.hpp"


ParallelCoordPlot::ParallelCoordPlot(QwtPlot* plot, LegendsPtr legends)
	: m_plot(plot), m_legends(legends), m_bShowCurves(true), m_bFittedCurves(true), 
		m_bShowVariance(true), m_dimToDisplay(8), m_bApplySelectionTransparency(true)
{	
	m_plot->setCanvasBackground(Qt::white);
	m_plot->setCanvasLineWidth(0);
	m_plot->axisWidget(QwtPlot::xBottom)->setAutoFillBackground(true);
	m_plot->axisWidget(QwtPlot::yLeft)->setAutoFillBackground(true);
	m_plot->axisWidget(QwtPlot::xBottom)->setPalette(Qt::white);
	m_plot->axisWidget(QwtPlot::yLeft)->setPalette(Qt::white);
	m_plot->axisAutoScale(QwtPlot::xBottom);
	m_plot->axisAutoScale(QwtPlot::yLeft);
	m_plot->canvas()->setCursor(Qt::CrossCursor);

	// connect signals to slots
	plot->setContextMenuPolicy(Qt::CustomContextMenu);
	QObject::connect(plot, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(PopupMenu(const QPoint &)));
}

void ParallelCoordPlot::SetSamples(SamplesPtr samples)
{
	m_samples = samples;
	ParallelCoordSelection* m_parallelCoordSelection = new ParallelCoordSelection(m_plot->canvas(), m_samples);
	QObject::connect(m_parallelCoordSelection, SIGNAL(SelectionSetChanged()), this, SLOT(UpdateMarkers()));
}

void ParallelCoordPlot::SetData(const Matrix& embedding, const QVector<double>& variance)
{
	m_embedding = embedding;
	m_variance = variance;
}

void ParallelCoordPlot::PopupMenu(const QPoint & pos)
{
	QMenu menu;
  QAction *action= menu.addAction("Send to detached window...");
	QObject::connect(action, SIGNAL(triggered()), this, SLOT(SendToDetachedWindow()));

  menu.exec(m_plot->mapToGlobal(pos));
}

void ParallelCoordPlot::Plot()
{
	Plot(m_plot);
}

void ParallelCoordPlot::Plot(QwtPlot* plot)
{
	if(m_embedding.size() == 0)
		return;

	plot->detachItems();	

	// plot vertical line at each principal component
	for(int i = 0; i < m_embedding.at(0).size() && i < (int)m_dimToDisplay; ++i)
	{
		QwtPlotMarker *vertLine = new QwtPlotMarker();
		if(m_bShowVariance && i < m_variance.size())
		{
			vertLine->setLabel(QwtText(QString("%1%").arg(m_variance.at(i)*100, 0, 'g', 3)));
			vertLine->setLabelAlignment(Qt::AlignRight | Qt::AlignTop);
		}

    vertLine->setLineStyle(QwtPlotMarker::VLine);
    vertLine->setLinePen(QPen(Qt::gray, 0, Qt::DashLine));
    vertLine->setXValue(i+1);
		vertLine->setZ(-1);
    vertLine->attach(plot);
	}

	// plot data
	QSet<uint> activeSampleIds = m_samples->GetActiveSampleIds();

	if(activeSampleIds.size() != m_embedding.size())
	{
		// the active set is in the process of being modified so
		// we should hold off regenerating this plot
		return;
	}

	QSet<uint> selectedSampleIds = m_samples->GetSelectedSampleIds();

	uint ptIndex = 0;
	foreach(uint sampleId, activeSampleIds)
	{
		QwtSymbol::Style shape = m_samples->GetSample(sampleId).GetShape();
		uint size = m_samples->GetSample(sampleId).GetSize();

		QColor color = m_samples->GetSample(sampleId).GetColor();
		if(m_bApplySelectionTransparency && selectedSampleIds.size() > 0)
		{
			// make non-selected items more transparent
			if(!selectedSampleIds.contains(sampleId))
				color.setAlpha(Properties::Inst().GetSelectionOpacity());
		}
					
		ParallelCoordCurve* curve = new ParallelCoordCurve(sampleId);
		curve->SetMarker(new ParallelCoordData(m_embedding, m_dimToDisplay, ptIndex), 
													shape, color, size, 
													m_samples->GetSample(sampleId).IsVisible(),
													selectedSampleIds.contains(sampleId), 
													m_samples->GetSample(sampleId).IsGuaranteedVisible(),
													m_bFittedCurves, m_bShowCurves);

		curve->attach(plot);

		ptIndex++;
	}


	QFont font = plot->axisFont(QwtPlot::xBottom);
	QwtText xAxisLabel("Principal component");
	xAxisLabel.setFont(font);		
	plot->setAxisTitle(QwtPlot::xBottom, xAxisLabel);
	
	plot->setAxisMaxMinor(QwtPlot::xBottom, 0);

	plot->replot();
}

void ParallelCoordPlot::UpdateMarkers()
{
	if(m_embedding.size() == 0)
		return;

	QSet<uint> selectedSampleIds = m_samples->GetSelectedSampleIds();

	const QwtPlotItemList& itmList = m_plot->itemList();
	QList<ParallelCoordCurve*> curves;
	for(QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); ++it)
	{
		if((*it)->rtti() == ParallelCoordCurve::Rtti_ParallelCoordCurve)
		{
			ParallelCoordCurve *curve = (ParallelCoordCurve*)(*it);
			curves.append(curve);
		}
	}

	foreach(ParallelCoordCurve* curve, curves)
	{
		uint sampleId = curve->GetSampleId();

		QwtSymbol::Style shape = m_samples->GetSample(sampleId).GetShape();
		QColor color = m_samples->GetSample(sampleId).GetColor();
		uint size = m_samples->GetSample(sampleId).GetSize();

		if(m_bApplySelectionTransparency && selectedSampleIds.size() > 0)
		{
			// make non-selected items more transparent
			if(!selectedSampleIds.contains(sampleId))
				color.setAlpha(Properties::Inst().GetSelectionOpacity());
		}

		curve->SetVisualProperties(shape, color, size, 
															m_samples->GetSample(sampleId).IsVisible(),
															selectedSampleIds.contains(sampleId),
															m_samples->GetSample(sampleId).IsGuaranteedVisible(),
															m_bFittedCurves, m_bShowCurves);
	}

	m_plot->replot();
}

void ParallelCoordPlot::SendToDetachedWindow()
{
	DetachedPlotDlg* dlg = new DetachedPlotDlg(false);
	dlg->SetBackgroundColor(Properties::Inst().GetBackgroundColor());
	Clone(dlg->GetPlot());
	dlg->show();
}

void ParallelCoordPlot::Clone(QwtPlot* plot)
{
	plot->axisWidget(QwtPlot::xBottom)->setAutoFillBackground(true);
	plot->axisWidget(QwtPlot::yLeft)->setAutoFillBackground(true);
	plot->axisWidget(QwtPlot::xBottom)->setPalette(Properties::Inst().GetBackgroundColor());
	plot->axisWidget(QwtPlot::yLeft)->setPalette(Properties::Inst().GetBackgroundColor());
	plot->setCanvasBackground(Properties::Inst().GetBackgroundColor());
	plot->setCanvasLineWidth(0);

	Plot(plot);
}

void ParallelCoordPlot::SetBackgroundColor(const QColor& color)
{
	m_plot->axisWidget(QwtPlot::xBottom)->setPalette(color);
	m_plot->axisWidget(QwtPlot::yLeft)->setPalette(color);

	m_plot->setCanvasBackground(color);

	m_plot->replot();
}