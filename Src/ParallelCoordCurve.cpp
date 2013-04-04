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

#include "ParallelCoordCurve.hpp"

#include "ParallelCoordPlot.hpp"

#include "Properties.hpp"

ParallelCoordCurve::ParallelCoordCurve(uint sampleId)
	: m_sampleId(sampleId), m_selectedCurve(new QwtPlotCurve()), m_bSelected(false)
{
	setRenderHint(QwtPlotItem::RenderAntialiased);
	setItemAttribute(QwtPlotItem::AutoScale);

	m_selectedCurve->setStyle(QwtPlotCurve::NoCurve);
}

void ParallelCoordCurve::SetMarker(ParallelCoordData* data, 
																			QwtSymbol::Style shape, QColor& color, uint size, 
																			bool bVisible, bool bSelected, bool bGuaranteedVisiblity, 
																			bool bFittedCurves, bool bShowCurves)
{
	setData(data);
	m_selectedCurve->setData(data);

	SetVisualProperties(shape, color, size, bVisible, bSelected, bGuaranteedVisiblity, bFittedCurves, bShowCurves);
}

void ParallelCoordCurve::SetVisualProperties(QwtSymbol::Style shape, QColor& color, uint size, 
																								bool bVisible, bool bSelected, bool bGuaranteedVisiblity,
																								bool bFittedCurves, bool bShowCurves)
{
	// set marker properties
	QwtSymbol* symbol;
	if(shape == QwtSymbol::Cross || shape == QwtSymbol::XCross || shape == QwtSymbol::HLine || shape == QwtSymbol::VLine || shape == QwtSymbol::Star1)
		symbol = new QwtSymbol(shape, QBrush(color), QPen(color), QSize(size,size));
	else
		symbol = new QwtSymbol(shape, QBrush(color), QPen(QColor(0,0,0,color.alpha())), QSize(size,size));

	setSymbol(symbol);
	setPen(color);

	if(bFittedCurves)
		setCurveAttribute(QwtPlotCurve::Fitted);

	if(bShowCurves)
		setStyle(QwtPlotCurve::Lines);
	else
		setStyle(QwtPlotCurve::NoCurve);

	setZ(bSelected + 2.0*bGuaranteedVisiblity);
	setVisible(bVisible);

	// set selection marker properties
	QwtSymbol* selectionSymbol = new QwtSymbol(QwtSymbol::Rect, Properties::Inst().GetHighlightBrush(), Properties::Inst().GetHighlightPen(),	QSize(size+5,size+5));
	m_selectedCurve->setSymbol(selectionSymbol);
	m_selectedCurve->setZ(bSelected + 2.0*bGuaranteedVisiblity - 0.5);

	m_bSelected = bSelected;
}

void ParallelCoordCurve::draw(QPainter* p, const QwtScaleMap& xMap, const QwtScaleMap& yMap, const QRectF& canvasRect) const
{
	QwtPlotCurve::draw(p, xMap, yMap, canvasRect);

	if(m_bSelected)
		m_selectedCurve->draw(p, xMap, yMap, canvasRect);
}

QRectF ParallelCoordCurve::boundingRect() const 
{ 
	if(m_bSelected)
		return m_selectedCurve->boundingRect();

	return QwtPlotCurve::boundingRect();
}