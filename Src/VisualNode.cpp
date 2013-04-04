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
// along with Chameleon.  If not, see <http://www.gnu.org/licenses/>.
//=======================================================================

#include "stdafx.h"

#include "VisualNode.hpp"

#include "VisualTree.hpp"
#include "Properties.hpp"
#include "TreeTools.hpp"
#include "ParsimonyCalculator.hpp"

#include "SplitSystem.hpp"
#include "Legends.hpp"

const int NODE_Z_VALUE = 3;
const int SELECTION_WIDTH = 2;
const int HIGHLIGHT_OFFSET = 2;
const int PEN_WIDTH = 1;
const int ALIGN_TIP_LINE_OFFSET = 4;

VisualNode::VisualNode(unsigned int id,  const QString& name)
	: m_id(id), m_name(name), m_collapsedLabel(name), m_parent(NULL), m_tree(NULL),
		m_distanceToRoot(VisualNode::NO_DISTANCE), m_distanceToParent(VisualNode::NO_DISTANCE), 
		m_distanceToClosestLeafNode(VisualNode::NO_DISTANCE),
		m_distanceToFurthestLeafNode(VisualNode::NO_DISTANCE),
		m_support(VisualNode::NO_DISTANCE), m_depth(0), m_bProcessed(false), m_bTextHighlight(false),
		m_diameter(0), m_labelWidth(0), m_labelHeight(0), m_bCollapsed(false),
		m_shape(QwtSymbol::Ellipse), m_parsimonyData(NULL), m_totalBranchLength(0),
		m_bActiveSet(true), m_bSelected(false), m_bBold(false)
{
	Initialize();

	setPos(0, 0);
}

VisualNode::VisualNode(unsigned int id,  const QString& name, qreal x, qreal y, qreal diameter)
	: m_id(id), m_name(name), m_parent(NULL), m_tree(NULL),
		m_distanceToRoot(VisualNode::NO_DISTANCE), m_distanceToParent(VisualNode::NO_DISTANCE), 
		m_distanceToClosestLeafNode(VisualNode::NO_DISTANCE),
		m_distanceToFurthestLeafNode(VisualNode::NO_DISTANCE),
		m_support(0), m_depth(0), m_bProcessed(false), m_bTextHighlight(false),
		m_diameter(4), m_labelWidth(0), m_labelHeight(0), m_bCollapsed(false),
		m_shape(QwtSymbol::Ellipse), m_parsimonyData(NULL), m_totalBranchLength(0),
		m_bActiveSet(true), m_bSelected(false), m_bBold(false)
{
	Initialize();

	setPos(x, y);
}

void VisualNode::Initialize()
{
	setFlag(ItemIsSelectable);
	setZValue(NODE_Z_VALUE);
	setAcceptsHoverEvents(true);
}

VisualNode::VisualNode(const VisualNode &rhs)
{
	m_id = rhs.GetId();
	m_name = rhs.GetName();
	m_distanceToParent = rhs.GetDistanceToParent();
	m_distanceToRoot = rhs.GetDistanceToRoot();
	m_distanceToClosestLeafNode = rhs.GetDistanceToClosestLeafNode();
	m_distanceToFurthestLeafNode = rhs.GetDistanceToFurthestLeafNode();
	m_totalBranchLength = rhs.GetTotalBranchLength();
	m_support = rhs.GetSupport();
	m_depth = rhs.GetDepth();
	m_height = rhs.GetHeight();
	
	m_bProcessed = rhs.IsProcessed();
	m_bActiveSet = rhs.IsActiveSet();
	m_bSelected = rhs.IsSelected();
	m_bBold = rhs.IsBold();
	m_bTextHighlight = rhs.IsTextHighlight();

	m_diameter = rhs.GetSize();
	m_color = rhs.GetColor();
	m_shape = rhs.GetShape();

	m_labelWidth = rhs.GetLabelWidth();
	m_labelHeight = rhs.GetLabelHeight(); 
	m_bCollapsed = rhs.IsCollapsed();

	m_parsimonyData = rhs.GetParsimonyData();

	m_parent = NULL;
	m_children.clear();

	m_parentBranch = NULL;
	m_tree = NULL;

	setFlag(ItemIsSelectable);
	setZValue(NODE_Z_VALUE);
	setAcceptsHoverEvents(true);
}

VisualNode& VisualNode::operator=(const VisualNode &rhs)
{
	if(this != &rhs)
	{
		m_id = rhs.GetId();
		m_name = rhs.GetName();
		m_distanceToParent = rhs.GetDistanceToParent();
		m_distanceToRoot = rhs.GetDistanceToRoot();
		m_distanceToClosestLeafNode = rhs.GetDistanceToClosestLeafNode();
		m_distanceToFurthestLeafNode = rhs.GetDistanceToFurthestLeafNode();
		m_totalBranchLength = rhs.GetTotalBranchLength();
		m_support = rhs.GetSupport();
		m_depth = rhs.GetDepth();
		m_bProcessed = rhs.IsProcessed();
		m_bActiveSet = rhs.IsActiveSet();
		m_bSelected = rhs.IsSelected();

		m_diameter = rhs.GetSize();
		m_labelWidth = rhs.GetLabelWidth();
		m_labelHeight = rhs.GetLabelHeight(); 
		m_bCollapsed = rhs.IsCollapsed();

		m_parsimonyData = rhs.GetParsimonyData();

		m_parent = NULL;
		m_children.clear();

		m_parentBranch = NULL;
		m_tree = NULL;

		setFlag(ItemIsSelectable);
		setZValue(NODE_Z_VALUE);
		setAcceptsHoverEvents(true);

		setSelected(rhs.isSelected());
	}

  return *this;
}

QList<unsigned int> VisualNode::GetChildrenIds() const
{
	QList<unsigned int> childrenId;
	for(int i = 0; i < m_children.size(); i++) 
	{
		childrenId.push_back(m_children.at(i)->GetId());
	}

	return childrenId;
}

VisualNode* VisualNode::GetChild(unsigned int pos) const
{
	return m_children.at(pos);
} 

void VisualNode::AddChild(unsigned int pos, VisualNode* node)
{
	m_children.insert(m_children.begin() + pos, node);
	node->SetParent(this);
}

void VisualNode::AddChild(VisualNode* node)
{
	m_children.push_back(node);
	node->SetParent(this);
}

void VisualNode::RemoveChild(unsigned int pos)
{
	m_children.erase(m_children.begin() + pos);
}

void VisualNode::RemoveChildren() 
{  
	m_children.clear();
}

void VisualNode::RemoveChild(VisualNode* node)
{
	for(int i = 0; i < m_children.size(); i++)
	{
		if(m_children.at(i) == node)
		{
			m_children.erase(m_children.begin() + i);
			return;
		}
	}
}

