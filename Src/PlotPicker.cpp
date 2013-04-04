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

#include "PlotPicker.hpp"

PlotPicker::PlotPicker(QwtPlot *plot): QObject(plot)
{
  m_canvas = plot->canvas();

  m_canvas->installEventFilter(this);

  // We want the focus, but no focus rect. The selected point will be highlighted instead.
  m_canvas->setFocusPolicy(Qt::StrongFocus);
  m_canvas->setCursor(Qt::ArrowCursor);
  m_canvas->setFocusIndicator(QwtPlotCanvas::ItemFocusIndicator);
  m_canvas->setFocus();
}

bool PlotPicker::event(QEvent *e)
{
	return QObject::event(e);
}

bool PlotPicker::eventFilter(QObject *object, QEvent *e)
{
	if ( object != (QObject *)plot()->canvas() )
		return false;

	switch(e->type())
	{
		case QEvent::Paint:
		{   
			QApplication::postEvent(this, new QEvent(QEvent::User));
			break;
		}

		case QEvent::MouseButtonRelease:
		{
			select(((QMouseEvent *)e)->pos());			
			return true; 
		}

		case QEvent::ToolTip:
		{
			select(((QHelpEvent *)e)->pos());			
			return true; 
		}

		default:
				break;
	}

	return QObject::eventFilter(object, e);
}

// Select the point at a position. If there is no point
// deselect the selected point
void PlotPicker::select(const QPoint& mousePos)
{
	QList<QwtPlotMarker*> selectedPts;

	const QwtPlotItemList& itmList = plot()->itemList();
	for ( QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); ++it )
	{
		if ( (*it)->rtti() == QwtPlotMarker::Rtti_PlotMarker )
		{
			QwtPlotMarker *pt = (QwtPlotMarker*)(*it);
			double ptX = plot()->transform(QwtPlot::xBottom, pt->xValue());
			double ptY = plot()->transform(QwtPlot::yLeft, pt->yValue());

			double d = (mousePos.x() - ptX)*(mousePos.x() - ptX) + (mousePos.y() - ptY)*(mousePos.y() - ptY);
			if( d < 0.5*pt->symbol()->size().width() * 0.5*pt->symbol()->size().width() )
			{
				selectedPts.push_back(pt);
			} 
		}
	}

	if(selectedPts.size() != 0)
	{
		QString sampleIdsStr;
		foreach(QwtPlotMarker* pt, selectedPts)
			sampleIdsStr += pt->title().text() + QString(", ");
		sampleIdsStr = sampleIdsStr.left(sampleIdsStr.size()-2);
		QToolTip::showText(m_canvas->mapToGlobal(mousePos), sampleIdsStr);
	}
}


