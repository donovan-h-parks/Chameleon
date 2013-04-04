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

#ifndef BOX_PLOT_HPP
#define BOX_PLOT_HPP

#include "stdafx.h"

class BoxPlot: public QGraphicsItem
{
public:
	struct BoxPlotData
	{
		double minimum;
		double lowerQuartile;
		double median;
		double upperQuartile;
		double maximum;
		double iqr;
		double lowerWhisker;
		double upperWhisker;
		QList<double> outliers;
	};

public:
	BoxPlot() {}

	void SetData(const Matrix& dissVectors, const QStringList& labels);

	QGraphicsScene* GetScene() const { return m_scene; }

	QRectF boundingRect() const;

	void SetBackgroundColor(const QColor& color) { m_scene->setBackgroundBrush(QBrush(color)); }

	QList<BoxPlotData> GetBoxPlotData() const { return m_boxPlots; }

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void resizeEvent(QResizeEvent* e);

	void hoverMoveEvent( QGraphicsSceneHoverEvent* e);
	void mousePressEvent( QGraphicsSceneMouseEvent * e);
	void mouseDoubleClickEvent( QGraphicsSceneMouseEvent * e );

private:
	QGraphicsScene* m_scene;

	QList<BoxPlotData> m_boxPlots;
};

#endif