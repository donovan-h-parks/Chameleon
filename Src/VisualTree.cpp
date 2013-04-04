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

#include "VisualTree.hpp"

#include "Properties.hpp"

#include "Tree.hpp"
#include "NewickIO.hpp"
#include "VisualNode.hpp"
#include "VisualBranch.hpp"

#include "System.hpp"
#include "Legends.hpp"

#include "ParsimonyCalculator.hpp"

VisualTree::VisualTree(LegendsPtr legends)
:		m_legends(legends), m_bVisible(false), 
		m_dummyRootParent(new VisualNode(Tree<VisualNode>::ROOT_ID, "dummy root")), 
		m_leafSpacing(0), m_viewportWidth(0), m_treeWidth(0), m_treeHeight(0),
		m_layoutStyle(RECTANGULAR_LAYOUT), m_branchStyle(PHYLOGRAM_BRANCHES),
		m_bAlignedTips(true), m_nodeLabelType(VisualNode::ASSIGNED_LEAF_LABEL), 
		m_branchLabelType(VisualBranch::NO_LABEL), m_scene(new QGraphicsScene()),		
		m_branchColorStyle(VisualBranch::PROPOGATE_DISCRETE_COLOR),m_nodeColorStyle(VisualNode::PROPOGATE_DISCRETE_COLOR), 
		m_nodeShapeStyle(VisualNode::SINGLE_SHAPE),	m_nodeSizeStyle(VisualNode::LEAVES_ONLY_SIZE), 
		m_tree(0), m_parsimonyCalculator(new ParsimonyCalculator()), m_leafTreatment(DEFAULT_TREATMENT),
		m_abundanceStyle(ABUNDANCE_NONE), m_abundanceMinSize(10), m_abundanceMaxSize(100),
		m_bShowColorCategory(false), m_bShowShapeCategory(false), m_bShowSizeCategory(false)
{
	m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);

	m_collapsedLeafProperties.bAbundanceInLabel = (m_abundanceStyle != ABUNDANCE_NONE);
}

void VisualTree::SetActiveSystem(SystemPtr system)
{
	m_activeSystem = system;
}

void VisualTree::SetTree(Tree<VisualNode>* tree)
{
	Log::Inst().Debug("Entering VisualTree::SetTree()");

	QApplication::setOverrideCursor(Qt::WaitCursor);

	m_bVisible = false;

	m_tree = tree;

	// Remove all items from the scene
	m_scene->clear();
	
	tree->CalculateStatistics(m_activeSystem->GetSamples());

	m_visualScale = new VisualScale();
	m_scene->addItem(m_visualScale);

	m_visualAxis = new VisualAxis();
	m_scene->addItem(m_visualAxis);

	m_activeSetHighlighter = new VisualSubtreeHighlighter();
	m_activeSetHighlighter->SetVisibility(false);
	m_scene->addItem(m_activeSetHighlighter);

	m_branches.resize(tree->GetNumberOfNodes());
	for(int i = 0; i < m_branches.size(); ++i)
	{
		m_branches[i] = new VisualBranch();
		m_scene->addItem(m_branches[i]);
	}

	// Assign visual branches to nodes
	ConnectBranchesToNodes();

	QList<VisualNode*> nodes = tree->GetNodes();
	foreach(VisualNode* node, nodes)
		m_scene->addItem(node);	

	// Point tree elements to the tree
	for(int i = 0; i < m_branches.size(); ++i)
		m_branches[i]->SetTree(this);

	foreach(VisualNode* node, nodes)
		node->SetTree(this);	

	// Calculate reasonable root depth
	emit RootLengthChanged(tree->GetDistanceToFurthestLeafNode() * 0.05);	
	
	// Color branches and nodes according to current style
	emit NodeColorStyleChanged();
	emit NodeSizeStyleChanged();
	emit NodeShapeStyleChanged();
	emit BranchColorStyleChanged();

	emit AbundanceStyleChanged();
	
	emit NewTreeSet();

	// Layout tree	
	SetVisible(true);

	// Add node labels to text searcher
	m_textSearch.clear();
	foreach(VisualNode* node, nodes)
	{
		if(node->GetName() != "")
			m_textSearch.add(node->GetName(), node->GetId());
	}

	// entire tree is active when first set
	m_activeSubtreeRoot = tree->GetRootNode();

	CalculateAbundanceExtents();

	QApplication::restoreOverrideCursor();

	Log::Inst().Debug("Leaving VisualTree::SetTree(...)");
}

void VisualTree::ConnectBranchesToNodes()
{
	Log::Inst().Debug("VisualTree::ConnectBranchesToNodes()");

	// make all branches visible
	foreach(VisualBranch* branch, m_branches)
		branch->setVisible(true);

	// initialize dummy parent to root
	m_dummyRootParent->setPos(Properties::Inst().GetViewportBorderSize(), 0);
	m_dummyRootParent->setFlag(QGraphicsItem::ItemIsSelectable, false);
	m_dummyRootParent->RemoveChildren();
	m_dummyRootParent->AddChild(GetTree()->GetRootNode());
	m_dummyRootParent->SetParent(NULL);
	m_dummyRootParent->ClearBranches();
	
	// assign branches to noes	
	int index = 0;
	QStack<VisualNode*> stack;	
	stack.push(GetTree()->GetRootNode());
	while(!stack.isEmpty())
	{
		VisualNode* curNode = stack.pop();
		curNode->ClearBranches();
		curNode->SetTree(this);

		// add children to queue
		for(uint i = 0; i < curNode->GetNumberOfChildren(); ++i)
			stack.push(curNode->GetChild(i));

		// setup edge for node
		m_branches[index]->SetSource(curNode->GetParent());
		m_branches[index]->SetDest(curNode);

		index++;
	}

	// hide branches in collapsed nodes
	foreach(VisualNode* node, m_tree->GetNodes())
	{
		if(node->IsCollapsed())
		{
			foreach(VisualBranch* branch, node->GetBranches())
				branch->setVisible(false);
		}
	}
}

