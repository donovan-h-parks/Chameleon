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

#include "VisualPhylogeny.hpp"

#include "Legends.hpp"
#include "Properties.hpp"

#include "ParsimonyCalculator.hpp"

#include "SeqMetadata.hpp"
#include "ColorMaps.hpp"

VisualPhylogeny::VisualPhylogeny(SplitSystemPtr splitSystem, LegendsPtr legends, ColorMapsPtr colorMaps)
	: VisualTree(legends), m_seqMetadata(new SeqMetadata(colorMaps)), m_bUseSequenceMetadata(false)
{
	m_leafTreatment = WEIGHTED_TREATMENT;
	SetActiveSystem(splitSystem);
}

void VisualPhylogeny::SetTree(Tree<VisualNode>* tree)
{
	Log::Inst().Debug("Entering VisualPhylogeny::SetTree(...)");

	VisualTree::SetTree(tree);

	CollapseToScreen();

	// Setup initial scale length
	m_visualScale->setPos(Properties::Inst().GetViewportBorderSize(), 
														m_scene->sceneRect().height()-m_visualScale->boundingRect().height());

	Log::Inst().Debug("Leaving VisualPhylogeny::SetTree(...)");
}

void VisualPhylogeny::SetNodeColorStyle(const QString& style, const QColor& color)
{
	Log::Inst().Debug("VisualPhylogeny::SetNodeColorStyle(...)");

	if(!m_activeSystem || !m_tree)
		return;

	if(style == "Single colour")
	{
		m_nodeColorStyle = VisualNode::SINGLE_COLOR;
		SetNodeColor(color);
		return;
	}
	else if(style == "Propogate continuous")
		m_nodeColorStyle = VisualNode::PROPOGATE_CONTINUOUS_COLOR;
	else if(style == "Propogate weighted")
		m_nodeColorStyle = VisualNode::PROPOGATE_WEIGHTED_COLOR;
	else if(style == "Propogate discrete")
		m_nodeColorStyle = VisualNode::PROPOGATE_DISCRETE_COLOR;

	// set node colors
	QList<VisualNode*> postOrderNodes = m_tree->PostOrder();
	if(postOrderNodes.size() == 1)
		return;	// there is only a root node

	foreach(VisualNode* node, postOrderNodes)
	{		
		// get colors associated with the current node
		QList<QColor> nodeColors;		
		QList<float> weights;
		if(node->IsLeaf())
		{
			// get all colors assigned to the leaf node
			if(m_bUseSequenceMetadata)
			{
				weights.append(1);
				nodeColors.append(m_seqMetadata->GetMetadataColor(node->GetName()));
			}
			else
			{
				QList<uint> sampleIds = m_activeSystem->GetSamples()->GetSequences()->GetSampleIdsFromSeqId(node->GetId());

				foreach(uint sampleId, sampleIds)
				{
					nodeColors.append(m_activeSystem->GetSamples()->GetSample(sampleId).GetColor());
					if(m_leafTreatment == VisualTree::RELATIVE_PROPORITON_TREATMENT)
						weights.append(m_activeSystem->GetSamples()->GetSequences()->GetRelativeProportionOfSeqs(node->GetId(), sampleId));
					else if(m_leafTreatment == WEIGHTED_TREATMENT)
						weights.append(m_activeSystem->GetSamples()->GetSequences()->GetNumSequences(node->GetId(), sampleId));
					else
						weights.append(uint(m_activeSystem->GetSamples()->GetSequences()->GetNumSequences(node->GetId(), sampleId) > 1));
				}
			}
		}
		else	
		{
			// we have an internal node, so get the colour of its children
			foreach(VisualNode* child, node->GetChildren())
			{
				nodeColors.append(child->GetColor());

				if(m_bUseSequenceMetadata)
				{
					weights.append(child->GetNumberOfSeqs());
				}
				else
				{
					if(m_leafTreatment == VisualTree::RELATIVE_PROPORITON_TREATMENT)
						weights.append(child->GetRelativeProportionOfSeqs());
					else if(m_leafTreatment == WEIGHTED_TREATMENT)
						weights.append(child->GetWeightedNumberOfSeqs());
					else 
						weights.append(child->GetNumberOfSeqs());
				}
			}
		}

		// color current node based on selected style
		QColor nodeColor;
		if(m_nodeColorStyle == VisualNode::PROPOGATE_DISCRETE_COLOR)
		{
			nodeColor = nodeColors.at(0);
			foreach(const QColor& color, nodeColors)
			{
				if(color != nodeColor)
					nodeColor = Qt::black;
			}
		}
		else if(m_nodeColorStyle == VisualNode::PROPOGATE_CONTINUOUS_COLOR)
		{
			float red = 0.0f, green = 0.0f, blue = 0.0f;
			foreach(const QColor& color, nodeColors)
			{
				red += color.redF();
				green += color.greenF();
				blue += color.blueF();
			}

			nodeColor.setRedF(red / nodeColors.size());
			nodeColor.setGreenF(green / nodeColors.size());
			nodeColor.setBlueF(blue / nodeColors.size());
		}
		else // m_nodeColorStyle == VisualNode::PROPOGATE_WEIGHTED_COLOR
		{
			float red = 0.0f, green = 0.0f, blue = 0.0f;
			uint totalWeight = 0;
			for(int j = 0; j < nodeColors.size(); ++j)
			{
				totalWeight += weights.at(j);

				QColor color = nodeColors.at(j);
				red += color.redF() * weights.at(j);
				green += color.greenF() * weights.at(j);
				blue += color.blueF() * weights.at(j);
			}

			nodeColor.setRedF(red / totalWeight);
			nodeColor.setGreenF(green / totalWeight);
			nodeColor.setBlueF(blue / totalWeight);
		}

		node->SetColor(nodeColor);
		node->update();
	}
}

