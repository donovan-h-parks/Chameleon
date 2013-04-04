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

#ifndef VISUAL_NODE
#define VISUAL_NODE

class VisualTree;
class VisualBranch;
struct sPARSIMONY_DATA;

class VisualNode: public QGraphicsItem
{
public:
	static const int DEFAULT_LEAF_NODE_SIZE = 9;
	static const int DEFAULT_INTERNAL_NODE_SIZE = 0;

public:
	enum NODE_FLAGS { NO_DISTANCE = INT_MIN };
	enum LABEL_TYPE { NO_LABEL, ASSIGNED_LABEL, ASSIGNED_LEAF_LABEL, DEPTH_LABEL, HEIGHT_LABEL, 
											DISTANCE_TO_ROOT_LABEL, DISTANCE_TO_CLOSEST_LEAF_LABEL, 
											DISTANCE_TO_FURTHEST_LEAF_LABEL, DISTANCE_TO_LEAVES_LABEL,
											CONSISTENCY_INDEX_LABEL, SUPPORT_LABEL };

	enum COLOR_STYLE { SINGLE_COLOR, PROPOGATE_CONTINUOUS_COLOR, PROPOGATE_WEIGHTED_COLOR, PROPOGATE_DISCRETE_COLOR };
	enum SIZE_STYLE { SINGLE_SIZE, LEAVES_ONLY_SIZE, PROPOGATE_CONTINUOUS_SIZE, PROPOGATE_WEIGHTED_SIZE, PROPOGATE_DISCRETE_SIZE };
	enum SHAPE_STYLE { SINGLE_SHAPE, PROPOGATE_DISCRETE_SHAPE };

	enum COLLAPSED_SHAPE { COLLAPSED_TRIANGULAR, COLLAPSED_RECTANGULAR };
	enum COLLAPSED_VARIABLE { COLLAPSED_BRANCH_LENGTH, COLLAPSED_FIXED, COLLAPSED_LEAF_NODE_SPAN, COLLAPSED_SIZE_VAR, COLLAPSED_ABUNDANCE, COLLAPSED_NONE };
	enum COLLAPSED_STATISTIC { COLLAPSED_MAX, COLLAPSED_MIN, COLLAPSED_MEAN, COLLAPSED_MEDIAN, COLLAPSED_TOTAL };
	enum COLLAPSED_GRADIENT_STYLE { COLLAPSED_GRADIENT_CONTINUOUS, COLLAPSED_GRADIENT_DISCRETE, COLLAPSED_GRADIENT_SINGLE_COLOR };
	enum COLLAPSED_GRADIENT_FILL { COLLAPSED_TOP_HALF, COLLAPSED_FULL };

public:
	struct CollapsedLineProp
	{	
		CollapsedLineProp()
			: variable(VisualNode::COLLAPSED_BRANCH_LENGTH), statistic(VisualNode::COLLAPSED_MAX), 
				factor(100.0), minSize(10), maxSize(10000) {}

		CollapsedLineProp(COLLAPSED_VARIABLE _variable, COLLAPSED_STATISTIC _statistics, float _factor,
											uint _minSize, uint _maxSize)
			: variable(_variable), statistic(_statistics), factor(_factor), minSize(_minSize), maxSize(_maxSize) {}
		
		COLLAPSED_VARIABLE variable; 
		COLLAPSED_STATISTIC statistic; 

		float factor;
		uint minSize;
		uint maxSize;
	};

	struct CollapsedProp
	{	
		CollapsedProp()
			: shape(VisualNode::COLLAPSED_RECTANGULAR), bShowLabels(true), bAbundanceInLabel(true),
				gradientStyle(VisualNode::COLLAPSED_GRADIENT_DISCRETE), gradientColor(Qt::lightGray), 
				gradientFill(VisualNode::COLLAPSED_TOP_HALF) {}

		VisualNode::COLLAPSED_SHAPE shape; 
		bool bShowLabels; 
		bool bAbundanceInLabel;

		CollapsedLineProp topLine;
		CollapsedLineProp middleLine;
		CollapsedLineProp bottomLine;
		CollapsedLineProp heightLine;