void VisualNode::Rotate() 
{ 
	uint lastIndex = m_children.size()-1;
	Swap(0, lastIndex); 
}

void VisualNode::Swap(unsigned int pos1, unsigned int pos2)
{
  VisualNode* node1 = GetChild(pos1);
  VisualNode* node2 = GetChild(pos2);

	// remove higher position item first!
	if(pos1 < pos2)
	{
		RemoveChild(pos2);
		RemoveChild(pos1);
	}
	else
	{
		RemoveChild(pos1);
		RemoveChild(pos2);
	}

  AddChild(pos1, node2);
  AddChild(pos2, node1);
}

unsigned int VisualNode::GetChildPosition(VisualNode* child) const
{
  for(int i = 0; i < m_children.size(); i++) 
	{
    if(m_children.at(i) == child) 
			return i;
  }

	assert(false);

	return m_children.size();	// invalid position
}

float VisualNode::GetSize() const 
{ 
	if(!m_tree)
		return m_diameter;

	if(m_tree->GetAbundanceStyle() == VisualTree::ABUNDANCE_PIE_CHART
				|| (IsLeaf() && m_tree->GetAbundanceStyle() == VisualTree::ABUNDANCE_PIE_CHART_LEAVES_ONLY))
	{
		return GetPieChartSize();
	}
	else
		return m_diameter; 
}

QRectF VisualNode::boundingRect() const
{
	if(m_bCollapsed)	
	{
		// calculate bounding box for collapsed node
		float lengthBL, lengthML, lengthTL, height;
		CollapsedNodeLineLengths(lengthBL, lengthML, lengthTL, height);
		
		float radius = 0.5 * m_diameter;
		float width = qMax<float>(lengthBL, qMax<float>(lengthML, lengthTL));
		if(GetLabel() != "")
		{
			if(m_tree->IsAlignedTips())
			{
				float length = m_tree->GetLabelStart() - x();
				width = length + m_labelWidth + radius;
			}
			else
			{
				width += m_labelWidth + VisualTree::LABEL_OFFSET;
			}
		}

		height += 2*SELECTION_WIDTH + 2*PEN_WIDTH;
		if(GetLabel() != "" && m_labelHeight > height)
			height = m_labelHeight;
			
		return QRectF(-radius - SELECTION_WIDTH - PEN_WIDTH, 
												-0.5*height, 
												width + 2*SELECTION_WIDTH + 2*PEN_WIDTH, 
												height);
	}
	else
	{
		int diameter = GetSize() + 2*SELECTION_WIDTH + 2*PEN_WIDTH;
		if(diameter < 10)	// make sure diameter is large enough for easy selection of nodes
			diameter = 10;

		float height = diameter;
		if(GetLabel() != "" && m_labelHeight > diameter)
			height = m_labelHeight;

		float width = diameter;
		if(GetLabel() != "" && m_labelWidth != 0)
			width += m_labelWidth;

		if(GetLabel() != "" && IsLeaf() && m_tree->IsAlignedTips())
		{
			float length = m_tree->GetLabelStart() - x();
			width += length - 0.5*GetSize();
		}
		else if(GetLabel() != "")
		{
			width += VisualTree::LABEL_OFFSET;
		}

		return QRectF(-0.5*diameter, -0.5*height, width, height);
	}

	return QRectF();
}

void VisualNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if(!m_bCollapsed)
	{
		if(m_tree->GetAbundanceStyle() == VisualTree::ABUNDANCE_PIE_CHART
				|| (IsLeaf() && m_tree->GetAbundanceStyle() == VisualTree::ABUNDANCE_PIE_CHART_LEAVES_ONLY))
		{
			PaintPieChart(painter, option, widget, GetLabel());
		}
		else
			PaintLeaf(painter, option, widget, GetLabel());
	}
	else
		PaintCollapsedNode(painter, option, widget);
}

float VisualNode::GetLabelWidth() const 
{ 
	return m_labelWidth; 
}

float VisualNode::GetLabelHeight() const 
{ 
	return m_labelHeight; 
}

void VisualNode::PaintLeaf(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, const QString& label)
{
	painter->setRenderHint(QPainter::Antialiasing, true);

	// set font for rendering text
	QFont font = m_tree->GetNodeFont();
	if(IsBold())
		font.setWeight(QFont::Bold);
	painter->setFont(font);

	// draw selection/highlight outline
	if(m_bTextHighlight)
	{
		painter->setPen(Properties::Inst().GetTextHighlightPen());
		painter->setBrush(Properties::Inst().GetTextHighlightBrush());
		painter->drawRoundedRect(boundingRect(), 0.5 * boundingRect().height(), 0.5 * boundingRect().height());	
	}
	else if(option->state & QStyle::State_Selected)
	{
		painter->setPen(Properties::Inst().GetHighlightPen());
		painter->setBrush(Properties::Inst().GetHighlightBrush());
		painter->drawRoundedRect(boundingRect(), 0.5 * boundingRect().height(), 0.5 * boundingRect().height());
	}

	// draw node
	if(m_shape == QwtSymbol::Cross || m_shape == QwtSymbol::XCross 
			|| m_shape == QwtSymbol::HLine || m_shape == QwtSymbol::VLine 
			|| m_shape == QwtSymbol::Star1)
	{
		QPen pen = QPen(m_color);
		pen.setWidth(2);
		painter->setPen(pen);
	}
	else
	{
		painter->setPen(QPen());
	}
		
	painter->setBrush(QBrush(m_color));
	qreal radius = 0.5 * m_diameter;
	QRectF rect(-radius, -radius, m_diameter, m_diameter);
	DrawSymbol(painter, m_shape, rect);

	// draw label
	if(label != "")
	{
		if(IsLeaf() && m_tree->IsAlignedTips())
		{	
			// draw dashed line
			float length = m_tree->GetLabelStart() - x() - 2*ALIGN_TIP_LINE_OFFSET - radius;
			if(length > ALIGN_TIP_LINE_OFFSET)
			{
				painter->setRenderHint(QPainter::Antialiasing, false);

				QPen pen;
				pen.setCosmetic(true);
				pen.setStyle(Qt::DotLine);
				pen.setColor(QColor(127, 127, 127));
				painter->setPen(pen);

				painter->drawLine(radius + ALIGN_TIP_LINE_OFFSET, 0, m_tree->GetLabelStart() - x() - ALIGN_TIP_LINE_OFFSET, 0);
			}

			// draw label	
			painter->setPen(QPen(m_tree->GetNodeFontColor()));
			painter->drawText(m_tree->GetLabelStart()-x(), -0.5 * m_labelHeight, 
												m_labelWidth, m_labelHeight, Qt::AlignVCenter | Qt::AlignLeft,  label);
		}
		else
		{
			painter->setPen(QPen(m_tree->GetNodeFontColor()));
			painter->drawText(0.5*GetSize() + VisualTree::LABEL_OFFSET, -0.5 * m_labelHeight,	
													m_labelWidth, m_labelHeight, Qt::AlignVCenter | Qt::AlignLeft,  label);
		}
	}
}