void VisualPhylogeny::SetNodeShapeStyle(const QString& style, const QString& shapeStr)
{
	Log::Inst().Debug("VisualPhylogeny::SetNodeShapeStyle(...)");

	if(!m_activeSystem || !m_tree)
		return;

	if(style == "Single shape")
	{
		m_nodeShapeStyle = VisualNode::SINGLE_SHAPE;
		SetNodeShape(shapeStr);
		return;
	}
	else if(style == "Propogate discrete")
		m_nodeShapeStyle = VisualNode::PROPOGATE_DISCRETE_SHAPE;

	// set node shape
	QList<VisualNode*> postOrderNodes = m_tree->PostOrder();
	if(postOrderNodes.size() == 1)
		return;	// there is only a root node

	foreach(VisualNode* node, postOrderNodes)
	{
		// get shape associated with the current node
		QList<QwtSymbol::Style> nodeShapes;		
		if(node->IsLeaf())
		{
			// get all shapes assigned to the leaf node
			QList<uint> sampleIds = m_activeSystem->GetSamples()->GetSequences()->GetSampleIdsFromSeqId(node->GetId());

			foreach(uint sampleId, sampleIds)
				nodeShapes.append(m_activeSystem->GetSamples()->GetSample(sampleId).GetShape());
		}
		else	
		{
			// we have an internal node, so get the shapes of its children
			foreach(VisualNode* child, node->GetChildren())
				nodeShapes.append(child->GetShape());
		}

		// set shape of current node based on selected style
		QwtSymbol::Style nodeShape;
		if(m_nodeShapeStyle == VisualNode::PROPOGATE_DISCRETE_SHAPE)
		{
			nodeShape = nodeShapes.at(0);
			foreach(const QwtSymbol::Style& shape, nodeShapes)
			{
				if(shape != nodeShape)
					nodeShape = QwtSymbol::NoSymbol;
			}
		}

		node->SetShape(nodeShape);
		if(nodeShape == QwtSymbol::NoSymbol)
			node->SetSize(0);
		node->update();
	}
}