		VisualNode::COLLAPSED_GRADIENT_STYLE gradientStyle;
		QColor gradientColor;
		VisualNode::COLLAPSED_GRADIENT_FILL gradientFill;
	};

public:
	VisualNode(unsigned int id,  const QString& name = "");
	VisualNode(unsigned int id,  const QString& name, qreal x, qreal y, qreal diameter);

	VisualNode(const VisualNode &rhs);
	VisualNode& operator=(const VisualNode &rhs);

	/** Get id associated with this node. */
	uint GetId() const  { return m_id; }

	/**
	 * @brief Set node's id.
	 * @param id New identity tag.
	 */
	void SetId(uint id) { m_id = id; }

	/** Get id of all children. */
	QList<uint> GetChildrenIds() const;
	  
	/** Get the name associated to this node. */
	const QString& GetName() const	{	return m_name; }
	    
	/**
	 * @brief Set name of node.
	 * @param name Name to give node.
	 */
	void SetName(const QString& name)	{	m_name = name; }

	/** Get the distance to the parent node.	 */     
	float GetDistanceToParent() const { return m_distanceToParent; }
	    
	/**
	 * @brief Set the distance to the parent node.
	 * @param distance Distance to parent node.
	 */
	void SetDistanceToParent(float distance) { m_distanceToParent = distance; }

	/** Get the distance to the root node.	 */     
	float GetDistanceToRoot() const { return m_distanceToRoot; }
	    
	/**
	 * @brief Set the distance to the root node.
	 * @param distance Distance to root node.
	 */
	void SetDistanceToRoot(float distance) { m_distanceToRoot = distance; }

	/** Get distance to the furthest leafnode. */
	float GetDistanceToFurthestLeafNode() const { return m_distanceToFurthestLeafNode; }

	/** set distance to the furthest leafnode. */
	void SetDistanceToFurthestLeafNode(float distance) { m_distanceToFurthestLeafNode = distance; }

	/** Get distance to the closest leaf node. */
	float GetDistanceToClosestLeafNode() const { return m_distanceToClosestLeafNode; }

	/** Set distance to the closest leaf node. */
	void SetDistanceToClosestLeafNode(float distance) { m_distanceToClosestLeafNode = distance; }

	/** Get total branch length in subtree rooted at this node. */
	float GetTotalBranchLength() const { return m_totalBranchLength; }

	/** Set total branch length in subtree rooted at this node. */
	void SetTotalBranchLength(float branchLength) { m_totalBranchLength = branchLength; }

	/** Get height of node (i.e., length of longest path to a leaf node). */
	int GetHeight() const { return m_height; }

	/** Set height of node (i.e., length of longest path to a leaf node). */
	void SetHeight(int height) { m_height = height; }

	/** Get depth of node (i.e., length of path to root). */
	int GetDepth() const { return m_depth; }

	/** Set depth of node (i.e., length of path to root). */
	void SetDepth(int depth) { m_depth = depth; }

	/** Get the bootstap value for this node.	 */     
	int GetSupport() const { return m_support; }
	    
	/**
	 * @brief Set the support value for this node.
	 * @param support Support value of node.
	 */
	void SetSupport(int support) { m_support = support; }

	/** Number of leaf nodes in subtree rooted at this node.*/
	uint GetNumberOfLeaves() { return m_numOfLeaves; }

	/** Number of leaf nodes in subtree rooted at this node.*/
	void SetNumberOfLeaves(uint n) { m_numOfLeaves = n; }

	/** Number of sequences in subtree rooted at this node (unweighted count).*/
	uint GetNumberOfSeqs() const { return m_numOfSeqs; }

	/** Number of sequences in subtree rooted at this node (unweighted count).*/
	void SetNumberOfSeqs(uint n) { m_numOfSeqs = n; }

	/** Number of sequences in subtree rooted at this node (accounts for weight of each unique seqs).*/
	uint GetWeightedNumberOfSeqs() const { return m_weightedNumOfSeqs; }