uint VisualNode::GetPieChartSize() const
{
	float numSeqs;
	if(m_tree->GetLeafTreatment() == VisualTree::RELATIVE_PROPORITON_TREATMENT)
		numSeqs = GetRelativeProportionOfSeqs();
	else if(m_tree->GetLeafTreatment() == VisualTree::WEIGHTED_TREATMENT)
		numSeqs = GetWeightedNumberOfSeqs();
	else
		numSeqs = GetNumberOfSeqs();

	float relativeAbundance = float(numSeqs) / m_tree->GetMaxAbundance();
	uint size = uint(relativeAbundance*m_tree->GetMaxAbundanceSize() + 0.5);

	if(size < m_tree->GetMinAbundanceSize())
		size = m_tree->GetMinAbundanceSize();

	if(size > m_tree->GetMaxAbundanceSize())
		size = m_tree->GetMaxAbundanceSize();

	return size;
}

void VisualNode::PaintPieChart(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, const QString& label)
{
	painter->setRenderHint(QPainter::Antialiasing, true);

	// calculate size of pie chart
	uint size = GetPieChartSize();

	// set font for rendering text
	QFont font = m_tree->GetNodeFont();
	if(IsBold())
		font.setWeight(QFont::Bold);
	painter->setFont(font);

	// draw selection/highlight outline
	if(m_bTextHighlight)
	{
		painter->setPen(Properties::Inst().GetTextHighlightPen());
		painter->setBrush(Properties::Inst().GetTextHighlightBrush());
		painter->drawRoundedRect(boundingRect(), 0.5 * boundingRect().height(), 0.5 * boundingRect().height());	
	}
	else if(option->state & QStyle::State_Selected)
	{
		painter->setPen(Properties::Inst().GetHighlightPen());
		painter->setBrush(Properties::Inst().GetHighlightBrush());
		painter->drawRoundedRect(boundingRect(), 0.5 * boundingRect().height(), 0.5 * boundingRect().height());
	}

	// get size of each pie chart wedge
	QSet<uint> activeSampleIds = m_tree->GetActiveSystem()->GetSamples()->GetActiveSampleIds();
	QMap<QString, uint> colorMap;
	float totalWeight = 0;
	foreach(const VisualNode* leaf, TreeTools<VisualNode>::GetLeaves(this))
	{
		// get all colors assigned to the leaf node
		QList<uint> sampleIds = m_tree->GetActiveSystem()->GetSamples()->GetSequences()->GetSampleIdsFromSeqId(leaf->GetId());
		foreach(uint sampleId, sampleIds)
		{
			if(activeSampleIds.contains(sampleId))
			{
				QColor color = m_tree->GetActiveSystem()->GetSamples()->GetSample(sampleId).GetColor();

				float weight;
				if(m_tree->GetLeafTreatment() == VisualTree::RELATIVE_PROPORITON_TREATMENT)
					weight = m_tree->GetActiveSystem()->GetSamples()->GetSequences()->GetRelativeProportionOfSeqs(leaf->GetId(), sampleId);
				else if(m_tree->GetLeafTreatment() == VisualTree::WEIGHTED_TREATMENT)
					weight = m_tree->GetActiveSystem()->GetSamples()->GetSequences()->GetNumSequences(leaf->GetId(), sampleId);
				else
					weight = uint(m_tree->GetActiveSystem()->GetSamples()->GetSequences()->GetNumSequences(leaf->GetId(), sampleId) >= 1);

				QString colorName = color.name();
				QMap<QString, uint>::const_iterator it = colorMap.find(colorName);
				if(it == colorMap.end())
					colorMap[colorName] = weight;
				else
					colorMap[colorName] = it.value() + weight;

				totalWeight += weight;
			}
		}
	}

	QList<uint> sortedWeighted = colorMap.values();
	qSort(sortedWeighted.begin(), sortedWeighted.end());

	// draw pie chart
	QPen pen(Qt::black);
	pen.setCosmetic(true);
	painter->setPen(pen);
		
	QRectF pieBoundingRect = QRectF(-0.5*size, -0.5*size, size, size);
	uint startAngle = 0;
	if(sortedWeighted.size() > 1)
	{
		// draw wedges of pie chart
		for(int i = 0; i < sortedWeighted.size(); ++i)
		{
			QString colorName = colorMap.key(sortedWeighted.at(i));

			painter->setBrush(QColor(colorName));

			// a complete circle consists of 5760 sections
			uint span = uint((float(sortedWeighted.at(i)) / totalWeight) * 5760 + 0.5);

			if(i == sortedWeighted.size()-1)
				span = 5760 - startAngle;	// simple to account for any rounding errors

			painter->drawPie(pieBoundingRect, startAngle, span);
			startAngle += span;
		}	
	}
	else
	{
		// draw single circle
		painter->setBrush(QColor(colorMap.keys()[0]));
		painter->drawEllipse(-0.5*size, -0.5*size, size, size);
	}

	// draw label
	float radius = 0.5*size;
	if(label != "")
	{
		if(IsLeaf() && m_tree->IsAlignedTips())
		{	
			// draw dashed line
			float length = m_tree->GetLabelStart() - x() - 2*ALIGN_TIP_LINE_OFFSET - radius;
			if(length > ALIGN_TIP_LINE_OFFSET)
			{
				painter->setRenderHint(QPainter::Antialiasing, false);

				QPen pen;
				pen.setCosmetic(true);
				pen.setStyle(Qt::DotLine);
				pen.setColor(QColor(127, 127, 127));
				painter->setPen(pen);

				painter->drawLine(radius + ALIGN_TIP_LINE_OFFSET, 0, m_tree->GetLabelStart() - x() - ALIGN_TIP_LINE_OFFSET, 0);
			}

			// draw label	
			painter->setPen(QPen(m_tree->GetNodeFontColor()));
			painter->drawText(m_tree->GetLabelStart()-x(), -0.5 * m_labelHeight, 
												m_labelWidth, m_labelHeight, Qt::AlignVCenter | Qt::AlignLeft,  label);
		}
		else
		{
			painter->setPen(QPen(m_tree->GetNodeFontColor()));
			painter->drawText(0.5*GetSize() + VisualTree::LABEL_OFFSET, -0.5 * m_labelHeight,	
													m_labelWidth, m_labelHeight, Qt::AlignVCenter | Qt::AlignLeft,  label);
		}
	}
}

