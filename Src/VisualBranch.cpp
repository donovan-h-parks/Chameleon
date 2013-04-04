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

#include "VisualBranch.hpp"

#include "VisualNode.hpp"
#include "VisualTree.hpp"

#include "Properties.hpp"

#include "Geometry.hpp"

#include "TreeTools.hpp"

const int SELECT_ADJUSTMENT = 5;
const int SELECTION_PEN_ADJUSTMENT = 1;
const int EDGE_Z_VALUE = 2;

VisualBranch::VisualBranch(): m_width(1), m_labelWidth(0), m_labelHeight(0), m_bDrawOutline(true)
{
	Initialize();
}

VisualBranch::VisualBranch(VisualNode* source, VisualNode* dest, const QColor& color, qreal width)
	: m_source(source), m_dest(dest), m_color(color), m_width(width), m_labelWidth(0), m_labelHeight(0), m_bDrawOutline(true) 
{
	Initialize();
	source->AddBranch(this);
	dest->SetParentBranch(this);
}

VisualBranch::VisualBranch(VisualBranch &rhs)
{
	m_source = rhs.GetSource();
	m_dest = rhs.GetDest();
	
	m_color = rhs.GetColor();
	m_width = rhs.GetWidth();	
}

void VisualBranch::Initialize()
{
	//setFlag(ItemIsSelectable);
	setZValue(EDGE_Z_VALUE);
}

QRectF VisualBranch::boundingRect() const
{
	if(m_tree->GetLayoutStyle() == VisualTree::RECTANGULAR_LAYOUT)
		return RectangularBoundingRect();

	Log::Inst().Error("VisualBranch::boundingRect(): unhandled layout style");
	return QRectF();
}



QRectF VisualBranch::RectangularBoundingRect() const
{
	float adjust = (0.5 * m_width) + SELECT_ADJUSTMENT + 1;

	if(m_labelWidth < m_dest->x() - m_source->x())
	{
		return QRectF(QPointF(m_source->x(), m_source->y()), QPointF(m_dest->x(), m_dest->y()))
									 .normalized()
									 .adjusted(-adjust, -m_labelHeight-adjust, adjust, adjust);
	}
	else
	{
		QRectF bb = QRectF(QPointF(m_dest->x()-m_labelWidth-0.5*qMax<float>(m_dest->GetSize(), m_width), m_source->y()), 
														QPointF(m_dest->x(), m_dest->y())).normalized().adjusted(-adjust, -m_labelHeight-adjust, adjust, adjust);
		return bb;
	}

}

void VisualBranch::AdjustExtents(double& xMin, double& xMax, double& yMin, double& yMax, const QPointF& pt) const
{
	if(pt.x() < xMin)
		xMin = pt.x();
	
	if(pt.x() > xMax)
		xMax = pt.x();

	if(pt.y() < yMin)
		yMin = pt.y();
	
	if(pt.y() > yMax)
		yMax = pt.y();
}

QPainterPath VisualBranch::shape() const
{
	if(m_tree->GetLayoutStyle() == VisualTree::RECTANGULAR_LAYOUT)
		return RectangularShape();

	Log::Inst().Error("VisualBranch::shape(): unhandled layout style");
	return QPainterPath();
}

QPainterPath VisualBranch::RectangularShape() const
{
	QPainterPath path;

	qreal adjustX = (0.5 * m_width) + SELECT_ADJUSTMENT;
	qreal adjustY = adjustX;
	if(m_dest->y() < m_source->y())
		adjustY = -adjustX;

	QVector<QPointF> points;
	if(m_source->IsRoot())
	{
		points << QPointF(m_source->x()-adjustX, m_source->y()-adjustY);
		points << QPointF(m_dest->x(), m_source->y()-adjustY);
		points << QPointF(m_dest->x(), m_source->y()+adjustY);
		points << QPointF(m_source->x()-adjustX, m_source->y()+adjustY);
	}
	else
	{
		points << QPointF(m_source->x()-adjustX, m_source->y());
		points << QPointF(m_source->x()-adjustX, m_dest->y()+adjustY);
		points << QPointF(m_dest->x(), m_dest->y()+adjustY);
		points << QPointF(m_dest->x(), m_dest->y()-adjustY);
		points << QPointF(m_source->x()+adjustX, m_dest->y()-adjustY);
		points << QPointF(m_source->x()+adjustX, m_source->y());
	}

	path.addPolygon(QPolygonF(points));
	path.closeSubpath();

	return path;
}