	/** Number of sequences in subtree rooted at this node (accounts for weight of each unique seqs).*/
	void SetWeightedNumberOfSeqs(uint n) { m_weightedNumOfSeqs = n; }

	/** Relative proportion of sequences in subtree rooted at this node (accounts for weight of each unique seqs).*/
	float GetRelativeProportionOfSeqs() const { return m_relativeProportionOfSeqs; }

	/** Relative proportion of sequences in subtree rooted at this node (accounts for weight of each unique seqs).*/
	void SetRelativeProportionOfSeqs(float n) { m_relativeProportionOfSeqs = n; }
	  
	/** Get parent of this node. */     
	VisualNode* GetParent() const  { return m_parent; }
	    
	/**
	 * @brief Set the parent node.
	 * @param node Parent node.
	 */
	void SetParent(VisualNode* parent) { m_parent = parent; }
	    
	/** Remove the parent node. */
	VisualNode* RemoveParent() { VisualNode* p = m_parent; m_parent = NULL; return p; }
	    
	/** Indicate if this node is the root node.	 */
	bool IsRoot() const { return m_parent == NULL; }

	/** Get number of child nodes. */	     
	uint GetNumberOfChildren() const { return m_children.size(); }
    
	/** 
	 * @brief Get specified child node. 
	 * @param pos Indicates child that should be returned.
	 * @return Child at specified index position.
	 */
	VisualNode* GetChild(uint pos) const;
	    
	/** 
	 * @brief Add child node at specified index position. 
	 * @param pos Position to add child.
	 * @param node Child node to add.
	 */
	void AddChild(uint pos, VisualNode* node);

	/** 
	 * @brief Add child node.
	 * @param node Child node to add.
	 */
	void AddChild(VisualNode* node);
    
	/** 
	 * @brief Remove child node.
	 * @param pos Specifies which child to remove.
	 */
	void RemoveChild(uint pos);

	/** 
	 * @brief Remove child node.
	 * @param node Node to be removed.
	 */
	void RemoveChild(VisualNode* node);

	/** Remove all child nodes. */
	void RemoveChildren();
	    
	/**
	 * @brief Get position of specified child node.
	 * @param child Child node to determine position of.
	 * @return Position of child node.
	 */
	uint GetChildPosition(VisualNode* child) const;

	/** Get all child nodes. */
	QList<VisualNode*> GetChildren() const { return m_children; }
	    
	/** Check if node is a leaf node. */
	bool IsLeaf() const  { return m_children.empty(); }

	/** 
	 * @brief Swap the position of the two indicated children.
	 * @brief pos1 Position of first child.
	 * @brief pos2 Position of second child.
	 */
	void Swap(uint pos1, uint pos2);

	/** 
	 * @brief Rotate the position of the children nodes.
	 */
	void Rotate();

	/** Check if node has been processed. */
	bool IsProcessed() const { return m_bProcessed; }

	/**
	 * @brief Set processed flag.
	 * @param processed Set node to processed (true) or unprocessed (false).
	 */
	void SetProcessed(bool processed) { m_bProcessed = processed; }

	/** Check if node is in the active set. */
	bool IsActiveSet() const { return m_bActiveSet; }

	/**
	 * @brief Set whether not is within the current active set. 
	 * @param active Set node to be in (true) or out (false) of the active set.
	 */
	void SetActiveSet(bool active) { m_bActiveSet = active; }

	void SetTree(VisualTree* tree);
	VisualTree* GetTree() const { return m_tree; }

	void SetSize(qreal diameter);
	float GetSize() const;

	QColor GetColor() const { return m_color; }
	void SetColor(const QColor& color);

	QwtSymbol::Style GetShape() const { return m_shape; }
	void SetShape(const QwtSymbol::Style& shape);

	void SetTextHighlight(bool highlight);
	bool IsTextHighlight() const { return m_bTextHighlight; }

	void SetCollapsedInternal(bool bCollapsed);
	void SetCollapsedLeaf(bool bCollapsed);
	bool IsCollapsed() const { return m_bCollapsed; }
	