void VisualTree::SetLayoutStyle(LAYOUT_STYLE layoutStyle)
{
	Log::Inst().Debug("VisualTree::SetLayoutStyle()");

	if(m_layoutStyle == layoutStyle)
		return;

	m_layoutStyle = layoutStyle;
}

void VisualTree::SetBranchStyle(BRANCH_STYLE branchStyle)
{
	Log::Inst().Debug("VisualTree::SetBranchStyle()");

	m_branchStyle = branchStyle;

	Layout();
}

void VisualTree::SetLeafTreatment(LEAF_TREATMENT leafTreatment)
{
	Log::Inst().Debug("VisualTree::SetLeafTreatment()");

	m_leafTreatment = leafTreatment;

	if(m_nodeColorStyle == VisualNode::PROPOGATE_WEIGHTED_COLOR)
		emit NodeColorStyleChanged();
	else if(m_nodeSizeStyle == VisualNode::PROPOGATE_WEIGHTED_SIZE)
		emit NodeSizeStyleChanged();
	else if(m_branchColorStyle == VisualBranch::PROPOGATE_WEIGHTED_COLOR)
		emit BranchColorStyleChanged();

	foreach(VisualNode* node, m_tree->GetNodes())
	{
		if(node->IsCollapsed())
			node->LabelChanged();
	}

	CalculateAbundanceExtents();

	Layout();
}

void VisualTree::SetAbundanceStyle(ABUNDANCE_STYLE abundanceStyle, uint minSize, uint maxSize)
{
	Log::Inst().Debug("VisualTree::SetAbundanceStyle()");

	m_abundanceMinSize = minSize;
	m_abundanceMaxSize = maxSize;

	// set collapsed leaf properties
	VisualNode::CollapsedLineProp lineProp;

	lineProp.variable = VisualNode::COLLAPSED_ABUNDANCE;
	lineProp.factor = 1.0;
	lineProp.minSize = m_abundanceMinSize;
	lineProp.maxSize = m_abundanceMaxSize;
	
	m_collapsedLeafProperties.shape = VisualNode::COLLAPSED_RECTANGULAR;
	m_collapsedLeafProperties.bShowLabels = true;
	m_collapsedLeafProperties.bAbundanceInLabel = (abundanceStyle != ABUNDANCE_NONE);

	m_collapsedLeafProperties.topLine = lineProp;
	m_collapsedLeafProperties.middleLine = lineProp;
	m_collapsedLeafProperties.bottomLine = lineProp;
	m_collapsedLeafProperties.heightLine = lineProp;

	m_collapsedLeafProperties.gradientStyle = VisualNode::COLLAPSED_GRADIENT_DISCRETE;
	m_collapsedLeafProperties.gradientFill = VisualNode::COLLAPSED_FULL;

	if(m_abundanceStyle != abundanceStyle)
	{
		if(m_abundanceStyle == ABUNDANCE_COLLAPSED_LEAVES || abundanceStyle == ABUNDANCE_COLLAPSED_LEAVES)
		{
			// if going from/to a collapsed leaf node style than we need to set the 
			// collapsed state of  all leaf nodes
			foreach(VisualNode* leaf, m_tree->GetLeaves())
			{
				if(abundanceStyle == ABUNDANCE_COLLAPSED_LEAVES)
					leaf->SetCollapsedLeaf(true);
				else
					leaf->SetCollapsedLeaf(false);
			}
		}
		else
		{
			// we just need to update the leaves to reflect the new style
			foreach(VisualNode* leaf, m_tree->GetLeaves())
				leaf->LabelChanged();
		}
	}

	m_abundanceStyle = abundanceStyle;
	
	Layout();
}

void VisualTree::CalculateAbundanceExtents()
{
	// calculate minimum and maximum abundance at any leaf node in tree
	m_abundanceMax = 0;
	m_abundanceMin = (float)INT_MAX;
	foreach(VisualNode* node, m_tree->GetNodes())
	{
		if(node->IsLeaf() || node->IsCollapsed())
		{
			float weight;
			if(m_leafTreatment == VisualTree::RELATIVE_PROPORITON_TREATMENT)
				weight = node->GetRelativeProportionOfSeqs();
			else if(m_leafTreatment == VisualTree::WEIGHTED_TREATMENT)
				weight = node->GetWeightedNumberOfSeqs();
			else
				weight = node->GetNumberOfSeqs();

			if(weight > m_abundanceMax)
				m_abundanceMax = weight;

			if(weight < m_abundanceMin)
				m_abundanceMin = weight;
		}
	}
}

void VisualTree::Layout()
{
	Log::Inst().Debug("VisualTree::Layout()");

	if(!IsVisible())
		return;

	m_viewportWidth = m_scene->views()[0]->viewport()->width();
	m_viewportHeight = m_scene->views()[0]->viewport()->height();

	if(m_layoutStyle == RECTANGULAR_LAYOUT)
		RectangularLayout();

	if(m_visualScale->IsAutomaticScale())
		SetAutomaticScale(true);

	m_activeSetHighlighter->UpdateSubtreeExtents();
}

