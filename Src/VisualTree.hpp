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

#ifndef VISUAL_TREE
#define VISUAL_TREE

#include "stdafx.h"

#include "Tree.hpp"
#include "VisualNode.hpp"
#include "VisualBranch.hpp"
#include "VisualScale.hpp"
#include "VisualAxis.hpp"
#include "VisualSubtreeHighlighter.hpp"
#include "SplitSystem.hpp"
#include "Legends.hpp"

#include "TextSearch.hpp"

class VisualTree: public QObject
{
	Q_OBJECT

public:
	static const int LABEL_OFFSET = 4;

public:
	enum TREE_TYPE { PHYLOGENY, CLUSTER_TREE };
	enum LAYOUT_STYLE { RECTANGULAR_LAYOUT };
	enum BRANCH_STYLE { PHYLOGRAM_BRANCHES, CLADOGRAM_BRANCHES, EQUAL_BRANCHES };
	enum LADDERIZE_DIR { LADDERIZE_BOTTOM, LADDERIZE_TOP };
	enum AUTO_COLLAPSE_CONSTRAINT { DIST_TO_FURTHEST_LEAF_NODE_CONSTRAINT, DIST_TO_ROOT_CONSTRAINT, 
																			TOTAL_BRANCH_LENGTH_CONSTRAINT, CONSISTENCY_INDEX_CONSTRAINT, 
																			SUPPORT_VALUE_CONSTRAINT};
	enum SELECTION_VISUAL { SELECTED_NODE, BOLD_NODE };
	enum LEAF_TREATMENT { DEFAULT_TREATMENT, UNWEIGHTED_TREATMENT, WEIGHTED_TREATMENT, RELATIVE_PROPORITON_TREATMENT };
	enum ABUNDANCE_STYLE { ABUNDANCE_NONE, ABUNDANCE_LABELS_ONLY, ABUNDANCE_PIE_CHART, ABUNDANCE_PIE_CHART_LEAVES_ONLY, ABUNDANCE_COLLAPSED_LEAVES };

public:
	VisualTree(LegendsPtr legends);

	void SetActiveSystem(SystemPtr system);

	virtual TREE_TYPE GetType() const = 0;

	virtual void SetTree(Tree<VisualNode>* tree);
	void SetOriginalTree(Tree<VisualNode>* tree) { m_origTree = tree; }

	LAYOUT_STYLE GetLayoutStyle() const { return m_layoutStyle; }	
	BRANCH_STYLE GetBranchStyle() { return m_branchStyle; }
	LEAF_TREATMENT GetLeafTreatment() { return m_leafTreatment; }

	Tree<VisualNode>* GetTree() const { return m_tree; }
	int GetTreeWidth() const { return m_treeWidth; }
	int GetTreeHeight() const { return m_treeHeight; }

	bool IsVisible() const { return m_bVisible; }
	
	bool IsAlignedTips() const { return m_bAlignedTips; }
	double GetLeafSpacing() const { return m_leafSpacing; }

	QStringList FindNodeLabels(const QString& searchStr, const QString& searchType);

	void Layout();

	void SetNodeFont(const QFont& font, const QColor& color);
	const QFont& GetNodeFont() const { return m_nodeFont; }
	const QColor& GetNodeFontColor() const { return m_nodeFontColor; }

	void SetBranchFont(const QFont& font, const QColor& color);
	const QFont& GetBranchFont() const { return m_branchFont; }
	const QColor& GetBranchFontColor() const { return m_branchFontColor; }

	const VisualNode* GetRootNode() const { return GetTree()->GetRootNode(); }
	const VisualNode* GetDummyRootParent() const { return m_dummyRootParent; }

	double GetRootLength() const { return m_rootLength; }

	VisualBranch::LABEL_TYPE GetBranchLabelType() const { return m_branchLabelType; }
	VisualNode::LABEL_TYPE GetNodeLabelType() const { return m_nodeLabelType; }

	VisualNode::CollapsedProp GetCollapsedNodeProperties() const { return m_collapsedNodeProperties; }
	VisualNode::CollapsedProp GetCollapsedLeafProperties() const { return m_collapsedLeafProperties; }
	
	const VisualScale* GetVisualScale() const { return m_visualScale; }
	const VisualAxis* GetVisualAxis() const { return m_visualAxis; }

	virtual void SetNodeColorStyle(const QString& style, const QColor& color) = 0;
	virtual void SetNodeShapeStyle(const QString& style, const QString& shapeStr) = 0;
	virtual void SetNodeSizeStyle(const QString& style, uint leafSize, uint internalSize) = 0;
	virtual void SetBranchColorStyle(const QString& style, const QColor& color) = 0;

