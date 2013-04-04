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

#include "VisualAxis.hpp"

#include "Properties.hpp"

#include "Metadata.hpp"

const int SCALE_Z_VALUE = 10;
const int LABEL_OFFSET_X = 4;

VisualAxis::VisualAxis()
	: m_width(6), m_height(100), m_labelHeight(0), m_maxLabelWidth(0), 
		m_field("<none>"), m_bLabelVisibility(true), m_fontColor(Qt::black)
{
	setFlag(ItemIsSelectable);
	setFlag(ItemIsMovable);
	setCacheMode(DeviceCoordinateCache);
	setZValue(SCALE_Z_VALUE);
	setVisible(false);
}


QRectF VisualAxis::boundingRect() const
{
	return QRectF(0, -m_labelHeight, m_width + m_maxLabelWidth + LABEL_OFFSET_X, m_height + 2*m_labelHeight);
}

void VisualAxis::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::Antialiasing, false);

	// draw axis
	QPen pen;
	pen.setCosmetic(true);
	pen.setWidth(1);
	painter->setPen(pen);

	QLinearGradient gradient(QPointF(0,0), QPointF(0, m_height));
	gradient.setColorAt(0, Qt::white);
	gradient.setColorAt(1, Qt::red);
	painter->setBrush(QBrush(gradient));

	painter->drawRect(0, 0, m_width, m_height);

	//draw label tick marks and text
	if(m_bLabelVisibility)
	{
		painter->setFont(m_font);
		QFontMetrics fm = painter->fontMetrics();
		int labelOffset = 0.5 * fm.ascent() - 1;
		
		double range = m_values.at(m_values.size()-1) - m_values.at(0);

		// draw label tick marks
		painter->setPen(QPen(Qt::black));
		painter->setBrush(QBrush(Qt::black));
		for(int i = 1; i < m_values.size() - 1; ++i)
		{
			double yOffset = ((m_values.at(i) - m_values.at(0)) / range)*m_height;
			painter->drawLine(m_width-1, yOffset, m_width+1, yOffset);
		}

		// draw label text
		painter->setPen(QPen(m_fontColor));		
		foreach(double value, m_values)
		{
			double yOffset = ((value - m_values.at(0)) / range)*m_height;

			QString valueStr = QString::number(value, 'f', 2);
			painter->drawText(m_width + LABEL_OFFSET_X, yOffset + labelOffset, valueStr);
		}
	}
}

void VisualAxis::SetFont(const QFont& font, const QColor& color) 
{ 
	prepareGeometryChange();
	m_font = font;
	m_fontColor = color;
	update();
}

void VisualAxis::SetWidth(int width) 
{ 
	prepareGeometryChange();
	m_width = width; 
	update();
}

void VisualAxis::SetHeight(int height) 
{ 
	prepareGeometryChange();
	m_height = height; 
	update();
}

void VisualAxis::SetVisibility(bool bVisible)
{
	setVisible(bVisible);
	update();
}

void VisualAxis::SetLabelVisibility(bool bVisible)
{
	prepareGeometryChange();
	m_bLabelVisibility = bVisible;
	update();
}

void VisualAxis::SetData(MetadataPtr metadata, const QString& field)
{
	prepareGeometryChange();

	m_maxLabelWidth = 0;
	if(field != "<none>")
	{
		setVisible(true);

		// get all values for axis and determine widest label
		QFontMetrics fontMetrics(m_font);	
		m_values.clear();
		QVector<QString> values = metadata->GetValues(field);
		foreach(const QString& value, values)
		{
			double v = value.toDouble();
			m_values.append(v);

			int labelWidth = fontMetrics.width(QString::number(v, 'f', 2));
			if(labelWidth > m_maxLabelWidth)
				m_maxLabelWidth = labelWidth;
		}

		m_labelHeight = fontMetrics.height();

		qSort(m_values.begin(), m_values.end());
	}
	else
		setVisible(false);

	update();
}