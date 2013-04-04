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

#ifndef VISUAL_PHYLOGENY
#define VISUAL_PHYLOGENY

#include "stdafx.h"

#include "VisualTree.hpp"
#include "SeqMetadata.hpp"
#include "ColorMaps.hpp"

class VisualPhylogeny: public VisualTree
{
	Q_OBJECT

public:
	VisualPhylogeny(SplitSystemPtr splitSystem, LegendsPtr legends, ColorMapsPtr colorMaps);

	virtual TREE_TYPE GetType() const { return PHYLOGENY; }

	virtual void SetTree(Tree<VisualNode>* tree);

	virtual void SetNodeColorStyle(const QString& style, const QColor& color);
	virtual void SetNodeShapeStyle(const QString& style, const QString& shapeStr);
	virtual void SetNodeSizeStyle(const QString& style, uint leafSize, uint internalSize);
	virtual void SetBranchColorStyle(const QString& style, const QColor& color);

	void CalculateParsimonyScore(const QString& field);

	void SetSelectedLeafNodes();
	void UpdateSelectedNodes() { /** do nothing */ }
	bool IsProcessSelectionUpdates() const { return false; }

	void ShowContextMenu(QGraphicsSceneContextMenuEvent *event, VisualNode* sourceNode);

	void GetNumberOfSelectedSeqs(VisualNode* node, float& numSeqs, float& numSelected);

	QString GetCategoryInfo(VisualNode* node, const QString& field);

	bool GetUseSequenceMetadata() const { return m_bUseSequenceMetadata; }
	void SetUseSequenceMetadata(bool bState);

	SeqMetadataPtr GetSeqMetadata() { return m_seqMetadata; }

	void GetCollapsedNodeGradient(const VisualNode* node, QMap<QString, float>& gradientMap, float& totalWeight);

public slots:
	void RestoreActiveSampleTree();
	void ProjectToSelectedLeaves();

	void SetPhylogenyMetadataCategories(const QString& category);
	void SetPhylogenyMetadataColorMap(const QString& colorMap);
	void SetPhylogenyOtherPercentage(double percentage);

private:
	void ProjectTo(const QStringList& leavesToRetain);

private:
	bool m_bUseSequenceMetadata;

	SeqMetadataPtr m_seqMetadata;
};

#endif