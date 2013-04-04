//=======================================================================
// Author: Donovan Parks
//
// Copyright 2009 Donovan Parks
//
// Based on code by: Julien Dutheil and Celine Scornavacca (Bio++ project)
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

#include "VisualScale.hpp"

#include "Properties.hpp"

const int SCALE_Z_VALUE = 10;

const int SELECTION_OFFSET = 3;

VisualScale::VisualScale()
	: m_scale(0.1f), m_pixelsToBranchLength(1.0), m_numSignDigits(2), m_lineWidth(1), 
		m_labelWidth(0), m_labelHeight(0), m_bAutomatic(true)
{
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setCacheMode(DeviceCoordinateCache);
	setZValue(SCALE_Z_VALUE);
	setVisible(false);
}


QRectF VisualScale::boundingRect() const
{
	double width = m_pixelsToBranchLength*m_scale;
	double horOffset = SELECTION_OFFSET;
	if(m_labelWidth > width)
	{
		horOffset = 0.5*(m_labelWidth - width) + SELECTION_OFFSET;
		width = m_labelWidth;
	}

	double penOffset = 0.5*m_lineWidth;
	double lineLength = m_pixelsToBranchLength*m_scale;
	return QRectF(-horOffset - penOffset, 
									-2 -SELECTION_OFFSET - penOffset, 
									width + 2*horOffset + 2*penOffset, 
									m_labelHeight + 4 + 2*SELECTION_OFFSET + 2*penOffset);
}

void VisualScale::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::Antialiasing, false);

	// get dimensions of scale label
	QString scaleStr = QString::number(m_scale, 'f', m_numSignDigits);
	painter->setFont(m_font);
	QFontMetrics fm = painter->fontMetrics();
	qreal labelWidth = fm.width(scaleStr);
	if(labelWidth!= m_labelWidth || fm.height() != m_labelHeight)
	{
		prepareGeometryChange();
		m_labelWidth = labelWidth;
		m_labelHeight = fm.height();
	}

	// draw selection box
	if(option->state & QStyle::State_Selected)
	{
		painter->setPen(Properties::Inst().GetHighlightPen());
		painter->setBrush(Properties::Inst().GetHighlightBrush());
		painter->drawRoundedRect(boundingRect(), 3, 3);
	}

	QPen pen;
	pen.setCosmetic(true);
	pen.setWidth(m_lineWidth);
	painter->setPen(pen);
	painter->setBrush(QBrush());

	// draw line
	float lineLength = m_pixelsToBranchLength*m_scale;

	painter->drawLine(0, 0, lineLength, 0);						// main line
	painter->drawLine(0, -2, 0, 2);										// left tick mark
	painter->drawLine(lineLength, -2, lineLength, 2);	// right tick mark

	// draw scale label
	painter->setPen(QPen(m_fontColor));
	if(m_labelWidth < lineLength)
		painter->drawText(QRectF(0, 2 + 0.5*m_lineWidth, lineLength, m_labelHeight), Qt::AlignHCenter, scaleStr);
	else
		painter->drawText(QRectF(-0.5*(m_labelWidth - lineLength), 2 + 0.5*m_lineWidth, m_labelWidth, m_labelHeight), Qt::AlignHCenter, scaleStr);
}

void VisualScale::SetFont(const QFont& font, const QColor& color) 
{ 
	prepareGeometryChange();
	m_font = font;
	m_fontColor = color;
	update();
}

void VisualScale::SetScale(double scale) 
{ 
	prepareGeometryChange();
	m_scale = scale; 
	update();
}

void VisualScale::SetPixelsPerUnitBranchLength(float pixelsToBranchLength) 
{ 
	prepareGeometryChange();
	m_pixelsToBranchLength = pixelsToBranchLength; 
	update();
}

void VisualScale::SetSignificantDigits(int digits) 
{ 
	prepareGeometryChange();
	m_numSignDigits = digits; 
	update();
}

void VisualScale::SetLineWidth(int width) 
{ 
	prepareGeometryChange();
	m_lineWidth = width; 
	update();
}

double VisualScale::SetAutomaticLength()
{
	double scale = 0.05;
	if(m_pixelsToBranchLength > 0)
	{
		// The pixels to branch length variable can be negative
		// before the viewport dimensions are properly initialized

		while(scale*m_pixelsToBranchLength < 50)
			scale *= 2;	
	}
	
	m_scale = scale;

	return scale;
}

void VisualScale::SetAutomaticScale(bool bAutomatic)
{
	m_bAutomatic = bAutomatic;

	if(m_bAutomatic)
		SetAutomaticLength();
}

void VisualScale::SetVisibility(bool bVisible)
{
	setVisible(bVisible);
	update();
}