/**********************************************************
* Original from the Qwt Widget Library file qwt_symbol.cpp.
* 
* Copyright (C) 1997   Josef Wilgen
* Copyright (C) 2002   Uwe Rathmann
*
* Modified by Donovan Parks, 2011 in order to streamline
* code for use in this project.
***********************************************************/
void VisualNode::DrawSymbol(QPainter *painter, QwtSymbol::Style symbol, const QRectF& r) const
{
    switch(symbol)
    {
        case QwtSymbol::Ellipse:
            painter->drawEllipse(r);
            break;
        case QwtSymbol::Rect:
            painter->drawRect(r);
            break;
        case QwtSymbol::Diamond:
        {
            const int w2 = r.width() / 2;
            const int h2 = r.height() / 2;

            QPolygon pa(4);
            pa.setPoint(0, r.x() + w2, r.y());
            pa.setPoint(1, r.right(), r.y() + h2);
            pa.setPoint(2, r.x() + w2, r.bottom());
            pa.setPoint(3, r.x(), r.y() + h2);
            painter->drawPolygon(pa);
            break;
        }
        case QwtSymbol::Cross:
        {
            const int w2 = r.width() / 2;
            const int h2 = r.height() / 2;

            painter->drawLine(r.x() + w2, r.y(), r.x() + w2, r.bottom());
            painter->drawLine(r.x(), r.y() + h2, r.right(), r.y() + h2);
            break;
        }
        case QwtSymbol::XCross:
        {
            painter->drawLine(r.left(), r.top(), r.right(), r.bottom());
            painter->drawLine(r.left(), r.bottom(), r.right(), r.top());
            break;
        }
        case QwtSymbol::Triangle:
        case QwtSymbol::UTriangle:
        {
            const int w2 = r.width() / 2;

            QPolygon pa(3);
            pa.setPoint(0, r.x() + w2, r.y());
            pa.setPoint(1, r.right(), r.bottom());
            pa.setPoint(2, r.x(), r.bottom());
            painter->drawPolygon(pa);
            break;
        }
        case QwtSymbol::DTriangle:
        {
            const int w2 = r.width() / 2;

            QPolygon pa(3);
            pa.setPoint(0, r.x(), r.y());
            pa.setPoint(1, r.right(), r.y());
            pa.setPoint(2, r.x() + w2, r.bottom());
            painter->drawPolygon(pa);
            break;
        }
        case QwtSymbol::RTriangle:
        {
            const int h2 = r.height() / 2;

            QPolygon pa(3);
            pa.setPoint(0, r.x(), r.y());
            pa.setPoint(1, r.right(), r.y() + h2);
            pa.setPoint(2, r.x(), r.bottom());
            painter->drawPolygon(pa);
            break;
        }
        case QwtSymbol::LTriangle:
        {
            const int h2 = r.height() / 2;

            QPolygon pa(3);
            pa.setPoint(0, r.right(), r.y());
            pa.setPoint(1, r.x(), r.y() + h2);
            pa.setPoint(2, r.right(), r.bottom());
            painter->drawPolygon(pa);
            break;
        }
        case QwtSymbol::HLine:
        {
            const int h2 = r.height() / 2;
            painter->drawLine(r.left(), r.top() + h2, r.right(), r.top() + h2);
            break;
        }
        case QwtSymbol::VLine:
        {
            const int w2 = r.width() / 2;
            painter->drawLine(r.left() + w2, r.top(), r.left() + w2, r.bottom());
            break;
        }
        case QwtSymbol::Star1:
        {
            const double sqrt1_2 = 0.70710678118654752440; /* 1/sqrt(2) */

            const int w2 = r.width() / 2;
            const int h2 = r.height() / 2;
            const int d1  = (int)( (double)w2 * (1.0 - sqrt1_2) );

            painter->drawLine(r.left() + d1, r.top() + d1, r.right() - d1, r.bottom() - d1);
            painter->drawLine(r.left() + d1, r.bottom() - d1, r.right() - d1, r.top() + d1);
            painter->drawLine(r.left() + w2, r.top(), r.left() + w2, r.bottom());
            painter->drawLine(r.left(), r.top() + h2, r.right(), r.top() + h2);
            break;
        }
        case QwtSymbol::Star2:
        {
            const int w = r.width();
            const int side = (int)(((double)r.width() * (1.0 - 0.866025)) /
                2.0);  // 0.866025 = cos(30°)
            const int h4 = r.height() / 4;
            const int h2 = r.height() / 2;
            const int h34 = (r.height() * 3) / 4;

            QPolygon pa(12);
            pa.setPoint(0, r.left() + (w / 2), r.top());
            pa.setPoint(1, r.right() - (side + (w - 2 * side) / 3), r.top() + h4 );
            pa.setPoint(2, r.right() - side, r.top() + h4);
            pa.setPoint(3, r.right() - (side + (w / 2 - side) / 3), r.top() + h2 );
            pa.setPoint(4, r.right() - side, r.top() + h34);
            pa.setPoint(5, r.right() - (side + (w - 2 * side) / 3), r.top() + h34 );
            pa.setPoint(6, r.left() + (w / 2), r.bottom());
            pa.setPoint(7, r.left() + (side + (w - 2 * side) / 3), r.top() + h34 );
            pa.setPoint(8, r.left() + side, r.top() + h34);
            pa.setPoint(9, r.left() + (side + (w / 2 - side) / 3), r.top() + h2 );
            pa.setPoint(10, r.left() + side, r.top() + h4);
            pa.setPoint(11, r.left() + (side + (w - 2 * side) / 3), r.top() + h4 );
            painter->drawPolygon(pa);
            break;
        }
        case QwtSymbol::Hexagon:
        {
            const int w2 = r.width() / 2;
            const int side = (int)(((double)r.width() * (1.0 - 0.866025)) / 2.0);  // 0.866025 = cos(30°)
            const int h4 = r.height() / 4;
            const int h34 = (r.height() * 3) / 4;

            QPolygon pa(6);
            pa.setPoint(0, r.left() + w2, r.top());
            pa.setPoint(1, r.right() - side, r.top() + h4);
            pa.setPoint(2, r.right() - side, r.top() + h34);
            pa.setPoint(3, r.left() + w2, r.bottom());
            pa.setPoint(4, r.left() + side, r.top() + h34);
            pa.setPoint(5, r.left() + side, r.top() + h4);
            painter->drawPolygon(pa);
            break;
        }
        default:;
    }
}