	void SetCollapsedNodeProperties(const VisualNode::CollapsedProp& prop);

	void Ladderize(LADDERIZE_DIR ladderizeDir);

	void SetTreeInspector(QTextBrowser* inspector) { m_treeInspector = inspector; }
	void SetTreeInspectorText(const QString& text) { m_treeInspector->setText(text); }

	virtual void CalculateParsimonyScore(const QString& field) = 0;

	void CollapseNodes(AUTO_COLLAPSE_CONSTRAINT contrainType, float constraint);

	VisualNode* GetActiveSubtreeRoot() { return m_activeSubtreeRoot; }
		
	virtual void SetSelectedLeafNodes() = 0;
	virtual void UpdateSelectedNodes() = 0;
	virtual void GetNumberOfSelectedSeqs(VisualNode* node, float& numSeqs, float& numSelected) = 0;	
	virtual void ShowContextMenu(QGraphicsSceneContextMenuEvent *event, VisualNode* sourceNode) = 0;
	virtual bool IsProcessSelectionUpdates() const = 0;
	virtual QString GetMethodMessage() const;

	SystemPtr GetActiveSystem() const { return m_activeSystem; }
	LegendsPtr GetLegends() const { return m_legends; }

	ABUNDANCE_STYLE GetAbundanceStyle() const { return m_abundanceStyle; }
	uint GetMinAbundanceSize() const { return m_abundanceMinSize; }
	uint GetMaxAbundanceSize() const { return m_abundanceMaxSize; }
	float GetMinAbundance() const { return m_abundanceMin; }
	float GetMaxAbundance() const { return m_abundanceMax; }

	bool GetShowColorCategory() const { return m_bShowColorCategory; }
	bool GetShowShapeCategory() const { return m_bShowShapeCategory; }
	bool GetShowSizeCategory() const { return m_bShowSizeCategory; }

	virtual QString GetCategoryInfo(VisualNode* node, const QString& field) = 0;

	virtual void GetCollapsedNodeGradient(const VisualNode* node, QMap<QString, float>& gradientMap, float& totalWeight) = 0;
	
public slots:	
	void SetVisible(bool visible) { m_bVisible = visible; }

	void SetLayoutStyle(LAYOUT_STYLE layoutStyle);
	void SetBranchStyle(BRANCH_STYLE branchStyle);
	void SetLeafTreatment(LEAF_TREATMENT leafTreatment);
	void SetAbundanceStyle(ABUNDANCE_STYLE abundanceStyle, uint minSize, uint maxSize);

	void CenterOnRoot();
	void CenterOnNode(const QString& nodeLabel);
	
	void SetViewportSize(int width, int height);
	void SetBranchWidth(int width);
	void SetDrawBranchOutline(bool state);
	void SetLeafNodeSize(int size);
	void SetInternalNodeSize(int size);
	
	void SetBranchColor(const QColor& color);
	void SetBranchLabel(const QString& labelType);

	void SetNodeColor(const QColor& color);
	void SetNodeShape(const QString& shapeStr);
	void SetNodeLabel(const QString& labelType);

	void SetRootLength(double length);
	void SetLeafSpacing(int spacing);

	void SetAlignedTips(int aligned) { m_bAlignedTips = aligned; Layout(); }
	
	void Reroot();
	void RotateSelectedBranches();
	void SortAlphabetical();
	void LadderizeBottom() { Ladderize(LADDERIZE_BOTTOM); }
	void LadderizeTop() { Ladderize(LADDERIZE_TOP); }

	void CollapseSelectedNode();
	void CollapseComplementSelectedNode();
	void CollapseComplement(VisualNode* selectedNode);
	void UncollapseAllNodes();
	void CollapseAllNodes();
	void CollapseToScreen();

	void SetScaleVisibility(bool bVisible) { if(!m_visualScale) return; m_visualScale->SetVisibility(bVisible); }
	void SetScaleLength(double length) { if(!m_visualScale) return; m_visualScale->SetScale(length); }
	void SetScaleSignificantDigits(int digits) { if(!m_visualScale) return; m_visualScale->SetSignificantDigits(digits); }
	void SetScaleLineWidth(int width) { if(!m_visualScale) return; m_visualScale->SetLineWidth(width); }
	void SetAutomaticScale(bool bAutomatic) { if(!m_visualScale) return; m_visualScale->SetAutomaticScale(bAutomatic); AutomaticScaleChange(m_visualScale->GetScale()); }
	void SetScaleFont(const QFont& font, const QColor& color) { if(!m_visualScale) return; m_visualScale->SetFont(font, color); }

