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

#include "VisualMatrixSlider.hpp"

#include "Geometry.hpp"

VisualMatrixSlider::VisualMatrixSlider(const QPolygonF& polygon, QGraphicsItem * parent)
	: QAbstractGraphicsShapeItem(parent), m_polygon(polygon), m_bShowLabel(true)
{
	setFlag(ItemIsMovable);
	setFlag(ItemSendsGeometryChanges);

	m_range = QLineF(QPointF(0,0), QPointF(1,0));
	m_startValue = 0;
	m_endValue = 1;
	setPos(0.5, 0);
}

void VisualMatrixSlider::SetSliderRange(const QPointF& start, const QPointF& end)
{
	m_range = QLineF(start, end);
}

void VisualMatrixSlider::SetValueRange(float start, float end)
{
	m_startValue = start;
	m_endValue = end;
}

double VisualMatrixSlider::GetValue() const
{
	float rangeDist = m_range.length();
	float posDist = QLineF(m_range.p1(), pos()).length();

	float valueRange = m_endValue - m_startValue;

	return m_startValue + valueRange*(posDist/rangeDist);
}

void VisualMatrixSlider::SetValue(float value)
{
	float valueRange = m_endValue - m_startValue;

	float lengthAlongLine = (value - m_startValue) / valueRange;

	QPointF pos = m_range.pointAt(lengthAlongLine);

	setPos(pos.x(), pos.y());

	update();
}

QVariant VisualMatrixSlider::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if(change == ItemPositionChange && scene()) 
	{
		parentItem()->update();

		// value is the new position.
		QPointF newPos = value.toPointF();

		// project position to line
		QPointF closestPoint;
		Geometry::ClosestPointToLineSegment(m_range, newPos, closestPoint);

		// keep the item on the line
		newPos.setX(closestPoint.x());
		newPos.setY(closestPoint.y());

		return newPos;
	}

	return QGraphicsItem::itemChange(change, value);
}

void VisualMatrixSlider::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(QPen(Qt::black));
	painter->setBrush(QBrush(Qt::lightGray));

	painter->drawPolygon(m_polygon);

	if(m_bShowLabel)
	{
		int labelOffset = 0.5 * painter->fontMetrics().ascent();
		painter->drawText(QPointF(m_polygon.boundingRect().width()+2, labelOffset), 
																				QString::number(GetValue(), 'g', 3));
	}
}

QRectF VisualMatrixSlider::boundingRect() const
{
	if(m_bShowLabel)
	{
		QString label = QString::number(GetValue(), 'g', 3);

		QFont font;
		QFontMetrics fm(font);
		float labelWidth = fm.width(label);
		float labelHeight = fm.height();

		float height = qMax<float>(labelHeight, m_polygon.boundingRect().height());
		float width = m_polygon.boundingRect().width() + labelWidth + 2;

		return QRectF(0, -0.5*height, width, height);
	}
	
	return m_polygon.boundingRect();
}