void VisualNode::PaintCollapsedNode(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::Antialiasing, true);

	// set font for rendering text
	QFont font = m_tree->GetNodeFont();
	if(IsBold())
		font.setWeight(QFont::Bold);
	painter->setFont(font);

	// draw selection/highlight outline
	if(m_bTextHighlight)
	{
		painter->setPen(Properties::Inst().GetTextHighlightPen());
		painter->setBrush(Properties::Inst().GetTextHighlightBrush());
		painter->drawRoundedRect(boundingRect(), 3, 3);	
	}
	else if(option->state & QStyle::State_Selected)
	{		
		painter->setPen(Properties::Inst().GetHighlightPen());
		painter->setBrush(Properties::Inst().GetHighlightBrush());
		painter->drawRoundedRect(boundingRect(), 3, 3);
	}

	DrawCollapsedPolygon(painter);
}

float VisualNode::CollapsedLineLength(const CollapsedLineProp& prop) const
{
	Log::Inst().Debug("VisualNode::CollapsedLineLength");

	float length; 

	if(prop.variable == COLLAPSED_BRANCH_LENGTH)
	{
		QList<const VisualNode*> leaves = TreeTools<VisualNode>::GetLeaves(this);	

		float sum = 0;
		float min = (float)INT_MAX;
		float max = (float)-INT_MAX;
		QList<float> nodeX;
		foreach(const VisualNode* leaf, leaves)
		{
			nodeX.append(leaf->x());
			sum += leaf->x();

			if(leaf->x() < min)
				min = leaf->x();

			if(leaf->x() > max)
				max = leaf->x();
		}

		if(prop.statistic == COLLAPSED_MAX)
			length = max - x();
		else if(prop.statistic == COLLAPSED_MIN)
			length = min - x();
		else if(prop.statistic == COLLAPSED_MEAN)
			length = sum / nodeX.size() - x();
		else if(prop.statistic == COLLAPSED_MEDIAN)
		{
			qSort(nodeX.begin(), nodeX.end());
			if((nodeX.size() & 1) == 0) // even
				length = 0.5*(nodeX.at(nodeX.size() / 2 - 1) + nodeX.at(nodeX.size() / 2)) - x();
			else
				length = nodeX.at(nodeX.size() / 2) - x();
		}
		else if(prop.statistic == COLLAPSED_TOTAL)
		{
			QList<const VisualNode*> nodes = TreeTools<VisualNode>::GetNodes(this);	

			float total = 0;
			foreach(const VisualNode* node, nodes)
				total += node->x() - node->GetParent()->x();
	
			length = total;
		}
		else
		{
			Log::Inst().Error( "Unrecognized collapsed node statistic.");
			return 0.0;
		}

		length *= prop.factor;
	}
	else if(prop.variable == COLLAPSED_FIXED)
	{
		length = prop.factor;
		return length;
	}
	else if(prop.variable == COLLAPSED_LEAF_NODE_SPAN)
	{
		QList<const VisualNode*> leaves = TreeTools<VisualNode>::GetLeaves(this);	
		float minY = (float)INT_MAX;
		float maxY = (float)-INT_MAX;
		foreach(const VisualNode* leaf, leaves)
		{
			if(leaf->y() < minY)
					minY = leaf->y();

			if(leaf->y() > maxY)
					maxY = leaf->y();
		}

		length = (maxY-minY)*prop.factor;
	}
	else if(prop.variable == COLLAPSED_SIZE_VAR)
	{
		QList<const VisualNode*> leaves = TreeTools<VisualNode>::GetLeaves(this);	

		QList<float> nodeSizeVar;
		float sum = 0;
		float min = (float)INT_MAX;
		float max = (float)-INT_MAX;
		foreach(const VisualNode* leaf, leaves)
		{
			float size = leaf->GetSize();
			if(size != NO_DISTANCE)
			{
				nodeSizeVar.append(size);
				sum += size;

				if(size < min)
					min = size;

				if(size > max)
					max = size;
			}
		}

		if(prop.statistic == COLLAPSED_MAX)
			length = max;
		else if(prop.statistic == COLLAPSED_MIN)
			length = min;
		else if(prop.statistic == COLLAPSED_MEAN)
			length = sum / nodeSizeVar.size();
		else if(prop.statistic == COLLAPSED_MEDIAN)
		{
			qSort(nodeSizeVar.begin(), nodeSizeVar.end());
			if((nodeSizeVar.size() & 1) == 0) // even
				length = 0.5*(nodeSizeVar.at(nodeSizeVar.size() / 2 - 1) + nodeSizeVar.at(nodeSizeVar.size() / 2));
			else
				length = nodeSizeVar.at(nodeSizeVar.size() / 2);
		}
		else if(prop.statistic == COLLAPSED_TOTAL)
		{
			QList<const VisualNode*> nodes = TreeTools<VisualNode>::GetNodes(this);	

			float total = 0;
			foreach(const VisualNode* node, nodes)
			{
				float size = node->GetSize();
				if(size != NO_DISTANCE)
					total += size;
			}
	
			length = total;
		}
		else
		{
			Log::Inst().Error( "Unrecognized collapsed node statistic.");
			return 0.0;
		}

		length *= prop.factor;
	}
	else if(prop.variable == COLLAPSED_ABUNDANCE)
	{
		float numSeqs;
		if(m_tree->GetLeafTreatment() == VisualTree::RELATIVE_PROPORITON_TREATMENT)
			numSeqs = GetRelativeProportionOfSeqs();
		else if(m_tree->GetLeafTreatment() == VisualTree::WEIGHTED_TREATMENT)
			numSeqs = GetWeightedNumberOfSeqs();
		else
			numSeqs = GetNumberOfSeqs();

		float relativeAbundance = float(numSeqs) / m_tree->GetMaxAbundance();
		length = relativeAbundance*m_tree->GetMaxAbundanceSize();
	}
	else if(prop.variable == COLLAPSED_NONE)
	{
		length = 0;
	}
	else
	{
		Log::Inst().Error( "Unrecognized collapsed node variable.");
		return 0.0;
	}

	// make sure extents are obeyed
	if(length < prop.minSize)
		length = prop.minSize;
	if(length > prop.maxSize)
		length = prop.maxSize; 

	return length;
}