void VisualTree::RectangularLayout()
{
	Log::Inst().Debug("VisualTree::RectangularLayout()");

	// set distance from root for all nodes
	LayoutDistanceFromRoot(m_rootLength);

	// extents of tree
	m_treeWidth = FindTreeWidthAndBranchScale();

	// scale x-position of nodes to within screen dimensions		
	QStack<VisualNode*> stack;	
	stack.push(GetTree()->GetRootNode());
	while(!stack.isEmpty())
	{
		VisualNode* curNode = stack.pop();

		// add children to queue
		for(uint i = 0; i < curNode->GetNumberOfChildren(); ++i)
			stack.push(curNode->GetChild(i));

		// position node
		float x = Properties::Inst().GetViewportBorderSize() + curNode->x()*m_visualScale->GetPixelsPerUnitBranchLength();
		curNode->setPos(x, curNode->y());
		curNode->update();
		curNode->GetParentBranch()->NodeMoved();
	}

	// set y-position of deepest uncollapsed nodes
	m_treeHeight = LayoutTipNodes();

	// set y-position of internal nodes
	LayoutInternalNodes(GetTree()->GetRootNode());
	m_dummyRootParent->setY(GetTree()->GetRootNode()->y());

	m_scene->setSceneRect(0, -Properties::Inst().GetViewportBorderSize(), 
													m_viewportWidth, m_treeHeight+2*Properties::Inst().GetViewportBorderSize());

	// make sure scale is always within the scene extents
	if(m_visualScale->x() < 0)
		m_visualScale->setX(0);
	else if(m_visualScale->x() > m_scene->sceneRect().width())
		m_visualScale->setX(m_scene->sceneRect().width() - m_visualScale->boundingRect().width());

	if(m_visualScale->y() < 0)
		m_visualScale->setY(0);
	else if(m_visualScale->y() > m_scene->sceneRect().height())
		m_visualScale->setY(m_scene->sceneRect().height()-m_visualScale->boundingRect().height());

	// set position of visual axis
	m_visualAxis->SetHeight(m_treeHeight);
	m_visualAxis->setX(m_viewportWidth - m_visualAxis->boundingRect().width() - Properties::Inst().GetViewportBorderSize());
	m_visualAxis->setY(0);
}

void VisualTree::LayoutDistanceFromRoot(float rootDepth)
{
	Log::Inst().Debug("VisualTree::LayoutDistanceFromRoot()");

	float maxDepth = 0;
	QList<VisualNode*> nodes = GetTree()->GetNodes();
	for(int i = 0; i < nodes.size(); ++i)
	{
		VisualNode* curNode = nodes[i];

		// set x-position of node
		if(m_branchStyle == PHYLOGRAM_BRANCHES)
			curNode->setX(curNode->GetDistanceToRoot() + rootDepth);
		else if(!curNode->IsLeaf() || m_branchStyle == EQUAL_BRANCHES)
			curNode->setX(curNode->GetDepth() + 1);
		else if(m_branchStyle == CLADOGRAM_BRANCHES)
			curNode->setX(GetTree()->GetTreeHeight() + 1);
	}
}

float VisualTree::LayoutTipNodes()
{
	Log::Inst().Debug("VisualTree::LayoutTipNodes()");

	QList<VisualNode*> tipNodes;
	FindTipNodes(GetTree()->GetRootNode(), tipNodes);
	
	float bottomBound = 0;
	foreach(VisualNode* node, tipNodes)
	{		
		QRectF extents = node->boundingRect();
		node->setY(bottomBound + m_leafSpacing + 0.5*extents.height());
		bottomBound += 2*m_leafSpacing + extents.height();
	}

	return bottomBound;
}

void VisualTree::FindTipNodes(VisualNode* node, QList<VisualNode*>& tipNodes)
{
	if(node->IsLeaf() || node->IsCollapsed())
	{
		tipNodes.push_back(node);
		return;
	}

	for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
		FindTipNodes(node->GetChild(i), tipNodes);
}

void VisualTree::LayoutInternalNodes(VisualNode* node)
{
	if(!node->IsCollapsed() && !node->IsLeaf())
	{
		for(uint i = 0; i < node->GetNumberOfChildren(); ++i)
			LayoutInternalNodes(node->GetChild(i));

		node->setY(0.5 * (node->GetChild(0)->y() + node->GetChild(node->GetNumberOfChildren()-1)->y()));
	}	
}

int VisualTree::FindTreeWidthAndBranchScale()
{
	Log::Inst().Debug("VisualTree::FindTreeWidthAndBranchScale()");

	// calculate width of tree in pixels taking into account the width of labels, 
	// the desired border size, and the size of any collapsed nodes
	QList<VisualNode*> tipNodes;
	FindTipNodes(GetTree()->GetRootNode(), tipNodes);

	// find node which sets the branch scale
	int availableWidth = int(m_viewportWidth - 2*Properties::Inst().GetViewportBorderSize() + 0.5);

	// find label start position if labels are too be aligned	
	float widestLabel = 0;
	if(IsAlignedTips())
	{				
		foreach(VisualNode* node, tipNodes)
		{
			if(node->GetLabelWidth() > widestLabel)
				widestLabel = node->GetLabelWidth();
		}

		m_labelStart = uint(m_viewportWidth - widestLabel - Properties::Inst().GetViewportBorderSize() + 0.5);
	}

	float minPixelsPerUnitLength = (float)INT_MAX;
	VisualNode* settingNode;
	foreach(VisualNode* node, tipNodes)
	{		
		float pixelsPerUnitLength;
		float labelWidth;
		if(node->IsCollapsed())
		{
			labelWidth = node->GetLabelWidth();	
			if(IsAlignedTips())
				labelWidth = widestLabel;

			// get length of collapsed node (this is in branch space)
			float lengthBL, lengthML, lengthTL;
			if(node->IsLeaf())
			{
				lengthBL = CollapsedLineLength(node, m_collapsedLeafProperties.bottomLine, availableWidth - labelWidth + 0.5*node->GetSize() - LABEL_OFFSET);
				lengthML = CollapsedLineLength(node, m_collapsedLeafProperties.middleLine, availableWidth - labelWidth + 0.5*node->GetSize() - LABEL_OFFSET);
				lengthTL = CollapsedLineLength(node, m_collapsedLeafProperties.topLine, availableWidth - labelWidth + 0.5*node->GetSize() - LABEL_OFFSET);
			}
			else
			{
				lengthBL= CollapsedLineLength(node, m_collapsedNodeProperties.bottomLine, availableWidth - labelWidth + 0.5*node->GetSize() - LABEL_OFFSET);
				lengthML = CollapsedLineLength(node, m_collapsedNodeProperties.middleLine, availableWidth - labelWidth + 0.5*node->GetSize() - LABEL_OFFSET);
				lengthTL = CollapsedLineLength(node, m_collapsedNodeProperties.topLine, availableWidth - labelWidth + 0.5*node->GetSize() - LABEL_OFFSET);
			}

			float length = qMax<float>(lengthBL, qMax<float>(lengthML, lengthTL));
			pixelsPerUnitLength = (availableWidth - labelWidth + 0.5*node->GetSize() - LABEL_OFFSET - length) / (node->x());
		}
		else
		{
			labelWidth = node->GetLabelWidth();
			if(IsAlignedTips())
				labelWidth = widestLabel;

			float depth = node->x();
			pixelsPerUnitLength = (availableWidth - labelWidth - 0.5*node->GetSize() - LABEL_OFFSET) / node->x();
		}

		if(pixelsPerUnitLength < minPixelsPerUnitLength)
		{
			settingNode = node;
			minPixelsPerUnitLength = pixelsPerUnitLength;
		}
	}

	m_visualScale->SetPixelsPerUnitBranchLength(minPixelsPerUnitLength);

	return availableWidth;
}

