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

#include "OrdinationPoint.hpp"

#include "Properties.hpp"

OrdinationPoint::OrdinationPoint(uint sampleId)
		: m_sampleId(sampleId), m_bSelected(false)
{
	setRenderHint(QwtPlotItem::RenderAntialiased);
	setLabelAlignment(Qt::AlignRight|Qt::AlignCenter);
}

void OrdinationPoint::SetMarker(double x, double y, const QString& label,
									QwtSymbol::Style shape, QColor& color, uint size, 
									bool bVisible, bool bSelected, bool bGuaranteedVisiblity)
{
	setValue(x, y);

	SetVisualProperties(label, shape, color, size, bVisible, bSelected, bGuaranteedVisiblity);
}

void OrdinationPoint::SetVisualProperties(const QString& label, QwtSymbol::Style shape, QColor& color, uint size, 
																	bool bVisible, bool bSelected, bool bGuaranteedVisiblity)
{
	setLabel(label);

	// set marker properties
	QwtSymbol* symbol;
	if(shape == QwtSymbol::Cross || shape == QwtSymbol::XCross || shape == QwtSymbol::HLine || shape == QwtSymbol::VLine || shape == QwtSymbol::Star1)
		symbol = new QwtSymbol(shape, QBrush(color), QPen(color), QSize(size,size));
	else
		symbol = new QwtSymbol(shape, QBrush(color), QPen(QColor(0,0,0,color.alpha())), QSize(size,size));

	setSymbol(symbol);

	setZ(bSelected + 2.0*bGuaranteedVisiblity);
	setVisible(bVisible);

	// set selection marker properties
	m_bSelected = bSelected;
}

void OrdinationPoint::draw(QPainter* painter, const QwtScaleMap& xMap, const QwtScaleMap& yMap, const QRectF& canvasRect) const
{
	// draw selection marker
	if(m_bSelected)
	{
		const QPointF pos(xMap.transform(xValue()), yMap.transform(yValue()));
		painter->save();
		painter->setPen(Properties::Inst().GetHighlightPen());
		painter->setBrush(Properties::Inst().GetHighlightBrush());
		int radius = 0.5*symbol()->size().width()+3;
		painter->drawRect(-radius+pos.x(), -radius+pos.y(), 2*radius, 2*radius);
		painter->restore();
	}

	QwtPlotMarker::draw(painter, xMap, yMap, canvasRect);
}

QRectF OrdinationPoint::boundingRect() const 
{ 
	if(m_bSelected)
	{
		int radius = 0.5*symbol()->size().width()+5;
		return QRectF(-radius, radius, -radius, radius);
	}
	
	return QwtPlotMarker::boundingRect();
}