	VisualBranch* GetParentBranch() { return m_parentBranch; }
	void SetParentBranch(VisualBranch* branch) { m_parentBranch = branch; }

	void ClearBranches() { m_branches.clear(); }
	void AddBranch(VisualBranch* branch) { m_branches.append(branch); }
	QList<VisualBranch*> GetBranches() const { return m_branches; }

	QString GetLabel() const { return m_label; }
	float GetLabelWidth() const;
	float GetLabelHeight() const;

	void SetCollapsedLabel(const QString& label);

	void LabelChanged();
	void FontChanged();

	QRectF boundingRect() const;

	void CollapsedNodeLineLengths(float& lengthBL, float& lengthML, float& lengthTL, float& height) const;

	void SetParsimonyData(sPARSIMONY_DATA* data) { m_parsimonyData = data; }
	sPARSIMONY_DATA* GetParsimonyData() const { return m_parsimonyData; }

	void SetSubtreeAsActive(bool bOnlySubtree);
	void SelectSubtree();
	void UnselectSubtree();

	void SetSelected(bool state, bool bUpdateGUI = true);
	bool IsSelected() const { return m_bSelected; }

	void SetBold(bool state) { m_bBold = state; }
	bool IsBold() const { return m_bBold; }

public slots:		
	void ToggleCollapsedInternal();

protected:
	void Initialize();

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void PaintLeaf(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, const QString& label);
	void PaintPieChart(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, const QString& label);

	void PaintCollapsedNode(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	
	void DrawCollapsedPolygon(QPainter* painter) const;

	void DrawSymbol(QPainter* painter, QwtSymbol::Style symbol, const QRectF& r) const;

	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	void hoverEnterEvent(QGraphicsSceneHoverEvent * event);

	float CollapsedLineLength(const CollapsedLineProp& prop) const;

	uint GetPieChartSize() const;

	QVariant itemChange(GraphicsItemChange change, const QVariant & value);

private:
	/** Unique id identifying node. */
  uint m_id;

	/** Name of node. */
  QString m_name;

	/** Children of node. */
  QList<VisualNode*> m_children;

	/** Parent of node. */
	VisualNode* m_parent;

	/** Distance to parent of this node. */
  float m_distanceToParent; 

	/** Distance to the root node. */
	float m_distanceToRoot;

	/** Distance to closest leaf node. */
	float m_distanceToClosestLeafNode;

	/** Distance to furthest leaf node.*/
	float m_distanceToFurthestLeafNode;

	/** Total branch length in subtree rooted at this node. */
	float m_totalBranchLength;

	/** Height of node (i.e., length of longest path to a leaf node). */
	int m_height;

	/** Depth of node (i.e., length of path to root). */
	int m_depth;

	/** Support for bipartition induced by node (e.g., bootstrap or jackknife support value). */
	int m_support;

	/** General-purpose flag. */
	bool m_bProcessed;

	float m_diameter;

	QString m_label;
	float m_labelWidth;
	float m_labelHeight;

	QString m_collapsedLabel;

	QColor m_color;
	QwtSymbol::Style m_shape;

	VisualTree* m_tree;

	bool m_bTextHighlight;

	bool m_bCollapsed;

	VisualBranch* m_parentBranch;
	QList<VisualBranch*> m_branches;

	sPARSIMONY_DATA* m_parsimonyData;

	/** Flag indicating if node is in the current active set. */
	bool m_bActiveSet;

	/** Flag indicating if node is in the selection set. */
	bool m_bSelected;

	/** Flag indicating if node text should be in bold. */
	bool m_bBold;

	/** Number of leaf nodes in subtree rooted at this node.*/
	uint m_numOfLeaves;

	/** Number of sequences in subtree rooted at this node (unweighted count).*/
	uint m_numOfSeqs;

	/** Number of sequences in subtree rooted at this node (accounts for weight of each unique seqs).*/
	uint m_weightedNumOfSeqs;

	/** Relative proportion of sequences in subtree rooted at this node (accounts for weight of each unique seqs). */
	float m_relativeProportionOfSeqs;
};

#endif