void VisualBranch::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if(m_tree->GetLayoutStyle() == VisualTree::RECTANGULAR_LAYOUT)
		PaintRectangular(painter, option, widget, GetLabel());
}

QString VisualBranch::GetLabel() const
{
	QString branchLabel;
	if(m_tree->GetBranchLabelType() == NO_LABEL)
		branchLabel = "";
	else if(m_tree->GetBranchLabelType() == ASSIGNED_INTERNAL_LABELS)
	{
		if(m_dest->IsLeaf())
			branchLabel = "";
		else
			branchLabel = m_dest->GetName();
	}
	else if(m_tree->GetBranchLabelType() == LENGTH_LABEL)
		branchLabel = QString::number(m_dest->GetDistanceToParent(), 'g', 3);
	else if(m_tree->GetBranchLabelType() == DEPTH_LABEL)
		branchLabel = QString::number(m_dest->GetDepth(), 'g', 3);
	else if(m_tree->GetBranchLabelType() == HEIGHT_LABEL)
		branchLabel = QString::number(m_dest->GetHeight(), 'g', 3);

	return branchLabel;
}

void VisualBranch::PaintRectangular(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, const QString& label)
{
	// draw selection box
	if(option->state & QStyle::State_Selected)
	{
		painter->setPen(Properties::Inst().GetHighlightPen());
		painter->setBrush(Properties::Inst().GetHighlightBrush());
		painter->drawPath(shape());
	}

	painter->setRenderHint(QPainter::Antialiasing, false);

	QPen pen;
	pen.setCosmetic(true);
	
	uint width = m_width;
	if((m_width & 1) == 0)
		width++;

	if(m_source->IsRoot())
	{
		// drawing the 'root' branch is a special case
		if(m_bDrawOutline)
		{
			pen.setColor(Qt::black);
			painter->setPen(pen);

			float offset = int(0.5*width) + 1;
			QLineF horLine1(m_source->x()-offset+1, m_source->y()-offset, m_dest->x()-offset, m_source->y()-offset);
			QLineF horLine2(m_source->x()-offset+1, m_source->y()+offset, m_dest->x()-offset, m_source->y()+offset);

			painter->drawLine(horLine1);
			painter->drawLine(horLine2);
		}

		// draw colour interior
		pen.setColor(m_color);	
		pen.setWidth(width);
		painter->setPen(pen);

		QLineF horLine(m_source->x(), m_source->y(), m_dest->x(), m_source->y());
		painter->drawLine(horLine);

		return;
	}

	// draw black outline
	if(m_bDrawOutline)
	{
		pen.setColor(Qt::black);
		painter->setPen(pen);

		QLineF vertLine1, vertLine2, horLine1, horLine2;
		float offset = int(0.5*width) + 1;
		if(m_source->y() > m_dest->y())
		{
			float x = m_source->x();
			vertLine1 = QLineF(m_source->x()-offset, m_source->y()-offset, m_source->x()-offset, m_dest->y()-offset);
			vertLine2 = QLineF(m_source->x()+offset, m_source->y(), m_source->x()+offset, m_dest->y()+offset);

			horLine1 = QLineF(m_source->x()-offset, m_dest->y()-offset, m_dest->x()-offset, m_dest->y()-offset);
			horLine2 = QLineF(m_source->x()+offset, m_dest->y()+offset, m_dest->x()-offset, m_dest->y()+offset);
		}
		else
		{
			vertLine1 = QLineF(m_source->x()-offset, m_source->y()+offset, m_source->x()-offset, m_dest->y()+offset);
			vertLine2 = QLineF(m_source->x()+offset, m_source->y(), m_source->x()+offset, m_dest->y()-offset);

			horLine1 = QLineF(m_source->x()-offset, m_dest->y()+offset, m_dest->x()-offset, m_dest->y()+offset);
			horLine2 = QLineF(m_source->x()+offset, m_dest->y()-offset, m_dest->x()-offset, m_dest->y()-offset);
		}

		if(m_dest->IsLeaf())
		{
			horLine1.setP2(QPointF(horLine1.x2() + offset, horLine1.y2()));
			horLine2.setP2(QPointF(horLine2.x2() + offset, horLine2.y2()));

			painter->drawLine(QLineF(m_dest->x(), m_dest->y()-offset, m_dest->x(), m_dest->y()+offset));
		}

		painter->drawLine(vertLine1);	
		painter->drawLine(vertLine2);
		painter->drawLine(horLine1);
		painter->drawLine(horLine2);
	}

	// draw colour interior
	QLineF vertLine, horLine;
	if(m_source->y() > m_dest->y())
		vertLine = QLineF(m_source->x(), m_source->y()-0.5*width, m_source->x(), m_dest->y());
	else
		vertLine = QLineF(m_source->x(), m_source->y()+0.5*width, m_source->x(), m_dest->y());

	if(m_dest->IsLeaf())
		horLine = QLineF(m_source->x(), m_dest->y(), m_dest->x()-0.5*width, m_dest->y());
	else
		horLine = QLineF(m_source->x(), m_dest->y(), m_dest->x(), m_dest->y());

	pen.setColor(m_color);	
	pen.setWidth(width);
	painter->setPen(pen);
	painter->drawLine(vertLine);
	painter->drawLine(horLine);
	
	// draw branch label
	if(label != "")
	{		
		painter->setPen(m_tree->GetBranchFontColor());
		painter->setFont(m_tree->GetBranchFont());
		if(horLine.length() > m_labelWidth)
		{
			painter->drawText(m_source->x(), m_dest->y()-m_labelHeight-0.5*m_width, 
													horLine.length(), m_labelHeight, 
													Qt::AlignVCenter | Qt::AlignHCenter,  label);
		}
		else
		{
			painter->drawText(m_dest->x()-m_labelWidth-0.5*qMax<float>(m_dest->GetSize(), m_width), 
													m_dest->y()-m_labelHeight-0.5*m_width, 
													m_labelWidth, m_labelHeight, 
													Qt::AlignVCenter | Qt::AlignHCenter,  label);
		}
	}
}

void VisualBranch::SetWidth(int width) 
{ 
	if(m_width == width)
		return;

	prepareGeometryChange();
	m_width = width; 
	update();
}

void VisualBranch::SetDrawOutline(bool state)
{ 
	if(m_bDrawOutline == state)
		return;

	prepareGeometryChange();
	m_bDrawOutline = state; 
	update();
}

void VisualBranch::SetSource(VisualNode* source) 
{ 
	source->AddBranch(this);
	prepareGeometryChange();
	m_source = source; 
	update();
}


void VisualBranch::SetDest(VisualNode* dest) 
{ 
	dest->SetParentBranch(this);
	prepareGeometryChange();
	m_dest = dest; 
	update();
}

void VisualBranch::FontChanged()
{
	prepareGeometryChange();

	QFontMetrics fontMetrics(m_tree->GetBranchFont());
	m_labelHeight = fontMetrics.height();
	m_labelWidth = fontMetrics.width(GetLabel());

	update();	
}

void VisualBranch::SetColor(const QColor& color) 
{ 
	m_color = color; 
	update();
}
