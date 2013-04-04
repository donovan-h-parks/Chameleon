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

#include "TreeViewport.hpp"

const float ZOOM_SENSITIVITY = 1.0f / 50.0f;

TreeViewport::TreeViewport(QWidget* parent ): QGraphicsView(parent), m_zoom(0)
{
	setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::SmoothPixmapTransform);
	setDragMode(QGraphicsView::RubberBandDrag);
	setOptimizationFlags(QGraphicsView::DontSavePainterState);
	//setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	//setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void TreeViewport::SetBackgroundColor(const QColor& color)
{
	setBackgroundBrush(QBrush(color));
}

void TreeViewport::keyPressEvent(QKeyEvent* event)
{
	QGraphicsView::keyPressEvent(event);
}

void TreeViewport::wheelEvent(QWheelEvent* event)
{
	const float STEP_SIZE = 15;

	if(event->modifiers() == Qt::ControlModifier)
	{
		m_zoom += (event->delta()/STEP_SIZE)*ZOOM_SENSITIVITY;
		SetProjectionMatrix();
	}
	else
	{
		QGraphicsView::wheelEvent(event);
	}
}

void TreeViewport::resizeEvent(QResizeEvent* event)
{
	QGraphicsView::resizeEvent(event);
	emit ViewportResized(viewport()->width(), viewport()->height());
}

void TreeViewport::ViewRoot()
{
	ensureVisible(QRectF(0, 0, 0, 0));
}

void TreeViewport::ZoomIn()
{
	m_zoom += ZOOM_SENSITIVITY;
	SetProjectionMatrix();
}

void TreeViewport::ZoomOut()
{
	m_zoom -= ZOOM_SENSITIVITY;
	SetProjectionMatrix();
}

void TreeViewport::ZoomDefault()
{
	m_zoom = 0;
	SetProjectionMatrix();
}

void TreeViewport::SetProjectionMatrix()
{
	qreal scale = qPow(2.0f, m_zoom);

	QMatrix matrix;
	matrix.scale(scale, scale);
	setMatrix(matrix);
}