void VisualPhylogeny::SetNodeSizeStyle(const QString& style, uint leafSize, uint internalSize)
{
	Log::Inst().Debug("VisualPhylogeny::SetNodeSizeStyle(...)");

	if(!m_activeSystem || !m_tree)
		return;

	if(style == "Single size")
	{
		m_nodeSizeStyle = VisualNode::SINGLE_SIZE;
		SetLeafNodeSize(leafSize);
		SetInternalNodeSize(internalSize);
		Layout();
		return;
	}
	else if(style == "Leaves only (average)")
		m_nodeSizeStyle = VisualNode::LEAVES_ONLY_SIZE;
	else if(style == "Propogate continuous")
		m_nodeSizeStyle = VisualNode::PROPOGATE_CONTINUOUS_SIZE;
	else if(style == "Propogate weighted")
		m_nodeSizeStyle = VisualNode::PROPOGATE_WEIGHTED_SIZE;
	else if(style == "Propogate discrete")
		m_nodeSizeStyle = VisualNode::PROPOGATE_DISCRETE_SIZE;

	// set node size
	QList<VisualNode*> postOrderNodes = m_tree->PostOrder();
	if(postOrderNodes.size() == 1)
		return;	// there is only a root node

	foreach(VisualNode* node, postOrderNodes)
	{
		// get size associated with the current node
		QList<uint> nodeSizes;
		QList<float> weights;
		if(node->IsLeaf())
		{
			// get all shapes assigned to the leaf node
			QList<uint> sampleIds = m_activeSystem->GetSamples()->GetSequences()->GetSampleIdsFromSeqId(node->GetId());

			foreach(uint sampleId, sampleIds)
			{
				nodeSizes.append(m_activeSystem->GetSamples()->GetSample(sampleId).GetSize());
				if(m_leafTreatment == VisualTree::RELATIVE_PROPORITON_TREATMENT)
					weights.append(m_activeSystem->GetSamples()->GetSequences()->GetRelativeProportionOfSeqs(node->GetId(), sampleId));
				else if(m_leafTreatment == WEIGHTED_TREATMENT)
					weights.append(m_activeSystem->GetSamples()->GetSequences()->GetNumSequences(node->GetId(), sampleId));
				else
					weights.append(uint(m_activeSystem->GetSamples()->GetSequences()->GetNumSequences(node->GetId(), sampleId) > 1));
			}
		}
		else	
		{
			// we have an internal node, so get the shapes of its children
			foreach(VisualNode* child, node->GetChildren())
			{
				nodeSizes.append(child->GetSize());
				if(m_leafTreatment == VisualTree::RELATIVE_PROPORITON_TREATMENT)
					weights.append(child->GetRelativeProportionOfSeqs());
				else if(m_leafTreatment == WEIGHTED_TREATMENT)
					weights.append(child->GetWeightedNumberOfSeqs());
				else
					weights.append(child->GetNumberOfSeqs());
			}
		}

		// set size of current node based on selected style
		uint nodeSize = 0;
		if(m_nodeSizeStyle == VisualNode::LEAVES_ONLY_SIZE)
		{
			if(node->IsLeaf())
			{
				// set to the average size
				foreach(uint size, nodeSizes)
					nodeSize += size;

				nodeSize = uint(float(nodeSize) / nodeSizes.size() + 0.5);
			}
			else
				nodeSize = 0;
		}
		else if(m_nodeSizeStyle == VisualNode::PROPOGATE_DISCRETE_SIZE)
		{
			nodeSize = nodeSizes.at(0);
			foreach(uint size, nodeSizes)
			{
				if(size != nodeSize)
					nodeSize = 0;
			}
		}
		else if(m_nodeSizeStyle == VisualNode::PROPOGATE_CONTINUOUS_SIZE)
		{
			float sumSizes = 0.0f;
			foreach(uint size, nodeSizes)
				sumSizes += size;

			nodeSize = sumSizes / nodeSizes.size();
		}
		else // m_nodeSizeStyle == VisualNode::PROPOGATE_WEIGHTED_SIZE
		{
			float size = 0.0f;
			uint totalWeight = 0;
			for(int j = 0; j < nodeSizes.size(); ++j)
			{
				totalWeight += weights.at(j);
				size += nodeSizes.at(j) * weights.at(j);
			}

			nodeSize = size / totalWeight;
		}

		node->SetSize(nodeSize);
	}

	Layout();
}

