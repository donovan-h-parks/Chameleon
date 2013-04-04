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

#include "BoxPlot.hpp"

void BoxPlot::SetData(const Matrix& dissVectors, const QStringList& labels)
{
	m_boxPlots.clear();

	for(int i = 0; i < dissVectors.size(); ++i)
	{
		QVector<double> vec = dissVectors.at(i);
		qSort(vec.begin(), vec.end());

		BoxPlotData boxPlot;
		boxPlot.minimum = vec.at(0);
		boxPlot.maximum = vec.at(vec.size()-1);

		int mid = vec.size() / 2;
		int midLQ = mid / 2;
		int midUQ = vec.size() - midLQ;
		if(vec.size() % 2 == 0)
		{			
			boxPlot.median = (vec.at(mid)+vec.at(mid-1))/2;
			boxPlot.lowerQuartile = (vec.at(midLQ)+vec.at(midLQ-1))/2;
			boxPlot.upperQuartile = (vec.at(midUQ)+vec.at(midUQ-1))/2;
		}
		else
		{
			boxPlot.median = vec.at(mid);
			boxPlot.lowerQuartile = vec.at(midLQ);
			boxPlot.upperQuartile = vec.at(midUQ-1);
		}

		boxPlot.iqr = boxPlot.upperQuartile - boxPlot.lowerQuartile;
		boxPlot.lowerWhisker = qMax<double>(boxPlot.minimum, boxPlot.lowerQuartile - 1.5*boxPlot.iqr);
		boxPlot.upperWhisker = qMin<double>(boxPlot.maximum, boxPlot.upperQuartile + 1.5*boxPlot.iqr);

		foreach(double value, vec)
		{
			if(value < boxPlot.lowerWhisker || value > boxPlot.upperWhisker)
				boxPlot.outliers.append(value);
		}

		m_boxPlots.append(boxPlot);
	}
}

QRectF BoxPlot::boundingRect() const
{
	return QRectF();
}

void BoxPlot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void BoxPlot::resizeEvent(QResizeEvent* e)
{
	update();
}

void BoxPlot::hoverMoveEvent( QGraphicsSceneHoverEvent* e)
{

}

void BoxPlot::mousePressEvent( QGraphicsSceneMouseEvent * e)
{

}

void BoxPlot::mouseDoubleClickEvent( QGraphicsSceneMouseEvent * e )
{

}