void VisualNode::CollapsedNodeLineLengths(float& lengthBL, float& lengthML, float& lengthTL, float& height) const
{	
	CollapsedProp prop;
	if(IsLeaf())
	{
		prop = m_tree->GetCollapsedLeafProperties();
		prop.heightLine = CollapsedLineProp(COLLAPSED_FIXED, COLLAPSED_TOTAL, m_diameter, 0, 0);

		lengthBL = lengthML = lengthTL = CollapsedLineLength(prop.bottomLine);
		height = CollapsedLineLength(prop.heightLine);
	}
	else
	{
		prop = m_tree->GetCollapsedNodeProperties();

		lengthBL = CollapsedLineLength(prop.bottomLine);
		lengthML = CollapsedLineLength(prop.middleLine);
		lengthTL = CollapsedLineLength(prop.topLine);
		height = CollapsedLineLength(prop.heightLine);
	}

	if(prop.middleLine.variable == COLLAPSED_NONE)
	{
		// middle line should be along edge from top and bottom lines
		float run = lengthTL-lengthBL;
		if(run == 0)
			lengthML = lengthBL;
		else
		{
			float slope = run / height;
			lengthML = lengthBL + 0.5*height*slope;
		}
	}
}

void VisualNode::DrawCollapsedPolygon(QPainter* painter) const
{
	Log::Inst().Debug("VisualNode::DrawCollapsedPolygon()");

	float lengthBL, lengthML, lengthTL, height;
	CollapsedNodeLineLengths(lengthBL, lengthML, lengthTL, height);

	VisualNode::CollapsedProp prop;
	if(IsLeaf())
		prop = m_tree->GetCollapsedLeafProperties();
	else
		prop = m_tree->GetCollapsedNodeProperties();

	// define collapse node polygons
	QPolygonF topPolygon, fullPolygon;
	float offset = 0.5*m_diameter;
	if(prop.shape == COLLAPSED_TRIANGULAR)
	{
		QVector<QPointF> topPoints(3);
		topPoints[0] = QPointF(-offset, 0);
		topPoints[1] = QPointF(lengthTL-offset, -0.5*height);
		topPoints[2] = QPointF(lengthML-offset, 0);

		topPolygon = QPolygonF(topPoints);

		QVector<QPointF> allPoints(4);
		allPoints[0] = QPointF(-offset, 0);
		allPoints[1] = QPointF(lengthTL-offset, -0.5*height);
		allPoints[2] = QPointF(lengthML-offset, 0);
		allPoints[3] = QPointF(lengthBL-offset, 0.5*height);

		fullPolygon = QPolygonF(allPoints);
	}
	else if(prop.shape == COLLAPSED_RECTANGULAR)
	{
		QVector<QPointF> topPoints(4);
		topPoints[0] = QPointF(-offset, 0);
		topPoints[1] = QPointF(-offset, -0.5*height);
		topPoints[2] = QPointF(lengthTL-offset, -0.5*height);
		topPoints[3] = QPointF(lengthML-offset, 0);

		topPolygon = QPolygonF(topPoints);

		QVector<QPointF> allPoints(6);
		allPoints[0] = QPointF(-offset, 0);
		allPoints[1] = QPointF(-offset, -0.5*height);
		allPoints[2] = QPointF(lengthTL-offset, -0.5*height);
		allPoints[3] = QPointF(lengthML-offset, 0);
		allPoints[4] = QPointF(lengthBL-offset, 0.5*height);
		allPoints[5] = QPointF(-offset, 0.5*height);

		fullPolygon = QPolygonF(allPoints);
	}

	// setup gradient
	QLinearGradient gradient;
	gradient.setSpread(QGradient::PadSpread);
	if(prop.gradientFill == COLLAPSED_FULL)
	{
		gradient.setStart(-offset, 0);
		gradient.setFinalStop(qMax<float>(lengthBL-offset, qMax<float>(lengthML-offset, lengthTL-offset)), 0);
	}
	else
	{
		gradient.setStart(-offset, -0.25*height);
		gradient.setFinalStop(qMax<float>(lengthML-offset, lengthTL-offset), -0.25*height);
	}

	// get number of times each color occurs in leaf nodes
	QMap<QString, float> gradientMap;
	float totalWeight = 0;
	m_tree->GetCollapsedNodeGradient(this, gradientMap, totalWeight);

	// create gradient with colors in ascending order of frequency
	QList<float> values = gradientMap.values();
	qSort(values.begin(), values.end());
			
	if(prop.gradientStyle == COLLAPSED_GRADIENT_CONTINUOUS)
	{		
		float prop = 0.0;
		for(int i = 0; i < values.size(); ++i)
		{
			QString colorName = gradientMap.key(values.at(i));
			gradientMap.remove(colorName);

			if(i == 0)
				gradient.setColorAt(0, colorName);
			else if(i == values.size()-1)
				gradient.setColorAt(1, colorName);
			else
				gradient.setColorAt(prop, colorName);

			prop += values.at(i) / totalWeight;
		}
	}
	else if(prop.gradientStyle == COLLAPSED_GRADIENT_DISCRETE)
	{
		QString prevColor;
		float prop = 0.0;
		for(int i = 0; i < values.size(); ++i)
		{
			QString colorName = gradientMap.key(values.at(i));
			gradientMap.remove(colorName);

			if(i == 0)
				gradient.setColorAt(0, colorName);
			else if(i == values.size()-1)
			{
				gradient.setColorAt(prop - 1e-6, prevColor);
				gradient.setColorAt(prop, colorName);
				gradient.setColorAt(1, colorName);
			}
			else
			{
				gradient.setColorAt(prop - 1e-6, prevColor);
				gradient.setColorAt(prop, colorName);
			}

			prop += values.at(i) / totalWeight;
			prevColor = colorName;
		}
	}
	else if(prop.gradientStyle == COLLAPSED_GRADIENT_SINGLE_COLOR)
	{
		gradient.setColorAt(0, prop.gradientColor);
		gradient.setColorAt(1, prop.gradientColor);
	}

	// draw collapsed node
	painter->setRenderHint(QPainter::Antialiasing, true);
	QPen pen;
	pen.setCosmetic(true);
	painter->setPen(pen);

	if(prop.gradientFill == COLLAPSED_FULL)
	{
		QBrush brush(gradient);
		painter->setBrush(brush);
		painter->drawConvexPolygon(fullPolygon);
	}
	else	// COLLAPSED_TOP_HALF
	{
		painter->setBrush(QBrush(prop.gradientColor));
		painter->drawConvexPolygon(fullPolygon);

		painter->setBrush(gradient);
		painter->drawConvexPolygon(topPolygon);
	}

	// draw label
	QString label = GetLabel();
	float length = qMax<float>(lengthBL, qMax<float>(lengthML, lengthTL));
	if(label != "")
	{
		if(m_tree->IsAlignedTips())
		{	
			// draw dashed line
			float dashedLineLength = m_tree->GetLabelStart() - (x() - offset + length) - 2*ALIGN_TIP_LINE_OFFSET;
			if(dashedLineLength > ALIGN_TIP_LINE_OFFSET)
			{
				painter->setRenderHint(QPainter::Antialiasing, false);

				QPen pen;
				pen.setCosmetic(true);
				pen.setStyle(Qt::DotLine);
				pen.setColor(QColor(127, 127, 127));
				painter->setPen(pen);

				painter->drawLine(-offset + length + ALIGN_TIP_LINE_OFFSET, 0, m_tree->GetLabelStart() - x() - ALIGN_TIP_LINE_OFFSET, 0);
			}

			// draw label	
			painter->setPen(QPen(m_tree->GetNodeFontColor()));
			painter->drawText(m_tree->GetLabelStart() - x(), -0.5 * m_labelHeight, 
												m_labelWidth, m_labelHeight, 
												Qt::AlignVCenter | Qt::AlignLeft,  label);
		}
		else
		{
			painter->setPen(QPen(m_tree->GetNodeFontColor()));
			painter->drawText(-offset + length + VisualTree::LABEL_OFFSET, -0.5 * m_labelHeight,	
												m_labelWidth, m_labelHeight, 
												Qt::AlignVCenter | Qt::AlignLeft,  label);
		}
	}
}