void VisualPhylogeny::SetBranchColorStyle(const QString& style, const QColor& color)
{
	Log::Inst().Debug("VisualPhylogeny::SetBranchColorStyle()");

	if(!m_activeSystem || !m_tree)
		return;

	if(style == "Single colour")
	{
		m_branchColorStyle = VisualBranch::SINGLE_COLOR;
		SetBranchColor(color);
		return;
	}
	else if(style == "Propogate continuous")
		m_branchColorStyle = VisualBranch::PROPOGATE_CONTINUOUS_COLOR;
	else if(style == "Propogate weighted")
		m_branchColorStyle = VisualBranch::PROPOGATE_WEIGHTED_COLOR;
	else if(style == "Propogate discrete")
		m_branchColorStyle = VisualBranch::PROPOGATE_DISCRETE_COLOR;

	// set branch colors
	QList<VisualNode*> postOrderNodes = m_tree->PostOrder();
	if(postOrderNodes.size() == 1)
		return;	// there is only a root node

	foreach(VisualNode* node, postOrderNodes)
	{
		// get colors associated with the current node
		QList<QColor> branchColors;
		QList<float> weights;
		if(node->IsLeaf())
		{
			// get all colors assigned to the leaf node
			QList<uint> sampleIds = m_activeSystem->GetSamples()->GetSequences()->GetSampleIdsFromSeqId(node->GetId());

			foreach(uint sampleId, sampleIds)
			{
				branchColors.append(m_activeSystem->GetSamples()->GetSample(sampleId).GetColor());
				if(m_leafTreatment == VisualTree::RELATIVE_PROPORITON_TREATMENT)
					weights.append(m_activeSystem->GetSamples()->GetSequences()->GetRelativeProportionOfSeqs(node->GetId(), sampleId));
				else if(m_leafTreatment == WEIGHTED_TREATMENT)
					weights.append(m_activeSystem->GetSamples()->GetSequences()->GetNumSequences(node->GetId(), sampleId));
				else
					weights.append(uint(m_activeSystem->GetSamples()->GetSequences()->GetNumSequences(node->GetId(), sampleId) > 1));
			}
		}
		else	
		{
			// we have an internal node, so get the color of the branches leading to its children
			foreach(VisualNode* child, node->GetChildren())
			{
				branchColors.append(child->GetParentBranch()->GetColor());
				if(m_leafTreatment == VisualTree::RELATIVE_PROPORITON_TREATMENT)
					weights.append(child->GetRelativeProportionOfSeqs());
				else if(m_leafTreatment == WEIGHTED_TREATMENT)
					weights.append(child->GetWeightedNumberOfSeqs());
				else 
					weights.append(child->GetNumberOfSeqs());
			}
		}

		// set size of current node based on selected style
		QColor branchColor;		
		if(m_branchColorStyle == VisualBranch::PROPOGATE_DISCRETE_COLOR)
		{
			branchColor = branchColors.at(0);
			foreach(QColor color, branchColors)
			{
				if(color != branchColor)
					branchColor = Qt::black;
			}
		}
		else if(m_branchColorStyle == VisualBranch::PROPOGATE_CONTINUOUS_COLOR)
		{
			float red = 0.0f, green = 0.0f, blue = 0.0f;
			foreach(const QColor& color, branchColors)
			{
				red += color.redF();
				green += color.greenF();
				blue += color.blueF();
			}

			branchColor.setRedF(red / branchColors.size());
			branchColor.setGreenF(green / branchColors.size());
			branchColor.setBlueF(blue / branchColors.size());
		}
		else // m_branchColorStyle == VisualBranch::PROPOGATE_WEIGHTED_COLOR
		{
			float red = 0.0f, green = 0.0f, blue = 0.0f;
			uint totalWeight = 0;
			for(int j = 0; j < branchColors.size(); ++j)
			{
				uint weight = weights.at(j);
				totalWeight += weight;

				QColor color = branchColors.at(j);
				red += color.redF() * weight;
				green += color.greenF() * weight;
				blue += color.blueF() * weight;
			}

			branchColor.setRedF(red / totalWeight);
			branchColor.setGreenF(green / totalWeight);
			branchColor.setBlueF(blue / totalWeight);
		}

		if(!node->IsRoot())
		{
			node->GetParentBranch()->SetColor(branchColor);
			node->GetParentBranch()->update();
		}
	}
}


