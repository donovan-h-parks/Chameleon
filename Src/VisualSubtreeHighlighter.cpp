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

#include "VisualSubtreeHighlighter.hpp"

#include "VisualTree.hpp"
#include "TreeTools.hpp"

const int HIGHLIGHTER_Z_VALUE = 0;
const int HIGHLIGHTER_OFFSET = 2;

VisualSubtreeHighlighter::VisualSubtreeHighlighter(): m_node(NULL)
{
	setCacheMode(DeviceCoordinateCache);
	setZValue(HIGHLIGHTER_Z_VALUE);
}


QRectF VisualSubtreeHighlighter::boundingRect() const
{
	return m_extents;
}

void VisualSubtreeHighlighter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setPen(QPen(QColor(164, 164, 164)));
	painter->setBrush(QBrush(QColor(240, 240, 240)));
	painter->drawRoundedRect(boundingRect(), 3, 3);
}

void VisualSubtreeHighlighter::SetSubtree(VisualNode* node) 
{ 
	m_node = node; 
	UpdateSubtreeExtents();
}

void VisualSubtreeHighlighter::UpdateSubtreeExtents()
{
	if(!m_node || !isVisible())
		return;

	prepareGeometryChange();

	QRectF bb = m_node->boundingRect();

	float xMin = bb.left() + m_node->x();	
	float xMax = bb.right() + m_node->x();
	
	float yMin = bb.top() + m_node->y();
	float yMax = bb.bottom() + m_node->y();

	QQueue<VisualNode*> queue;
	queue.enqueue(m_node);
	while(!queue.empty())
	{
		VisualNode* node = queue.dequeue();
		if(node->IsCollapsed() || node->IsLeaf())
		{
			QRectF bb = node->boundingRect();

			if(bb.left() + node->x() < xMin)
				xMin = bb.left() + node->x();

			if(bb.right() + node->x() > xMax)
				xMax = bb.right() + node->x();

			if(bb.top() + node->y() < yMin)
				yMin = bb.top() + node->y();

			if(bb.bottom() + node->y() > yMax)
				yMax = bb.bottom() + node->y();
		}
		else	// not collapsed and not a leaf node
		{
			foreach(VisualNode* child, node->GetChildren())
				queue.enqueue(child);
		}
	}

	m_extents = QRectF(xMin - HIGHLIGHTER_OFFSET, yMin - HIGHLIGHTER_OFFSET, (xMax-xMin) + 2*HIGHLIGHTER_OFFSET, (yMax-yMin) + 2*HIGHLIGHTER_OFFSET);
	update();
}

void VisualSubtreeHighlighter::SetVisibility(bool bVisible)
{
	setVisible(bVisible);
	update();
}