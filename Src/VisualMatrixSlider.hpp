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

#ifndef VISUAL_MATRIX_SLIDER
#define VISUAL_MATRIX_SLIDER

#include "stdafx.h"

class VisualMatrixSlider: public QAbstractGraphicsShapeItem
{
public:
	VisualMatrixSlider(const QPolygonF& polygon, QGraphicsItem * parent);

	void SetSliderRange(const QPointF& start, const QPointF& end);
	void SetValueRange(float start, float end);

	QPointF GetPos() const { return pos(); }

	double GetValue() const;
	void SetValue(float value);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual QRectF boundingRect() const;

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
	QPolygonF m_polygon;
	QLineF m_range;
	
	float m_startValue;
	float m_endValue;

	bool m_bShowLabel;
};

#endif