void VisualPhylogeny::CalculateParsimonyScore(const QString& field)
{
	Log::Inst().Debug("VisualPhylogeny::CalculateParsimonyScore(...)");

	if(!m_tree)
		return;

	m_parsimonyCalculator->Calculate(m_tree, m_activeSystem->GetSamples(), field, true);
}

void VisualPhylogeny::ShowContextMenu(QGraphicsSceneContextMenuEvent *event, VisualNode* sourceNode)
{
	Log::Inst().Debug("VisualPhylogeny::ShowContextMenu()");

	QMenu menu;

	// set active set state of node
	menu.addAction("Select subtree");
	menu.addSeparator();

	// set active set state of node
	//menu.addAction("Set subtree as active set");
	//menu.addAction("Set entire tree as active set");
	//menu.addSeparator();

	// set collapsed node menu items
	QAction *collapseAction;
	QIcon collapseIcon;
	if(sourceNode->IsCollapsed())
	{
		QAction* labelAction = menu.addAction("Set collapsed label");
		QIcon labelIcon;
		labelIcon.addFile(QString::fromUtf8(":/icons/icons/tag_blue_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
		labelAction->setIcon(labelIcon);
		menu.addSeparator();

		collapseAction = menu.addAction("Uncollapse node");		
    collapseIcon.addFile(QString::fromUtf8(":/icons/icons/phylogram.png"), QSize(), QIcon::Normal, QIcon::Off);
	}
	else	
	{    
		collapseAction = menu.addAction("Collapse node");
		collapseIcon.addFile(QString::fromUtf8(":/icons/icons/collapse.png"), QSize(), QIcon::Normal, QIcon::Off);
	}

	collapseAction->setIcon(collapseIcon);

	// collapse complement
	QAction *collapseComplementAction;
	QIcon collapseComplementIcon;
	collapseComplementAction = menu.addAction("Collapse complement");		
  collapseComplementIcon.addFile(QString::fromUtf8(":/icons/icons/collapse-complement.png"), QSize(), QIcon::Normal, QIcon::Off);
	collapseComplementAction->setIcon(collapseComplementIcon);

	QAction *a = menu.exec(event->screenPos());

	// check if user cancelled menu
	if(!a)
		return;

	// process selected menu item
	if(a->text() == "Uncollapse node" || a->text() == "Collapse node")
	{
		sourceNode->ToggleCollapsedInternal();
		Layout(); 
	}
	else if(a->text() == "Collapse complement")
	{
		CollapseComplement(sourceNode);
	}
	else if(a->text() == "Set collapsed label")
	{
		bool bOK;
		QString label = QInputDialog::getText(0, "Collapsed node label", "Label:", QLineEdit::Normal, sourceNode->GetLabel(), &bOK);

		if(bOK)
		{
			sourceNode->SetCollapsedLabel(label);
			Layout(); 
		}
	}
		else if(a->text() == "Select subtree")
	{
	sourceNode->SelectSubtree();
	}
	else if(a->text() == "Unselect subtree")
	{
		sourceNode->UnselectSubtree();
	}
	else if(a->text() == "Set subtree as active set")
	{
		sourceNode->SetSubtreeAsActive(true);
	}
	else if(a->text() == "Set entire tree as active set")
	{
		sourceNode->SetSubtreeAsActive(false);
	}
}

void VisualPhylogeny::SetSelectedLeafNodes()
{
	Log::Inst().Debug("VisualPhylogeny::SetSelectedLeafNodes()");

	if(!m_tree)
		return;

	// update labels of all collapsed nodes
	foreach(VisualNode* node, m_tree->GetNodes())
		node->LabelChanged();		

	Layout();
}

void VisualPhylogeny::RestoreActiveSampleTree() 
{ 
	Log::Inst().Debug("VisualPhylogeny::RestoreActiveSampleTree()");

	if(!m_tree)
		return;

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	QSet<uint> activeSampleIds = m_activeSystem->GetSamples()->GetActiveSampleIds();
	QStringList leavesToRetain;
	foreach(VisualNode* node, m_origTree->GetNodes())
	{
		QList<uint> sampleIds = m_activeSystem->GetSamples()->GetSequences()->GetSampleIdsFromSeqId(node->GetId());
		foreach(uint sampleId, sampleIds)
		{
			if(activeSampleIds.contains(sampleId))
			{
				leavesToRetain.append(node->GetName());
				break;
			}
		}
	}

	ProjectTo(leavesToRetain);

	QApplication::restoreOverrideCursor();
}

void VisualPhylogeny::ProjectToSelectedLeaves()
{
	Log::Inst().Debug("VisualPhylogeny::ProjectToSelectedLeaves()");

	if(!m_tree)
		return;

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	QList<VisualNode*> tipNodes;
	FindTipNodes(m_tree->GetRootNode(), tipNodes);

	QStringList leavesToRetain;
	foreach(VisualNode* node, tipNodes)
	{
		if(node->isSelected())
		{
			if(node->IsLeaf())
				leavesToRetain.append(node->GetName());
			else
				leavesToRetain.append(TreeTools<VisualNode>::GetLeafNames(node));
		}
	}
	
	ProjectTo(leavesToRetain);

	QApplication::restoreOverrideCursor();
}

void VisualPhylogeny::ProjectTo(const QStringList& leavesToRetain)
{
	Log::Inst().Debug("VisualPhylogeny::ProjectTo()");

	// project tree
	Tree<VisualNode>* projectedTree = m_origTree->Clone();
	projectedTree->Project(leavesToRetain);

	// set reasonable values for new tree
	m_abundanceStyle = ABUNDANCE_NONE;
		
	// show projected tree and set split system to reflect the new tree
	m_activeSystem->CreateFromTree(projectedTree->GetRootNode());
	VisualTree::SetTree(projectedTree);

	// remove any samples without sequences in the projected tree
	// from the active sample set
	QSet<uint> activeSamples = m_activeSystem->GetSamples()->GetActiveSampleIds();
	QSet<uint> samplesToRemove;
	foreach(uint sampleId, activeSamples)
	{
		uint seqs = m_activeSystem->GetSamples()->GetSample(sampleId).GetNumSequences();
		if(m_activeSystem->GetSamples()->GetSample(sampleId).GetNumSequences() == 0)
			samplesToRemove.insert(sampleId);
	}
	m_activeSystem->GetSamples()->SetSamplesToInactive(samplesToRemove);

	SetSelectedLeafNodes();

	Layout();
}

void VisualPhylogeny::GetNumberOfSelectedSeqs(VisualNode* node, float& numSeqs, float& numSelected)
{
	numSeqs = 0;
	numSelected = 0;
	QSet<uint> selectedSampleIds = m_activeSystem->GetSamples()->GetSelectedSampleIds();
	QSet<uint> activeSampleIds = m_activeSystem->GetSamples()->GetActiveSampleIds();
	foreach(VisualNode* leaf,  TreeTools<VisualNode>::GetLeaves(node))
	{
		QList<uint> sampleIds = m_activeSystem->GetSamples()->GetSequences()->GetSampleIdsFromSeqId(leaf->GetId());
		foreach(uint sampleId, sampleIds)
		{
			if(activeSampleIds.contains(sampleId))
			{
				float weight;
				if(m_leafTreatment == VisualTree::RELATIVE_PROPORITON_TREATMENT)
					weight = m_activeSystem->GetSamples()->GetSequences()->GetRelativeProportionOfSeqs(leaf->GetId(), sampleId);
				else if(m_leafTreatment == VisualTree::WEIGHTED_TREATMENT)
					weight = m_activeSystem->GetSamples()->GetSequences()->GetNumSequences(leaf->GetId(), sampleId);
				else
					weight = uint(m_activeSystem->GetSamples()->GetSequences()->GetNumSequences(leaf->GetId(), sampleId) >= 1);

				numSeqs += weight;

				if(selectedSampleIds.contains(sampleId))
					numSelected += weight;
			}
		}
	}
}


QString VisualPhylogeny::GetCategoryInfo(VisualNode* node, const QString& field)
{
	Log::Inst().Debug("VisualPhylogeny::GetCategoryInfo(VisualNode* node, const QString& field)");

	QString categoryInfo;

	if(m_bUseSequenceMetadata)
	{
		categoryInfo += m_seqMetadata->GetMetadataValue(node->GetName());
	}
	else
	{
		QList<uint> sampleIds = m_activeSystem->GetSamples()->GetSequences()->GetSampleIdsFromSeqId(node->GetId());
		foreach(uint sampleId, sampleIds)
		{
			QString category  = m_activeSystem->GetSamples()->GetMetadata()->GetValue(field, sampleId);
			categoryInfo += category;
		}
	}

	return categoryInfo;
}

void VisualPhylogeny::SetUseSequenceMetadata(bool bState) 
{ 
	m_bUseSequenceMetadata = bState; 

	if(!m_seqMetadata->GetFields().isEmpty())
	{
		emit BranchColorStyleChanged();
		emit NodeColorStyleChanged();
	}
}

void VisualPhylogeny::SetPhylogenyMetadataCategories(const QString& category) 
{ 
	m_seqMetadata->SetField(category); 

	emit BranchColorStyleChanged();
	emit NodeColorStyleChanged();

	if(m_bShowColorCategory)
		UpdateAllLabels();
}

void VisualPhylogeny::SetPhylogenyMetadataColorMap(const QString& colorMap)
{
	m_seqMetadata->SetColorMap(colorMap);

	emit BranchColorStyleChanged();
	emit NodeColorStyleChanged();
}

void VisualPhylogeny::SetPhylogenyOtherPercentage(double percentage) 
{ 
	m_seqMetadata->SetOtherPercentage(percentage); 

	emit BranchColorStyleChanged();
	emit NodeColorStyleChanged();
}

void VisualPhylogeny::GetCollapsedNodeGradient(const VisualNode* node, QMap<QString, float>& gradientMap, float& totalWeight)
{
	QSet<uint> activeSampleIds = m_activeSystem->GetSamples()->GetActiveSampleIds();

	foreach(const VisualNode* leaf, TreeTools<VisualNode>::GetLeaves(node))
	{
		if(m_bUseSequenceMetadata)
		{
			QColor color = m_seqMetadata->GetMetadataColor(leaf->GetName());
			QString colorName = color.name();
			QMap<QString, float>::const_iterator it = gradientMap.find(colorName);
			if(it == gradientMap.end())
				gradientMap[colorName] = 1;
			else
				gradientMap[colorName] = it.value() + 1;
	
			totalWeight += 1;
		}
		else
		{
			// get all colors assigned to the leaf node
			QList<uint> sampleIds = m_activeSystem->GetSamples()->GetSequences()->GetSampleIdsFromSeqId(leaf->GetId());
			foreach(uint sampleId, sampleIds)
			{
				if(activeSampleIds.contains(sampleId))
				{
					QColor color = m_activeSystem->GetSamples()->GetSample(sampleId).GetColor();

					float weight;
					if(m_leafTreatment == VisualTree::RELATIVE_PROPORITON_TREATMENT)
						weight = m_activeSystem->GetSamples()->GetSequences()->GetRelativeProportionOfSeqs(leaf->GetId(), sampleId);
					else if(m_leafTreatment == VisualTree::WEIGHTED_TREATMENT)
						weight = m_activeSystem->GetSamples()->GetSequences()->GetNumSequences(leaf->GetId(), sampleId);
					else
						weight = uint(m_activeSystem->GetSamples()->GetSequences()->GetNumSequences(leaf->GetId(), sampleId) >= 1);

					QString colorName = color.name();
					QMap<QString, float>::const_iterator it = gradientMap.find(colorName);
					if(it == gradientMap.end())
						gradientMap[colorName] = weight;
					else
						gradientMap[colorName] = it.value() + weight;

					totalWeight += weight;
				}
			}
		}
	}
}