void VisualNode::SetSize(qreal diameter)
{
	prepareGeometryChange();
	m_diameter = diameter;
	update();
}

void VisualNode::SetColor(const QColor& color)
{
	m_color = color;
	update();
}

void VisualNode::SetShape(const QwtSymbol::Style& shape)
{
	m_shape = shape;
	update();
}

void VisualNode::SetTextHighlight(bool highlight) 
{ 
	m_bTextHighlight = highlight; 
	update(); 
}

void VisualNode::SetCollapsedLabel(const QString& label)
{
	m_collapsedLabel = label;
	LabelChanged();
}

void VisualNode::LabelChanged()
{
	m_label = "";
	if(m_tree->GetNodeLabelType() == ASSIGNED_LABEL || 
			m_tree->GetNodeLabelType() == ASSIGNED_LEAF_LABEL ||
			m_tree->GetNodeLabelType() == SUPPORT_LABEL ||
			m_tree->GetNodeLabelType() == CONSISTENCY_INDEX_LABEL ||
			m_tree->GetNodeLabelType() == HEIGHT_LABEL ||
			m_tree->GetNodeLabelType() == DISTANCE_TO_CLOSEST_LEAF_LABEL ||
			m_tree->GetNodeLabelType() == DISTANCE_TO_FURTHEST_LEAF_LABEL)
	{
		if(m_tree->GetNodeLabelType() == ASSIGNED_LEAF_LABEL && !IsLeaf() && !m_bCollapsed)
		{
			m_label = "";
		}
		else if(IsLeaf() && !m_tree->GetCollapsedLeafProperties().bAbundanceInLabel)
		{
			float numSeqs = 0, numSelected = 0;
			m_tree->GetNumberOfSelectedSeqs(this, numSeqs, numSelected);
			if(numSelected > 0)
				SetBold(true);
			else
				SetBold(false);

			m_label = GetName();
		}
		else
		{	
			float numSeqs = 0, numSelected = 0;
			m_tree->GetNumberOfSelectedSeqs(this, numSeqs, numSelected);
			if(numSelected > 0)
				SetBold(true);
			else
				SetBold(false);

			if(IsLeaf())
				m_label = GetName();
			else if(m_tree->GetCollapsedNodeProperties().bShowLabels)
				m_label = m_collapsedLabel;

			if((IsLeaf() && m_tree->GetCollapsedLeafProperties().bAbundanceInLabel)
					|| (!IsLeaf() && m_tree->GetCollapsedNodeProperties().bAbundanceInLabel))
			{
				if(m_label != "")
					m_label += " ";

				m_label += "(" + QString::number(numSeqs, 'g', 2) + ")";

				if(numSelected != 0)
				{
					if(m_label != "")
						m_label += " ";

					m_label += "[" + QString::number(numSelected, 'g', 2) + "]";
				}
			}
		}
	}

	if(m_tree->GetNodeLabelType() == DEPTH_LABEL)
		m_label = QString::number(GetDepth(), 'g', 3);
	else if(m_tree->GetNodeLabelType() == HEIGHT_LABEL && !IsLeaf())
		m_label = QString::number(GetHeight(), 'g', 3);
	else if(m_tree->GetNodeLabelType() == DISTANCE_TO_ROOT_LABEL)
		m_label = QString::number(GetDistanceToRoot(), 'g', 3);
	else if(m_tree->GetNodeLabelType() == DISTANCE_TO_CLOSEST_LEAF_LABEL && !IsLeaf())
		m_label = QString::number(GetDistanceToClosestLeafNode(), 'g', 3);
	else if(m_tree->GetNodeLabelType() == DISTANCE_TO_FURTHEST_LEAF_LABEL && !IsLeaf())
		m_label = QString::number(GetDistanceToFurthestLeafNode(), 'g', 3);
	else if(m_tree->GetNodeLabelType() == DISTANCE_TO_LEAVES_LABEL)
		m_label = QString::number(TreeTools<VisualNode>::GetAvgDistToLeafNodes(this), 'g', 3);
	else if(m_tree->GetNodeLabelType() == CONSISTENCY_INDEX_LABEL && !IsLeaf())
		m_label = QString::number(GetParsimonyData()->consistencyIndex, 'g', 3);
	else if(m_tree->GetNodeLabelType() == SUPPORT_LABEL && !IsLeaf())
		m_label = QString::number(GetSupport());

	// append category information to label
	if(IsLeaf())
	{
		// color category info
		QString categoryInfo = "";
		if(m_tree->GetShowColorCategory())
			categoryInfo = m_tree->GetCategoryInfo(this, m_tree->GetLegends()->GetColorField());

		if(!categoryInfo.isEmpty())
		{
			if(!m_label.isEmpty())
				m_label += " | ";
			m_label += categoryInfo;
		}

		// shape category info
		categoryInfo = "";
		if(m_tree->GetShowShapeCategory())
			categoryInfo = m_tree->GetCategoryInfo(this, m_tree->GetLegends()->GetShapeField());

		if(!categoryInfo.isEmpty())
		{
			if(!m_label.isEmpty())
				m_label += " | ";
			m_label += categoryInfo;
		}

		// size category info
		categoryInfo = "";
		if(m_tree->GetShowSizeCategory())
			categoryInfo = m_tree->GetCategoryInfo(this, m_tree->GetLegends()->GetSizeField());

		if(!categoryInfo.isEmpty())
		{
			if(!m_label.isEmpty())
				m_label += " | ";
			m_label += categoryInfo;
		}
	}

	FontChanged();
}

