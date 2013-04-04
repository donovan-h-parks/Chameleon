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

#ifndef VISUAL_SUBTREE_HIGHLIGHTER
#define VISUAL_SUBTREE_HIGHLIGHTER

#include "VisualNode.hpp"

class VisualSubtreeHighlighter: public QGraphicsItem
{
public:
	VisualSubtreeHighlighter();

	void SetSubtree(VisualNode* node);

	void UpdateSubtreeExtents();

	void SetVisibility(bool bVisible);	

protected:
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
	VisualNode* m_node;

	QRectF m_extents;
};

#endif