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

#ifndef VISUAL_CLUSTER_TREE
#define VISUAL_CLUSTER_TREE

#include "stdafx.h"

#include "VisualTree.hpp"

class VisualClusterTree: public VisualTree
{
	Q_OBJECT

public:
	VisualClusterTree(LegendsPtr legends);

	virtual TREE_TYPE GetType() const { return CLUSTER_TREE; }

	virtual void SetTree(Tree<VisualNode>* tree);

	void SetNodeColorStyle(const QString& style, const QColor& color);
	void SetNodeShapeStyle(const QString& style, const QString& shapeStr);
	void SetNodeSizeStyle(const QString& style, uint leafSize, uint internalSize);
	void SetBranchColorStyle(const QString& style, const QColor& color);

	void CalculateParsimonyScore(const QString& field);

	void SetSelectedLeafNodes();
	void UpdateSelectedNodes();

	void ShowContextMenu(QGraphicsSceneContextMenuEvent *event, VisualNode* sourceNode);

	bool IsProcessSelectionUpdates() const { return m_bProcessSelectionUpdates; }

	QString GetMethodMessage() const;

	void GetNumberOfSelectedSeqs(VisualNode* node, float& numSeqs, float& numSelected);

	QString GetCategoryInfo(VisualNode* node, const QString& field);

	void GetCollapsedNodeGradient(const VisualNode* node, QMap<QString, float>& gradientMap, float& totalWeight);

public slots:
	void VisibleSamplesChanged();

private:
	bool m_bProcessSelectionUpdates;

	UniSplitPtr m_uniSplit;
};

#endif