void VisualNode::FontChanged()
{
	prepareGeometryChange();

	if(m_label != "")
	{
		QFont font = m_tree->GetNodeFont();
		if(IsBold())
			font.setWeight(QFont::Bold);

		QFontMetrics fontMetrics(font);
		m_labelHeight = fontMetrics.height();
		m_labelWidth = fontMetrics.width(m_label);
	}
	else
	{
		m_labelHeight = 1;
		m_labelWidth = 1;
	}

	update();
}

void VisualNode::ToggleCollapsedInternal()
{
	m_bCollapsed = !m_bCollapsed;
	SetCollapsedInternal(m_bCollapsed);
}

void VisualNode::SetCollapsedLeaf(bool bCollapsed)
{
	if(!IsLeaf())
		return;
	
	m_bCollapsed = bCollapsed;

	LabelChanged();

	prepareGeometryChange();
	update();
}

void VisualNode::SetCollapsedInternal(bool bCollapsed)
{
	if(IsLeaf())
		return;

	m_bCollapsed = bCollapsed;

	foreach(VisualBranch* branch, m_branches)
		branch->setVisible(!m_bCollapsed);
	
	QStack<VisualNode*> stack;
	for(uint i = 0; i < GetNumberOfChildren(); ++i)
		stack.push(GetChild(i));

	while(!stack.isEmpty())
	{
		VisualNode* curNode = stack.pop();
		curNode->setVisible(!m_bCollapsed);
		curNode->SetSelected(m_bCollapsed);

		foreach(VisualBranch* branch, curNode->GetBranches())
			branch->setVisible(!curNode->IsCollapsed() && curNode->isVisible());
		
		if(!curNode->IsCollapsed())
		{
			for(uint i = 0; i < curNode->GetNumberOfChildren(); ++i)
				stack.push(curNode->GetChild(i));
		}
	}

	LabelChanged();

	prepareGeometryChange();
	update();
}

void VisualNode::SetTree(VisualTree* tree) 
{
	m_tree = tree; 
	LabelChanged();
}

void VisualNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	m_tree->CollapseSelectedNode(); 
}

void VisualNode::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	m_tree->ShowContextMenu(event, this);
}

void VisualNode::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
	QString tooltip;

	if(GetName() != "")
		tooltip += GetName() + "\n\n";

	if(GetSupport() != VisualNode::NO_DISTANCE)
		tooltip += "Support: " + QString::number(GetSupport()) + "\n\n";

	tooltip += "Number of children: " + QString::number(GetNumberOfChildren()) + "\n";
	tooltip += "Number of leaves in subtree: " + QString::number(GetNumberOfLeaves()) + "\n\n";

	tooltip += "Depth: " + QString::number(GetDepth()) + "\n";
	tooltip += "Height: " + QString::number(GetHeight()) + "\n\n";

	tooltip += "Distance to parent: " + QString::number(GetDistanceToParent()) + "\n";
	tooltip += "Distance to root: " + QString::number(GetDistanceToRoot()) + "\n";
	tooltip += "Distance to closest leaf node: " + QString::number(GetDistanceToClosestLeafNode()) + "\n";
	tooltip += "Distance to furthest leaf node: " + QString::number(GetDistanceToFurthestLeafNode()) + "\n";
	tooltip += "Branch length of subtree: " + QString::number(GetTotalBranchLength()) + "\n\n";

	if(IsActiveSet())
		tooltip += "Within active set: true";
	else
		tooltip += "Within active set: false";

	if(m_parsimonyData)
	{
		tooltip += "\n\n";
		tooltip += ParsimonyData::field + " consistency index: " + QString::number(m_parsimonyData->GetConsistencyIndex()) + "\n";
		tooltip += ParsimonyData::field + " parsimony score: " + QString::number(m_parsimonyData->GetNodeScore()) + "\n";
		
		tooltip += "Parsimonious characters: \n";

		QStringList parsimoniousCharacters = m_parsimonyData->parsimoniousCharacters.toList();
		qSort(parsimoniousCharacters.begin(), parsimoniousCharacters.end());

		uint index = 0;
		foreach(const QString& value, parsimoniousCharacters)
		{
			tooltip += value;

			if(index != parsimoniousCharacters.size()-1)
				tooltip += "\n";

			index++;
		}
	}

	m_tree->SetTreeInspectorText(tooltip);

	setToolTip(tooltip);
	update();
}

void VisualNode::SetSubtreeAsActive(bool bOnlySubtree)
{
	if(bOnlySubtree)
	{
		// *** Put only nodes in this subtree in the active set

		// set all nodes to be inactive
		QList<VisualNode*> nodes = m_tree->GetTree()->GetNodes();
		foreach(VisualNode* node, nodes)
			node->SetActiveSet(false);

		// place all nodes in subtree rooted as this node in the active set
		QList<VisualNode*> activeNodes = TreeTools<VisualNode>::GetNodes(this);
		foreach(VisualNode* node, activeNodes)
			node->SetActiveSet(true);

		m_tree->SetActiveSubtree(this);
	}
	else
	{
		// *** Put all nodes in the active set
		QList<VisualNode*> nodes = m_tree->GetTree()->GetNodes();
		foreach(VisualNode* node, nodes)
			node->SetActiveSet(true);

		m_tree->SetActiveSubtree(NULL);
	}
}

void VisualNode::SetSelected(bool state, bool bUpdateGUI) 
{ 
	m_bSelected = state; 

	if(bUpdateGUI)
		setSelected(state); 
}

void VisualNode::SelectSubtree()
{
	QList<VisualNode*> nodes = TreeTools<VisualNode>::GetNodes(this);
	foreach(VisualNode* node, nodes)
	{
		if(node->IsLeaf() || node->IsCollapsed())
			node->SetSelected(true);
	}
}

void VisualNode::UnselectSubtree()
{
	QList<VisualNode*> nodes = TreeTools<VisualNode>::GetNodes(this);
	foreach(VisualNode* node, nodes)
		node->SetSelected(false);
}

QVariant VisualNode::itemChange(GraphicsItemChange change, const QVariant & value)
{
	if(change == ItemSelectedHasChanged && scene() && m_tree->IsProcessSelectionUpdates())
	{
		bool bSelected = value.toBool();
		if(IsLeaf())
			m_bSelected = bSelected;

		if(IsCollapsed())
		{
			QList<VisualNode*> leaves = TreeTools<VisualNode>::GetLeaves(this);
			foreach(VisualNode* leaf, leaves)
				leaf->SetSelected(bSelected, false);

			LabelChanged();
		}

		m_tree->UpdateSelectedNodes();
	}

	return QGraphicsItem::itemChange(change, value);
}