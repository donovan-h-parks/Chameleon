#include "stdafx.h"

#include "VisualClusterTree.hpp"

#include "Legends.hpp"
#include "Properties.hpp"
#include "UniSplit.hpp"
#include "NewickIO.hpp"
#include "System.hpp"

#include "ParsimonyCalculator.hpp"

VisualClusterTree::VisualClusterTree(LegendsPtr legends): VisualTree(legends)
{

}

void VisualClusterTree::SetTree(Tree<VisualNode>* tree)
{
	Log::Inst().Debug("VisualClusterTree::SetTree(...)");

	VisualTree::SetTree(tree);
	Layout();

	// Setup initial scale length
	m_visualScale->setPos(Properties::Inst().GetViewportBorderSize(), 
														m_scene->sceneRect().height()-m_visualScale->boundingRect().height());
}

void VisualClusterTree::SetNodeColorStyle(const QString& style, const QColor& color)
{
	Log::Inst().Debug("VisualClusterTree::SetNodeColorStyle(...)");

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
		QColor nodeColor;
		if(node->IsLeaf())
		{
			// set color of node based on legend
			Sample sample;
			if(!m_activeSystem->GetSamples()->GetSample(node->GetName(), sample))
				Log::Inst().Error("Invalid sample specified setting node colour: " + node->GetName());

			nodeColor = sample.GetColor();
		}
		else
		{
			// set color of node based on color of children
			QList<VisualNode*> children = node->GetChildren();
			
			if(m_nodeColorStyle == VisualNode::PROPOGATE_DISCRETE_COLOR)
			{
				nodeColor = children.at(0)->GetColor();
				for(int j = 0; j < children.size(); ++j)
				{
					if(children.at(j)->GetColor() != nodeColor)
						nodeColor = Qt::black;
				}
			}
			else if(m_nodeColorStyle == VisualNode::PROPOGATE_CONTINUOUS_COLOR)
			{
				float red = 0.0f, green = 0.0f, blue = 0.0f;
				for(int j = 0; j < children.size(); ++j)
				{
					QColor color = children.at(j)->GetColor();
					red += color.redF();
					green += color.greenF();
					blue += color.blueF();
				}

				nodeColor.setRedF(red / children.size());
				nodeColor.setGreenF(green / children.size());
				nodeColor.setBlueF(blue / children.size());
			}
			else // m_nodeColorStyle == VisualNode::PROPOGATE_WEIGHTED_COLOR
			{
				float red = 0.0f, green = 0.0f, blue = 0.0f;
				uint totalWeight = 0;
				for(int j = 0; j < children.size(); ++j)
				{
					uint weight = children.at(j)->GetWeightedNumberOfSeqs();
					totalWeight += weight;

					QColor color = children.at(j)->GetColor();
					red += color.redF() * weight;
					green += color.greenF() * weight;
					blue += color.blueF() * weight;
				}

				nodeColor.setRedF(red / totalWeight);
				nodeColor.setGreenF(green / totalWeight);
				nodeColor.setBlueF(blue / totalWeight);
			}
		}

		node->SetColor(nodeColor);
		node->update();
	}

}

void VisualClusterTree::SetNodeShapeStyle(const QString& style, const QString& shapeStr)
{
	Log::Inst().Debug("VisualClusterTree::SetNodeShapeStyle(...)");

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
		QwtSymbol::Style nodeShape;
		if(node->IsLeaf())
		{
			// set shape of node based on legend
			Sample sample;
			if(!m_activeSystem->GetSamples()->GetSample(node->GetName(), sample))
				Log::Inst().Error("Invalid sample specified setting node shape: " + node->GetName());

			nodeShape = sample.GetShape();
		}
		else
		{
			// set shape based on shape of children
			QList<VisualNode*> children = node->GetChildren();
			
			if(m_nodeShapeStyle == VisualNode::PROPOGATE_DISCRETE_SHAPE)
			{
				nodeShape = children.at(0)->GetShape();
				for(int j = 0; j < children.size(); ++j)
				{
					if(children.at(j)->GetShape() != nodeShape)
						nodeShape = QwtSymbol::NoSymbol;
				}
			}
		}

		node->SetShape(nodeShape);
		if(nodeShape == QwtSymbol::NoSymbol)
			node->SetSize(0);
		node->update();
	}
}