float VisualTree::CollapsedLineLength(VisualNode* node, const VisualNode::CollapsedLineProp& prop, uint width) const
{
	// determine length of line in pixels
	float length; 

	if(prop.variable == VisualNode::COLLAPSED_BRANCH_LENGTH)
	{
		QList<VisualNode*> leaves = TreeTools<VisualNode>::GetLeaves(node);	

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

		if(prop.statistic == VisualNode::COLLAPSED_MAX)
			length = max - node->x();
		else if(prop.statistic == VisualNode::COLLAPSED_MIN)
			length = min - node->x();
		else if(prop.statistic == VisualNode::COLLAPSED_MEAN)
			length = sum / nodeX.size() - node->x();
		else if(prop.statistic == VisualNode::COLLAPSED_MEDIAN)
		{
			qSort(nodeX.begin(), nodeX.end());
			if((nodeX.size() & 1) == 0) // even
				length = 0.5*(nodeX.at(nodeX.size() / 2 - 1) + nodeX.at(nodeX.size() / 2)) - node->x();
			else
				length = nodeX.at(nodeX.size() / 2) - node->x();
		}
		else if(prop.statistic == VisualNode::COLLAPSED_TOTAL)
		{
			QList<VisualNode*> nodes = TreeTools<VisualNode>::GetNodes(node);	

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
	else if(prop.variable == VisualNode::COLLAPSED_FIXED)
	{
		length = prop.factor;
		return length;
	}
	else if(prop.variable == VisualNode::COLLAPSED_LEAF_NODE_SPAN)
	{
		QList<VisualNode*> leaves = TreeTools<VisualNode>::GetLeaves(node);	
		float minY = (float)INT_MAX;
		float maxY = (float)-INT_MAX;
		foreach(VisualNode* leaf, leaves)
		{
			if(leaf->y() < minY)
					minY = leaf->y();

			if(leaf->y() > maxY)
					maxY = leaf->y();
		}

		length = (maxY-minY)*prop.factor;
	}
	else if(prop.variable == VisualNode::COLLAPSED_SIZE_VAR)
	{
		QList<VisualNode*> leaves = TreeTools<VisualNode>::GetLeaves(node);	

		QList<float> nodeSizeVar;
		float sum = 0;
		float min = (float)INT_MAX;
		float max = (float)-INT_MAX;
		foreach(VisualNode* leaf, leaves)
		{
			float size = leaf->GetSize();
			if(size != VisualNode::NO_DISTANCE)
			{
				nodeSizeVar.append(size);
				sum += size;

				if(size < min)
					min = size;

				if(size > max)
					max = size;
			}
		}

		if(prop.statistic == VisualNode::COLLAPSED_MAX)
			length = max;
		else if(prop.statistic == VisualNode::COLLAPSED_MIN)
			length = min;
		else if(prop.statistic == VisualNode::COLLAPSED_MEAN)
			length = sum / nodeSizeVar.size();
		else if(prop.statistic == VisualNode::COLLAPSED_MEDIAN)
		{
			qSort(nodeSizeVar.begin(), nodeSizeVar.end());
			if((nodeSizeVar.size() & 1) == 0) // even
				length = 0.5*(nodeSizeVar.at(nodeSizeVar.size() / 2 - 1) + nodeSizeVar.at(nodeSizeVar.size() / 2));
			else
				length = nodeSizeVar.at(nodeSizeVar.size() / 2);
		}
		else if(prop.statistic == VisualNode::COLLAPSED_TOTAL)
		{
			QList<VisualNode*> nodes = TreeTools<VisualNode>::GetNodes(node);	

			float total = 0;
			foreach(VisualNode* node, nodes)
			{
				float size = node->GetSize();
				if(size != VisualNode::NO_DISTANCE)
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
	else if(prop.variable == VisualNode::COLLAPSED_ABUNDANCE)
	{
		float numSeqs;
		if(m_leafTreatment == VisualTree::RELATIVE_PROPORITON_TREATMENT)
			numSeqs = node->GetRelativeProportionOfSeqs();
		else if(m_leafTreatment == VisualTree::WEIGHTED_TREATMENT)
			numSeqs = node->GetWeightedNumberOfSeqs();
		else
			numSeqs = node->GetNumberOfSeqs();

		float relativeAbundance = numSeqs / GetMaxAbundance();
		length = relativeAbundance*GetMaxAbundanceSize();

		if(length < prop.minSize)
			length = prop.minSize;
		if(length > prop.maxSize)
			length = prop.maxSize; 

		return length;
	}
	else if(prop.variable == VisualNode::COLLAPSED_NONE)
	{
		length = 0;
	}
	else
	{
		Log::Inst().Error( "Unrecognized collapsed node variable.");
		return 0.0;
	}

	// change to pixel space
	float conversion = width / (node->x() + length);
	length *= conversion;

	// make sure extents are obeyed
	if(length < prop.minSize)
		length = prop.minSize;
	if(length > prop.maxSize)
		length = prop.maxSize; 

	return length;
}

void VisualTree::SetViewportSize(int width, int height)
{
	Log::Inst().Debug("VisualTree::SetViewportSize(int width, int height)");

	m_viewportWidth = width;
	m_viewportHeight = height;

	Layout();
}

void VisualTree::SetRootLength(double length)
{
	Log::Inst().Debug("VisualTree::SetRootLength(double length)");
	if(m_rootLength == length)
		return;

	m_rootLength = length;

	Layout();
}

void VisualTree::SetLeafSpacing(int spacing)
{
	Log::Inst().Debug("VisualTree::SetLeafSpacing(int spacing)");
	if(m_leafSpacing == spacing)
		return;

	m_leafSpacing = spacing;

	Layout();
}

void VisualTree::SetBranchWidth(int width)
{
	Log::Inst().Debug("VisualTree::SetBranchWidth(int width)");

	for(int i = 0; i < m_branches.size(); ++i)
		m_branches[i]->SetWidth(width);
}

void VisualTree::SetDrawBranchOutline(bool state)
{
	Log::Inst().Debug("VisualTree::SetDrawBranchOutline(bool state)");

	for(int i = 0; i < m_branches.size(); ++i)
		m_branches[i]->SetDrawOutline(state);
}

void VisualTree::SetLeafNodeSize(int size)
{
	Log::Inst().Debug("VisualTree::SetNodeSize(int size)");

	if(m_nodeSizeStyle == VisualNode::SINGLE_SIZE)
		GetTree()->SetLeafSize(size);

	Layout();
}

void VisualTree::SetInternalNodeSize(int size)
{
	Log::Inst().Debug("VisualTree::SetNodeSize(int size)");

	if(m_nodeSizeStyle == VisualNode::SINGLE_SIZE)
	{
		m_dummyRootParent->SetSize(size);
		GetTree()->SetInternalSize(size);
	}
}

void VisualTree::CenterOnRoot()
{
	Log::Inst().Debug("VisualTree::CenterOnRoot()");

	if(!IsVisible())
		return;

	foreach(QGraphicsView* view, m_scene->views())
		view->centerOn(m_viewportWidth/2, GetTree()->GetRootNode()->y());
}

QStringList VisualTree::FindNodeLabels(const QString& searchStr, const QString& searchType)
{
	Log::Inst().Debug("VisualTree::FindNodeLabels(const QString& searchStr, const QString& searchType)");

	QStringList results = m_textSearch.filterData(searchStr, searchType);

	if(!GetTree())
		return results;

	QList<VisualNode*> nodes = GetTree()->GetNodes();
	foreach(VisualNode* node, nodes)
		node->SetTextHighlight(false);

	if(searchStr != "")
	{
		// highlight results of search (unless the search string is empty)
		foreach(QString result, results)
		{
			uint nodeId;
			m_textSearch.data(result, nodeId);
			VisualNode* node = GetTree()->GetNode(nodeId);
			node->SetTextHighlight(true);
		}
	}

	return results;
}

void VisualTree::CenterOnNode(const QString& nodeLabel)
{
	Log::Inst().Debug("VisualTree::CenterOnNode(const QString& nodeLabel)");

	if(!IsVisible() || nodeLabel == "")
		return;

	uint nodeId;
	bool bFound = m_textSearch.data(nodeLabel, nodeId);
	if(bFound)
	{
		VisualNode* node = GetTree()->GetNode(nodeId);

		foreach(QGraphicsView* view, m_scene->views())
			view->centerOn(m_viewportWidth/2, node->y());
	}
	else
	{
		Log::Inst().Error("VisualTree:CenterOnNode(): searching for unknown node label.");
	}
}

void VisualTree::SetNodeFont(const QFont& font, const QColor& color) 
{ 
	Log::Inst().Debug("VisualTree::SetNodeFont(const QFont& font)");

	if(!GetTree())
		return;

	m_nodeFont = font; 
	m_nodeFontColor = color;

	QList<VisualNode*> nodes = GetTree()->GetNodes();
	foreach(VisualNode* node, nodes)
		node->FontChanged();

	Layout();
}

void VisualTree::SetBranchFont(const QFont& font, const QColor& color) 
{ 
	Log::Inst().Debug("VisualTree::SetBranchFont(const QFont& font)");

	m_branchFont = font; 
	m_branchFontColor = color;

	for(int i = 0; i < m_branches.size(); ++i)
		m_branches[i]->FontChanged();
}

void VisualTree::SetBranchColor(const QColor& color)
{
	Log::Inst().Debug("VisualTree::SetBranchColor(const QColor& color)");

	if(m_branchColorStyle == VisualBranch::SINGLE_COLOR)
	{
		for(int i = 0; i < m_branches.size(); ++i)
			m_branches[i]->SetColor(color);
	}
}

void VisualTree::SetBranchLabel(const QString& labelType)
{
	Log::Inst().Debug("VisualTree::SetBranchLabel(const QString& labelType)");

	if(labelType == "None")
		m_branchLabelType = VisualBranch::NO_LABEL;
	else if(labelType == "Assigned internal labels")
		m_branchLabelType = VisualBranch::ASSIGNED_INTERNAL_LABELS;
	else if(labelType == "Length")
		m_branchLabelType = VisualBranch::LENGTH_LABEL;
	else if(labelType == "Depth")
		m_branchLabelType = VisualBranch::DEPTH_LABEL;
	else if(labelType == "Height")
		m_branchLabelType = VisualBranch::HEIGHT_LABEL;

	for(int i = 0; i < m_branches.size(); ++i)
		m_branches[i]->LabelChanged();
}

void VisualTree::SetNodeColor(const QColor& color)
{
	if(!GetTree())
		return;

	Log::Inst().Debug("VisualTree::SetNodeColor(const QColor& color)");

	if(m_nodeColorStyle == VisualNode::SINGLE_COLOR)
	{
		QList<VisualNode*> nodes = GetTree()->GetNodes();
		foreach(VisualNode* node, nodes)
			node->SetColor(color);
	}
}

void VisualTree::SetNodeShape(const QString& shapeStr)
{
	Log::Inst().Debug("VisualTree::SetNodeShape(const QString& shapeStr)");

	if(!GetTree())
		return;

	if(m_nodeShapeStyle == VisualNode::SINGLE_SHAPE)
	{
		QwtSymbol::Style shape = Legends::GetShape(shapeStr);

		QList<VisualNode*> nodes = GetTree()->GetNodes();
		foreach(VisualNode* node, nodes)
			node->SetShape(shape);
	}
}

void VisualTree::SetNodeLabel(const QString& labelType)
{
	Log::Inst().Debug("VisualTree::SetNodeLabel(const QString& labelType)");

	if(!GetTree())
		return;

	if(labelType == "None")
		m_nodeLabelType = VisualNode::NO_LABEL;
	else if(labelType == "Assigned labels")
		m_nodeLabelType = VisualNode::ASSIGNED_LABEL;
	else if(labelType == "Assigned labels (leaves only)")
		m_nodeLabelType = VisualNode::ASSIGNED_LEAF_LABEL;
	else if(labelType == "Support values")
		m_nodeLabelType = VisualNode::SUPPORT_LABEL;
	else if(labelType == "Consistency index")
		m_nodeLabelType = VisualNode::CONSISTENCY_INDEX_LABEL;
	else if(labelType == "Depth")
		m_nodeLabelType = VisualNode::DEPTH_LABEL;
	else if(labelType == "Height")
		m_nodeLabelType = VisualNode::HEIGHT_LABEL;
	else if(labelType == "Distance to root")
		m_nodeLabelType = VisualNode::DISTANCE_TO_ROOT_LABEL;
	else if(labelType == "Distance to closest leaf")
		m_nodeLabelType = VisualNode::DISTANCE_TO_CLOSEST_LEAF_LABEL;
	else if(labelType == "Distance to furthest leaf")
		m_nodeLabelType = VisualNode::DISTANCE_TO_FURTHEST_LEAF_LABEL;
	else if(labelType == "Distance to leaves (average)")
		m_nodeLabelType = VisualNode::DISTANCE_TO_LEAVES_LABEL;

	UpdateAllLabels();
}

bool heightSorter(const VisualNode* node1, const VisualNode* node2)
{
	return node1->GetHeight() < node2->GetHeight();
}

void VisualTree::CollapseSelectedNode()
{
	Log::Inst().Debug("VisualTree::CollapseSelectedNode()");

	QList<QGraphicsItem*> items = m_scene->selectedItems();

	QList<VisualNode*> nodes;
	foreach(QGraphicsItem* item, items)
	{
		VisualNode* node = dynamic_cast<VisualNode*>(item);
		if(node)
			nodes.push_back(node);
	}

	if(nodes.size() > 0)
	{
		qSort(nodes.begin(), nodes.end(), heightSorter);
		foreach(VisualNode* node, nodes)
		{
			if(!node->IsLeaf())
				node->ToggleCollapsedInternal();
		}

		float offsetFromCenter = m_scene->views()[0]->mapFromScene(nodes.at(0)->pos()).y()-m_viewportHeight/2;

		Layout();

		if(nodes.size() == 1)
		{
			// keep root of collapsed subtree in the same position in the viewport
			m_scene->views()[0]->centerOn(m_viewportWidth/2, nodes.at(0)->y()-offsetFromCenter);
		}
	}
	else
	{
		QMessageBox::information(0, "Unable to collapse", "Select node(s) to collapse or uncollapse.");
	}
}

void VisualTree::CollapseComplementSelectedNode()
{
	Log::Inst().Debug("VisualTree::CollapseComplementSelectedNode()");

	QList<QGraphicsItem*> items = m_scene->selectedItems();

	QList<VisualNode*> nodes;
	foreach(QGraphicsItem* item, items)
	{
		VisualNode* node = dynamic_cast<VisualNode*>(item);
		if(node)
			nodes.push_back(node);
	}

	if(nodes.size() == 1)
		CollapseComplement(nodes.at(0));
	else
		QMessageBox::information(0, "Unable to collapse complement", "Select a single node.");
}

void VisualTree::CollapseComplement(VisualNode* selectedNode)
{
	Log::Inst().Debug("VisualTree::CollapseComplement(VisualNode* node)");

	// collapse complement of selected node
	VisualNode* childNode = selectedNode;
	VisualNode* parentNode = selectedNode->GetParent();
	while(!parentNode->IsRoot())
	{
		foreach(VisualNode* child, parentNode->GetChildren())
		{
			if(child != childNode && !child->IsLeaf())
				child->SetCollapsedInternal(true);
		}

		childNode = parentNode;
		parentNode = parentNode->GetParent();
	}

	// keep root of collapsed subtree in the same position in the viewport
	float offsetFromCenter = m_scene->views()[0]->mapFromScene(selectedNode->pos()).y()-m_viewportHeight/2;
	Layout();
	m_scene->views()[0]->centerOn(m_viewportWidth/2, selectedNode->y()-offsetFromCenter);
}

void VisualTree::RotateSelectedBranches()
{
	Log::Inst().Debug("VisualTree::RotateSelectedBranches()");

	QList<QGraphicsItem*> items = m_scene->selectedItems();

	QList<VisualNode*> nodes;
	foreach(QGraphicsItem* item, items)
	{
		VisualNode* node = dynamic_cast<VisualNode*>(item);
		if(node)
			nodes.push_back(node);
	}

	if(nodes.size() == 1)
	{
		nodes[0]->Rotate();

		Layout();
	}
	else
	{
		QMessageBox::information(0, "Unable to rotate branches", "Select a single node for which branches will be rotated.");
	}
}

void VisualTree::SortAlphabetical()
{
	Log::Inst().Debug("VisualTree::SortAlphabetical()");

	if(!GetTree())
		return;

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	QQueue<VisualNode*> nodes;
	nodes.enqueue(GetTree()->GetRootNode());

	while(!nodes.empty())
	{
		VisualNode* curNode = nodes.dequeue();

		QList<VisualNode*> children = curNode->GetChildren();
		
		QMultiMap<QString, VisualNode*> lowestLabelToNodes;
		foreach(VisualNode* child, children)
		{
			QStringList leafNames = TreeTools<VisualNode>::GetLeafNames(child);
			qSort(leafNames.begin(), leafNames.end(), caseInsensitiveLessThan);
			lowestLabelToNodes.insert(leafNames.at(0), child);

			if(!child->IsLeaf())
				nodes.enqueue(child);
		}

		curNode->RemoveChildren();
		QList<QString> keys = lowestLabelToNodes.uniqueKeys();
		qSort(keys.begin(), keys.end(), caseInsensitiveLessThan);

		foreach(const QString key, keys)
		{
			foreach(VisualNode* node, lowestLabelToNodes.values(key))
				curNode->AddChild(node);
		}
	}

	Layout();

	QApplication::restoreOverrideCursor();
}

void VisualTree::Ladderize(LADDERIZE_DIR ladderizeDir)
{
	Log::Inst().Debug("VisualTree::Ladderize()");

	if(!GetTree())
		return;

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	QQueue<VisualNode*> nodes;
	nodes.enqueue(GetTree()->GetRootNode());

	while(!nodes.empty())
	{
		VisualNode* curNode = nodes.dequeue();

		QList<VisualNode*> children = curNode->GetChildren();
		
		QMultiMap<uint, VisualNode*> numLeavesToNodes;
		foreach(VisualNode* child, children)
		{
			uint numLeaves = child->GetNumberOfLeaves();
			numLeavesToNodes.insert(numLeaves, child);

			if(!child->IsLeaf())
				nodes.enqueue(child);
		}

		curNode->RemoveChildren();
		QList<uint> keys = numLeavesToNodes.uniqueKeys();
		if(ladderizeDir == LADDERIZE_BOTTOM)
			qSort(keys.begin(), keys.end(), qGreater<uint>());

		foreach(uint key, keys)
		{
			foreach(VisualNode* node, numLeavesToNodes.values(key))
				curNode->AddChild(node);
		}
	}

	Layout();

	QApplication::restoreOverrideCursor();
}

void VisualTree::UpdateNodes()
{
	Log::Inst().Debug("VisualTree::UpdateNodes()");

	QList<VisualNode*> nodes = GetTree()->GetNodes();
	foreach(VisualNode* node, nodes)
		node->update();
}

void VisualTree::UncollapseAllNodes()
{
	Log::Inst().Debug("VisualTree::UncollapseAllNodes()");

	if(!GetTree())
		return;

	QList<VisualNode*> nodes = GetTree()->GetNodes();
	foreach(VisualNode* node, nodes)
	{
		node->SetCollapsedInternal(false);
		node->SetSelected(false);
	}

	Layout();
}

void VisualTree::CollapseAllNodes()
{
	Log::Inst().Debug("VisualTree::CollapseAllNodes()");

	if(!GetTree())
		return;

	QList<VisualNode*> nodes = GetTree()->GetNodes();
	foreach(VisualNode* node, nodes)
	{
		node->SetCollapsedInternal(true);
		node->SetSelected(false);
	}

	Layout();
}

void VisualTree::CollapseToScreen()
{
	Log::Inst().Debug("VisualTree::CollapseToScreen()");

	if(!m_tree)
		return;

	QApplication::setOverrideCursor(Qt::WaitCursor);

	// collapse all nodes
	QList<VisualNode*> nodes = GetTree()->GetNodes();
	foreach(VisualNode* node, nodes)
	{
		node->SetCollapsedInternal(true);
		node->SetSelected(false);
	}

	m_viewportWidth = m_scene->views()[0]->viewport()->width();
	m_viewportHeight = m_scene->views()[0]->viewport()->height();

	// expand nodes in a breadth-first order until it occupies
	// the entire screen
	QQueue<VisualNode*> queue;
	queue.enqueue(m_tree->GetRootNode());
	bool bDone = false;
	QSet<VisualNode*> tipNodes;
	while(!queue.empty() && !bDone)
	{
		VisualNode* curNode = queue.dequeue();

		if(!curNode->IsLeaf())
		{			
			curNode->SetCollapsedInternal(false);

			tipNodes.remove(curNode);
			foreach(VisualNode* child, curNode->GetChildren())
				tipNodes.insert(child);

			float height = 0;
			foreach(VisualNode* node, tipNodes)
			{		
				QRectF extents = node->boundingRect();
				height += 2*m_leafSpacing + extents.height();
			}

			if(height > m_viewportHeight-2*Properties::Inst().GetViewportBorderSize())
			{
				float collapsedHeight = curNode->boundingRect().height();

				curNode->SetCollapsedInternal(true);
				float uncollapsedHeight = curNode->boundingRect().height();

				if(uncollapsedHeight > collapsedHeight)
				{
					// better collapse parent as well to make sure tree will fit on the screen
					curNode->GetParent()->SetCollapsedInternal(true);
				}

				bDone = true;
			}
			else
			{
				foreach(VisualNode* child, curNode->GetChildren())
					queue.enqueue(child);
			}
		}
	}

	Layout();

	QApplication::restoreOverrideCursor();
}

void VisualTree::SetCollapsedNodeProperties(const VisualNode::CollapsedProp& properties)
{
	Log::Inst().Debug("VisualTree::SetCollapsedNodeProperties()");

	if(!GetTree())
		return;

	m_collapsedNodeProperties = properties;

	CalculateAbundanceExtents();

	Layout();
}

void VisualTree::CollapseNodes(AUTO_COLLAPSE_CONSTRAINT contrainType, float constraint)
{
	Log::Inst().Debug("VisualTree::CollapseNodes()");

	if(!GetTree())
		return;

	// uncollapse all nodes
	UncollapseAllNodes();

	// collapse nodes based on specified constraint
	QQueue<VisualNode*> queue;
	queue.enqueue(GetTree()->GetRootNode());

	while(!queue.empty())
	{
		VisualNode* curNode = queue.dequeue();

		if(contrainType == DIST_TO_FURTHEST_LEAF_NODE_CONSTRAINT)
		{
			if(curNode->GetDistanceToFurthestLeafNode() < constraint)
				curNode->SetCollapsedInternal(true);
		}
		else if(contrainType == DIST_TO_ROOT_CONSTRAINT)
		{
			if(curNode->GetDistanceToRoot() > constraint)
				curNode->SetCollapsedInternal(true);
		}
		else if(contrainType == TOTAL_BRANCH_LENGTH_CONSTRAINT)
		{
			if(curNode->GetTotalBranchLength() < constraint)
				curNode->SetCollapsedInternal(true);
		}
		else if(contrainType == CONSISTENCY_INDEX_CONSTRAINT)
		{
			ParsimonyData* data = curNode->GetParsimonyData();
			if(!data)
			{
				QMessageBox::information(0, "Collapse node message", "A parsimony analysis must be run first.", QMessageBox::Ok);
				return;
			}

			if(data->consistencyIndex > constraint)
				curNode->SetCollapsedInternal(true);
		}
		else if(contrainType == SUPPORT_VALUE_CONSTRAINT)
		{
			if(curNode->GetSupport() < constraint)
				curNode->SetCollapsedInternal(true);
		}

		// add children to processing queue if node is uncollapsed
		if(!curNode->IsCollapsed())
		{
			foreach(VisualNode* child, curNode->GetChildren())
			{
				if(!child->IsLeaf())
					queue.enqueue(child);
			}
		}
	}

	Layout();
}

void VisualTree::SetActiveSubtree(VisualNode* node)
{
	Log::Inst().Debug("VisualTree::SetActiveSubtree()");

	if(node)
	{
		m_activeSetHighlighter->SetVisibility(true);
		m_activeSetHighlighter->SetSubtree(node);

		m_activeSubtreeRoot = node;

		if(m_activeSystem)
			m_activeSystem->CreateFromTree(m_activeSubtreeRoot);
	}
	else
	{
		m_activeSetHighlighter->SetVisibility(false);

		m_activeSubtreeRoot = GetTree()->GetRootNode();

		if(m_activeSystem)
			m_activeSystem->CreateFromTree(m_activeSubtreeRoot);
	}
}

void VisualTree::Reroot()
{
	Log::Inst().Debug("VisualTree::Reroot()");

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	QList<QGraphicsItem*> items = m_scene->selectedItems();

	QList<VisualNode*> nodes;
	foreach(QGraphicsItem* item, items)
	{
		VisualNode* node = dynamic_cast<VisualNode*>(item);
		if(node)
			nodes.push_back(node);
	}

	if(nodes.size() == 1)
	{
		m_tree->Reroot(nodes.at(0));
		m_tree->CalculateStatistics(m_activeSystem->GetSamples());
		ConnectBranchesToNodes();

		Layout();

		emit NodeColorStyleChanged();
		emit NodeSizeStyleChanged();
		emit NodeShapeStyleChanged();
		emit BranchColorStyleChanged();
		emit AbundanceStyleChanged();
	}
	else
	{
		QApplication::restoreOverrideCursor();
		QMessageBox::information(0, "Unable to reroot tree", "Select a single node to reroot tree half way along parantal branch.");
		return;
	}

	QApplication::restoreOverrideCursor();
}

QString VisualTree::GetMethodMessage() const 
{ 
	Log::Inst().Debug("VisualTree::GetMethodMessage()");

	QString message;
	if(m_branchStyle == PHYLOGRAM_BRANCHES)
		message = "Phylogram";
	else if(m_branchStyle == EQUAL_BRANCHES)
		message = "Equal";
	else if(m_branchStyle == CLADOGRAM_BRANCHES)
		message = "Cladogram";

	if(m_leafTreatment == UNWEIGHTED_TREATMENT)
		message += " - unweighted";
	else if(m_leafTreatment == WEIGHTED_TREATMENT)
		message += " - weighted";
	else if(m_leafTreatment == RELATIVE_PROPORITON_TREATMENT)
		message += " - relative proportion";

	return message;
}

void VisualTree::UpdateAllLabels()
{
	foreach(VisualNode* node, m_tree->GetNodes())
		node->LabelChanged();

	Layout();
}

void VisualTree::LabelCategoriesChanged()
{
	if(m_bShowColorCategory || m_bShowShapeCategory || m_bShowSizeCategory)
		UpdateAllLabels();
}