	void SetAxisLabelVisibility(bool bVisible) {  if(!m_visualAxis) return; m_visualAxis->SetLabelVisibility(bVisible); }
	void SetAxisWidth(int width) { if(!m_visualAxis) return; m_visualAxis->SetWidth(width); }
	void SetAxisFont(const QFont& font, const QColor& color) { if(!m_visualAxis) return; m_visualAxis->SetFont(font, color); }
	void SetAxisData(const QString& field) { if(!m_visualAxis || !IsVisible()) return; m_visualAxis->SetData(m_activeSystem->GetSamples()->GetMetadata(), field); Layout(); }
	
	QGraphicsScene* GetScene() const { return m_scene; }

	uint GetLabelStart() const { return m_labelStart; }

	void SetActiveSubtree(VisualNode* node);

	void LabelCategoriesChanged();
	void SetShowColorCategory(bool bState) { m_bShowColorCategory = bState; UpdateAllLabels(); }
	void SetShowShapeCategory(bool bState) { m_bShowShapeCategory = bState; UpdateAllLabels(); }
	void SetShowSizeCategory(bool bState) { m_bShowSizeCategory = bState;UpdateAllLabels(); }
	
signals:
	void RootLengthChanged(double length);
	void AutomaticScaleChange(double scale);
	void BranchColorStyleChanged();
	void NodeColorStyleChanged();
	void NodeShapeStyleChanged();
	void NodeSizeStyleChanged();
	void AbundanceStyleChanged();
	void NewTreeSet();

protected:
	void ConnectBranchesToNodes();
	void RectangularLayout();

	void LayoutDistanceFromRoot(float rootDepth);
	float LayoutTipNodes();
	void FindTipNodes(VisualNode* node, QList<VisualNode*>& deepestUncollapsedNodes);
	void LayoutInternalNodes(VisualNode* node);
	int FindTreeWidthAndBranchScale();

	double CalculateScaleLength();

	void UpdateNodes();

	float CollapsedLineLength(VisualNode* node, const VisualNode::CollapsedLineProp& prop, uint width) const;

	void CalculateAbundanceExtents();

	void UpdateAllLabels();

protected:
	QGraphicsScene* m_scene;

	Tree<VisualNode>* m_origTree;
	Tree<VisualNode>* m_tree;

	SystemPtr m_activeSystem;
	LegendsPtr m_legends;

	VisualNode* m_activeSubtreeRoot;

	QVector<VisualBranch*> m_branches;

	VisualNode* m_dummyRootParent;

	VisualScale* m_visualScale;
	VisualAxis* m_visualAxis;

	VisualSubtreeHighlighter* m_activeSetHighlighter;

	bool m_bVisible;

	int m_leafSpacing;
	int m_treeWidth;
	int m_treeHeight;

	int m_viewportWidth;
	int m_viewportHeight;

	double m_rootLength;

	TextSearch m_textSearch;

	LAYOUT_STYLE m_layoutStyle;
	BRANCH_STYLE m_branchStyle;
	LEAF_TREATMENT m_leafTreatment;

	ABUNDANCE_STYLE m_abundanceStyle;
	uint m_abundanceMinSize;
	uint m_abundanceMaxSize;
	float m_abundanceMin;
	float m_abundanceMax;

	bool m_bAlignedTips;

	QFont m_nodeFont;
	QColor m_nodeFontColor;
	QFont m_branchFont;
	QColor m_branchFontColor;

	VisualNode::LABEL_TYPE m_nodeLabelType;
	VisualNode::COLOR_STYLE m_nodeColorStyle;
	VisualNode::SIZE_STYLE m_nodeSizeStyle;
	VisualNode::SHAPE_STYLE m_nodeShapeStyle;
	VisualBranch::LABEL_TYPE m_branchLabelType;
	VisualBranch::COLOR_STYLE m_branchColorStyle;

	int m_angularRange;

	VisualNode::CollapsedProp m_collapsedNodeProperties; 
	VisualNode::CollapsedProp m_collapsedLeafProperties;

	QTextBrowser* m_treeInspector;

	uint m_labelStart;

	ParsimonyCalculatorPtr m_parsimonyCalculator;

	bool m_bShowColorCategory;
	bool m_bShowShapeCategory;
	bool m_bShowSizeCategory;
};

#endif