void VisualClusterTree::SetNodeSizeStyle(const QString& style, uint leafSize, uint internalSize)
{
	Log::Inst().Debug("VisualClusterTree::SetNodeSizeStyle(...)");

	if(!m_activeSystem || !m_tree)
		return;

	if(style == "Single size")
	{
		m_nodeSizeStyle = VisualNode::SINGLE_SIZE;
		SetLeafNodeSize(leafSize);
		SetInternalNodeSize(internalSize);
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
		uint nodeSize;
		if(node->IsLeaf())
		{
			// set size of node based on legend
			Sample sample;
			if(!m_activeSystem->GetSamples()->GetSample(node->GetName(), sample))
				Log::Inst().Error("Invalid sample specified setting node size: " + node->GetName());

			nodeSize = sample.GetSize();
		}
		else
		{
			// set size of node based on size of children
			QList<VisualNode*> children = node->GetChildren();
			
			if(m_nodeSizeStyle == VisualNode::LEAVES_ONLY_SIZE)
			{
				nodeSize = 0;
			}
			else if(m_nodeSizeStyle == VisualNode::PROPOGATE_DISCRETE_SIZE)
			{
				nodeSize = children.at(0)->GetSize();
				for(int j = 0; j < children.size(); ++j)
				{
					if(children.at(j)->GetSize() != nodeSize)
						nodeSize = 0;
				}
			}
			else if(m_nodeSizeStyle == VisualNode::PROPOGATE_CONTINUOUS_SIZE)
			{
				float size = 0.0f;
				for(int j = 0; j < children.size(); ++j)
					size += children.at(j)->GetSize();

				nodeSize = size / children.size();
			}
			else // m_nodeSizeStyle == VisualNode::PROPOGATE_WEIGHTED_SIZE
			{
				float size = 0.0f;
				uint totalWeight = 0;
				for(int j = 0; j < children.size(); ++j)
				{
					uint weight = children.at(j)->GetWeightedNumberOfSeqs();
					totalWeight += weight;

					size += children.at(j)->GetSize() * weight;
				}

				nodeSize = size / totalWeight;
			}
		}

		node->SetSize(nodeSize);
	}

	Layout();
}

void VisualClusterTree::SetBranchColorStyle(const QString& style, const QColor& color)
{
	Log::Inst().Debug("VisualClusterTree::SetBranchColorBy(const QString& style)");

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
		QColor branchColor;
		if(node->IsLeaf())
		{
			// set color of branch based on legend
			Sample sample;
			if(!m_activeSystem->GetSamples()->GetSample(node->GetName(), sample))
				Log::Inst().Error("Invalid sample specified setting node colour: " + node->GetName());

			branchColor = sample.GetColor();
		}
		else
		{
			// set color of branch based on color of children
			QList<VisualBranch*> children = node->GetBranches();
			
			if(m_branchColorStyle == VisualBranch::PROPOGATE_DISCRETE_COLOR)
			{
				branchColor = children.at(0)->GetColor();
				for(int j = 0; j < children.size(); ++j)
				{
					if(children.at(j)->GetColor() != branchColor)
						branchColor = Qt::black;
				}
			}
			else if(m_branchColorStyle == VisualBranch::PROPOGATE_CONTINUOUS_COLOR)
			{
				float red = 0.0f, green = 0.0f, blue = 0.0f;
				for(int j = 0; j < children.size(); ++j)
				{
					QColor color = children.at(j)->GetColor();
					red += color.redF();
					green += color.greenF();
					blue += color.blueF();
				}

				branchColor.setRedF(red / children.size());
				branchColor.setGreenF(green / children.size());
				branchColor.setBlueF(blue / children.size());
			}
			else // m_branchColorStyle == VisualBranch::PROPOGATE_WEIGHTED_COLOR
			{
				float red = 0.0f, green = 0.0f, blue = 0.0f;
				uint totalWeight = 0;
				for(int j = 0; j < children.size(); ++j)
				{
					uint weight = children.at(j)->GetDest()->GetWeightedNumberOfSeqs();
					totalWeight += weight;

					QColor color = children.at(j)->GetColor();
					red += color.redF() * weight;
					green += color.greenF() * weight;
					blue += color.blueF() * weight;
				}

				branchColor.setRedF(red / totalWeight);
				branchColor.setGreenF(green / totalWeight);
				branchColor.setBlueF(blue / totalWeight);
			}
		}

		if(!node->IsRoot())
		{
			node->GetParentBranch()->SetColor(branchColor);
			node->GetParentBranch()->update();
		}
	}
}


void VisualClusterTree::CalculateParsimonyScore(const QString& field)
{
	Log::Inst().Debug("VisualClusterTree::CalculateParsimonyScore(...)");

	if(!m_tree)
		return;

	m_parsimonyCalculator->Calculate(m_tree, m_activeSystem->GetSamples(), field, false);
}

void VisualClusterTree::SetSelectedLeafNodes()
{
	Log::Inst().Debug("VisualClusterTree::SetSelectedLeafNodes(...)");

	if(!m_tree)
		return;

	QSet<uint> selectedSampleIds = m_activeSystem->GetSamples()->GetSelectedSampleIds();

	m_bProcessSelectionUpdates = false;

	QList<VisualNode*> nodes = m_tree->GetNodes();
	foreach(VisualNode* node, nodes)
	{
		node->SetSelected(false);

		if(node->IsLeaf() && selectedSampleIds.contains(node->GetId()))
			node->SetSelected(true);
		else if(node->IsCollapsed())
		{
			bool bContainsSelectedLeaf = false;
			QList<VisualNode*> leaves = TreeTools<VisualNode>::GetLeaves(node);
			foreach(VisualNode* leaf, leaves)
			{
				if(selectedSampleIds.contains(leaf->GetId()))
				{
					node->SetSelected(true);
					node->LabelChanged();	// need label to reflect number of selected leaves
					break;
				}
			}
		}
	}

	m_bProcessSelectionUpdates = true;
}

void VisualClusterTree::UpdateSelectedNodes()
{
	Log::Inst().Debug("VisualClusterTree::UpdateSelectedNodes(...)");

	if(!m_tree)
		return;

	// determine samples which are selected
	QSet<uint> selectedSampleIds;
	QList<VisualNode*> leaves = m_tree->GetLeaves();
	foreach(VisualNode* leaf, leaves)
	{
		if(leaf->IsSelected())
			selectedSampleIds.insert(leaf->GetId());
	}

	m_activeSystem->GetSamples()->SetSamplesToSelected(selectedSampleIds);
}

void VisualClusterTree::ShowContextMenu(QGraphicsSceneContextMenuEvent *event, VisualNode* sourceNode)
{
	QMenu menu;

	// set active set state of node
	menu.addAction("Select subtree");
	menu.addSeparator();

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
		sourceNode->SetSelected(true);
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
}

QString VisualClusterTree::GetMethodMessage() const 
{ 
	if(!m_tree)
		return "";

	return m_tree->GetName() + ", " + VisualTree::GetMethodMessage(); 
}

void VisualClusterTree::VisibleSamplesChanged()
{
	Log::Inst().Debug("VisualClusterTree::VisibleSamplesChanged(...)");

	if(!m_tree)
		return;

	QStringList sampleIdsToRetain;
	foreach(uint activeSampleId, m_activeSystem->GetSamples()->GetActiveSampleIds())
	{
		Sample sample = m_activeSystem->GetSamples()->GetSample(activeSampleId);
		if(sample.IsVisible())
			sampleIdsToRetain.append(sample.GetName());
	}

	Tree<VisualNode>* projectedTree = m_origTree->Clone();
	projectedTree->Project(sampleIdsToRetain);

	// indicate selected nodes
	QSet<uint> selectedNodes;
	QList<VisualNode*> nodes = m_tree->GetNodes();
	foreach(VisualNode* node, nodes)
	{
		if(node->IsSelected())
			selectedNodes.insert(node->GetId());
	}

	QList<VisualNode*> newNodes = projectedTree->GetNodes();
	foreach(VisualNode* node, newNodes)
	{
		if(selectedNodes.contains(node->GetId()))
			node->SetSelected(true);
	}

	VisualTree::SetTree(projectedTree);
	Layout();
}

void VisualClusterTree::GetNumberOfSelectedSeqs(VisualNode* node, float& numSeqs, float& numSelected)
{
	numSeqs = node->GetNumberOfLeaves();
	numSelected = 0;
}

QString VisualClusterTree::GetCategoryInfo(VisualNode* node, const QString& field)
{
	QString categoryInfo;

	Sample sample;
	if(!m_activeSystem->GetSamples()->GetSample(node->GetName(), sample))
		Log::Inst().Error("Invalid sample specified in GetCategoryInfo(): " + node->GetName());

	uint sampleId = sample.GetId();
	QString category  = m_activeSystem->GetSamples()->GetMetadata()->GetValue(field, sampleId);
	categoryInfo += category;
	
	return categoryInfo;
}

void VisualClusterTree::GetCollapsedNodeGradient(const VisualNode* node, QMap<QString, float>& gradientMap, float& totalWeight)
{
	foreach(const VisualNode* leaf, TreeTools<VisualNode>::GetLeaves(node))
	{
		// there is a single color assigned to each leaf node
		QString colorName = leaf->GetColor().name();
		QMap<QString, float>::const_iterator it = gradientMap.find(colorName);
		if(it == gradientMap.end())
			gradientMap[colorName] = 1;
		else
			gradientMap[colorName] = it.value() + 1;

		totalWeight++;
	}
}