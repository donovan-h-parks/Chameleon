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

#ifndef _TREE_
#define _TREE_

#include "stdafx.h"

#include "TreeTools.hpp"
#include "Log.hpp"
#include "Samples.hpp"

/**
 * @brief Build a new tree. The nodes of the tree can be any class derived from Node.
 *
 * Code example:
 * @code
 * @endcode
 *
 * @see Node
 */
template<class N> class Tree
{
public:
	static const uint ROOT_ID = INT_MAX;

public:	
	/** Constructor. */
	Tree(): m_root(NULL), m_name(""), m_numberOfLeaves(0), m_numberOfNodes(0)  {}

	/**
	 * @brief Constructor
	 * @param root Root of tree.
	 */
	Tree(N* root): m_root(root), m_name(""), m_numberOfLeaves(0), m_numberOfNodes(0) {}

	/** Copy constructor. */
	Tree(const Tree<N>& t);

	/** Assignment operator. */
	Tree<N>& operator=(const Tree<N>& t);

	/** Destructor. */
	~Tree();

	/** Clone tree. */
	Tree<N> * Clone() const { return new Tree<N>(*this); }

public:
	/** Get name of tree. */
	QString GetName() const  { return m_name; }

	/**
	 * @brief Set name of tree.
	 * @param name Desired name of tree.
	 */		
	void SetName(const QString& name) { m_name = name; }

	/** 
	 * @brief Set root node of tree.
	 * @param root Desired root node.
	 */
	void SetRootNode(N* root) 
	{ 
		m_root = root; 
		m_root->SetParent(NULL); 
		m_root->SetDistanceToParent(VisualNode::NO_DISTANCE); 
	}

	/** Get root node. */
	N* GetRootNode() const { return m_root; }

	/** Get id of root node. */
	unsigned int GetRootId() const { return m_root->GetId(); }

	/** Get node with the given id. */	
	N* GetNode(unsigned int id) const; 

	/** Get node with the given name. */
	N* GetNode(const QString& name) const;

	/** Get number of leaf nodes in tree. */
	unsigned int GetNumberOfLeaves() const { return m_numberOfLeaves; }

	/** Get all leaf nodes in tree. */
	QList<N*> GetLeaves() const { return TreeTools<N>::GetLeaves(m_root); }

	/** Get id of all leaf nodes. */
	QList<unsigned int> GetLeafIds() const { return TreeTools<N>::GetLeafIds(m_root); }

	/** Get name of all leaf nodes in depth first order. */
	QStringList GetLeafNames() const { return TreeTools<N>::GetLeafNames(m_root); }

	/** Get number of nodes in tree. */
	unsigned int GetNumberOfNodes() const { return m_numberOfNodes; }

	/** Get all nodes in tree. */
	QList<N*> GetNodes() const { return TreeTools<N>::GetNodes(m_root); }

	/** Get id of all nodes. */
	QList<unsigned int> GetNodesId() const { return TreeTools<N>::GetNodesId(m_root); }

	/** Get length of all branches. */
	QList<double> GetBranchLengths() const { return TreeTools<N>::GetBranchLengths(m_root); }

	/** Get depth of a give node (i.e. the maximum number of children 'generations'). */
	unsigned int GetDepth(N* node) const { return TreeTools<N>::GetDepth(node); }

	/** Get distance to furthest leaf node. */
	double GetDistToFurthestLeafNode(N* node) const { return TreeTools<N>::GetDistToFurthestLeafNode(node); }

	/** Get distance to root. */
	double GetDistToRoot(N* node) const { return TreeTools<N>::GetDistToRoot(node); }

	/** 
	 * @brief Get id of all children to the given node. 
	 * @param parentId Id of parent node.
	 * @return Id of all chilren to the node with the given id.
	 */
	QList<unsigned int> GetChildrenIds(unsigned int parentId) const { return GetNode(parentId)->GetChildrenIds(); }

	/** 
	 * @brief Get id of parent node to the given node.
	 * @param nodeId Id of node of interest.
	 * @return Id of parent node.
	 */
	unsigned int GetParentId(unsigned int nodeId) const { return GetNode(nodeId)->GetParentId(); }

	/** 
	 * @brief Get name of node.
	 * @param nodeId Id of node of interest.
	 * @return Name of node.
	 */
	QString GetNodeName(int nodeId) const { return GetNode(nodeId)->GetName(); }

	/** 
	 * @brief Set name of node.
	 * @param nodeId Id of node of interest.
	 * @param name Desired name of node.
	 */
	void SetNodeName(int nodeId,  const QString& name) { GetNode(nodeId)->SetName(name); }

	/** 
	 * @brief Indicate if tree has a node with a given id.
	 * @param nodeId Id to check.
	 * @return True if tree has a node with the given id.
	 */
	bool HasNode(unsigned int nodeId) const { return TreeTools<N>::HasNodeWithId(m_root, nodeId); }

	/** 
	 * @brief Indicate if node is a leaf.
	 * @param nodeId Id of node of interest.
	 * @return True if node is a leaf.
	 */
	bool IsLeaf(unsigned int nodeId) const { return GetNode(nodeId)->IsLeaf(); }

	/** 
	 * @brief Indicate if node is the root.
	 * @param nodeId Id of node of interest.
	 * @return True if node is the root.
	 */
	bool IsRoot(unsigned int nodeId) const { return TreeTools<N>::IsRoot(GetNode(nodeId)); }

	/** 
	 * @brief Get distance to parent node for the specified node.
	 * @param nodeId Id of node of interest.
	 * @return Distance to parent node.
	 */
	double GetDistanceToParent(unsigned int nodeId) const { return GetNode(nodeId)->GetDistanceToParent(); }

	/** 
	 * @brief Set distance to parent node from the specified node.
	 * @param nodeId Id of node of interest.
	 * @param dist Distance to parent node.
	 */
	void SetDistanceToParent(unsigned int nodeId, double dist)  { GetNode(nodeId)->SetDistanceToParent(dist); }
		
	/** 
	 * @brief Reset node ids so they are all unique values.
	 * @param nodeId Id of node of interest.
	 * @param dist Distance to parent node.
	 */
	void ResetNodeIds();
	
	/** Indicate if tree is multifurcating. */
	bool IsMultifurcating() const;
	
	/** Get total length of all branches in tree. */
	double GetTotalLength() const;

	/** 
	 * @brief Set all branches to the specified length.
	 * @param length Desired length.
	 */
	void SetBranchLengths(double length);

	/** 
	 * @brief Set all nodes to the specified size.
	 * @param size Desired size.
	 */
	void SetSize(int size);

	/** 
	 * @brief Set all leaf nodes to the specified size.
	 * @param size Desired size.
	 */
	void SetLeafSize(int size);

	/** 
	 * @brief Set all internal nodes to the specified size.
	 * @param size Desired size.
	 */
	void SetInternalSize(int size);


	/**
	 * @brief Scale tree distances by a constant factor.
	 * @param factor Amount to scale tree distances by.
	 */
	void ScaleTree(double factor);

  /** 
	 * @brief Reroot tree half way between parantal branch of specified node.
	 * @param node Node to reroot tree on.
	 */
	void Reroot(N* node);
 
	/**
	 * @brief Project tree onto the specified set of leaf nodes.
	 * @param leavesToRetain List of leave nodes to retain in tree.
	 */
	void Project(const QStringList& leavesToRetain);

	/** Get height of the tree. */
	int GetTreeHeight() { return m_root->GetHeight(); }

	/** Get distance to the furthest leaf node. */
	float GetDistanceToFurthestLeafNode() { return m_root->GetDistanceToFurthestLeafNode(); }

	/** Get distance to the closest leaf node. */
	float GetDistanceToClosestLeafNode() { return m_root->GetDistanceToClosestLeafNode(); }

	/**
	 * @brief Calculate commonly needs statistics for tree.
	 **/
	void CalculateStatistics(SamplesPtr samples);

	/** Node nodes in post-order traversal order. */
	QList<N*> PostOrder() { return TreeTools<N>::PostOrder(m_root); }

protected:		
		void DestroySubtree(N* node);

		void CalculatePostOrderStatistics(N* node, SamplesPtr samples);

protected:
	N* m_root;
	QString m_name;		

	uint m_numberOfLeaves;
	uint m_numberOfNodes;
};

// --- Function implementations -----------------------------------------------

template <class N>
Tree<N>::Tree(const Tree<N>& t)
  : m_root(NULL), m_name(t.GetName()), m_numberOfLeaves(t.GetNumberOfLeaves()), m_numberOfNodes(t.GetNumberOfNodes())
{	
	Log::Inst().Debug("Tree<N>::Tree(const Tree<N>& t)");

	//Perform a hard copy of the nodes:
	m_root = TreeTools<N>::CloneSubtree(t.GetRootNode());
}

template <class N>
Tree<N>& Tree<N>::operator=(const Tree<N>& t)
{
	// Free memory allocated to LHS tree
	if(m_root) 
	{ 
		DestroySubtree(m_root); 
		delete m_root; 
	}

	// Perform hard copy of nodes on RHS
  m_root = TreeTools<N>::CloneSubtree(t.GetRootNode());
  m_name = t.m_name;

	return *this;
}

template <class N>
Tree<N>::~Tree()
{
	/*
	if(m_root)
	{
		DestroySubtree(m_root);

		if(m_root)
		{
			delete m_root;
			m_root = NULL;
		}
	}
	*/
}
	
template <class N>
void Tree<N>::DestroySubtree(N* node)
{
	/*
	for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
	{
		N* child = node->GetChild(i);
		DestroySubtree(child);

		if(child)
		{
			delete child;
			child = NULL;
		}
	}
	*/
}

template <class N>
N* Tree<N>::GetNode(unsigned int id) const
{
	QList<N*> nodes = TreeTools<N>::SearchNodeWithId(m_root, id);

	if(nodes.size() > 1)
	{
		Log::Inst().Error("Multiple nodes have the same id = " + QString(id));
		return NULL;
	}
	else if(nodes.size() == 0)
	{
		Log::Inst().Error("No nodes with the provided id = " + QString(id));
		return NULL;
	}

	return nodes[0];
}

template <class N>
N* Tree<N>::GetNode(const QString& name) const
{
	QList<N*> nodes = TreeTools<N>::SearchNodeWithName(m_root, name);

	if(nodes.size() > 1)
	{
		Log::Inst().Error("Multiple nodes have the same name = " + name);
		return NULL;
	}
	else if(nodes.size() == 0)
	{
		Log::Inst().Error("No nodes with the provided name = " + name);
		return NULL;
	}

	return nodes[0];
}

template <class N>
void Tree<N>::ResetNodeIds()
{
	QList<N*> nodes = GetNodes();
	for(unsigned int i = 0; i < nodes.size(); i++)
  {
    nodes[i]->SetId(i);
  }
}

template <class N>
bool Tree<N>::IsMultifurcating() const
{
	bool b = false;
	for(unsigned int i = 0; i < m_root->GetNumberOfChildren(); i++)
  {
		b = b || TreeTools<N>::IsMultifurcating(m_root->GetChild(i));
	}
	return b;
}

template <class N>
double Tree<N>::GetTotalLength() const
{
	double length = 0;
	for(unsigned int i = 0; i < m_root->GetNumberOfChildren(); i++)
  {
    length += TreeTools<N>::GetTotalLength(m_root->GetChild(i));
  }
  return length;
}

template <class N>
void Tree<N>::SetBranchLengths(double length)
{
	for(unsigned int i = 0; i < m_root->GetNumberOfChildren(); i++)
  {
    TreeTools<N>::SetBranchLengths(m_root->GetChild(i), length);
  }
}

template <class N>
void Tree<N>::SetSize(int size)
{
	m_root->SetSize(size);
	for(uint i = 0; i < m_root->GetNumberOfChildren(); i++)
  {
    TreeTools<N>::SetSize(m_root->GetChild(i), size);
  }
}

template <class N>
void Tree<N>::SetLeafSize(int size)
{
	for(uint i = 0; i < m_root->GetNumberOfChildren(); i++)
  {
    TreeTools<N>::SetLeafSize(m_root->GetChild(i), size);
  }
}

template <class N>
void Tree<N>::SetInternalSize(int size)
{
	m_root->SetSize(size);
	for(uint i = 0; i < m_root->GetNumberOfChildren(); i++)
  {
    TreeTools<N>::SetInternalSize(m_root->GetChild(i), size);
  }
}

template <class N>
void Tree<N>::ScaleTree(double factor)
{
	for(unsigned int i = 0; i < m_root->GetNumberOfChildren(); i++)
  {
	  TreeTools<N>::ScaleTree(m_root->GetChild(i), factor);
  }
}

template <class N>
void Tree<N>::Reroot(N* node)
{
	if(node->IsRoot())
		return;

	QList<N*> rootChildren = m_root->GetChildren();
	m_root->RemoveChildren();

	N* parentNode = node->GetParent();

	N* prevNode;
	if(!parentNode->IsRoot() && parentNode->GetParent()->GetName() != "dummy root")
	{
		m_root->AddChild(node);
		node->SetDistanceToParent(0.5*node->GetDistanceToParent());

		// add parent of selected subtree as a child to new root
		N* curNode = parentNode->GetParent();	
		m_root->AddChild(parentNode);
		parentNode->RemoveChild(node);

		double prevDistToParent = parentNode->GetDistanceToParent();
		parentNode->SetDistanceToParent(node->GetDistanceToParent());	// this is already halved above

		float prevBootstrap = parentNode->GetSupport();
		parentNode->SetSupport(node->GetSupport());

		// reorganize tree from selected node to the previous root		
		prevNode = parentNode;
		while(!curNode->IsRoot() && curNode->GetParent()->GetName() != "dummy root")
		{
			N* parentNode = curNode->GetParent();
			prevNode->AddChild(curNode);
			curNode->RemoveChild(prevNode);
			double distToParent = curNode->GetDistanceToParent();
			curNode->SetDistanceToParent(prevDistToParent);
			float tempBootstrap = curNode->GetSupport();
			curNode->SetSupport(prevBootstrap);
			prevBootstrap = tempBootstrap;

			prevNode = curNode;
			curNode = parentNode;
			prevDistToParent = distToParent;
		}

		// add children of previous root to newly rooted tree
		foreach(N* child, rootChildren)
		{
			if(child != prevNode)
			{
				prevNode->AddChild(child);
				child->SetDistanceToParent(child->GetDistanceToParent() + prevDistToParent);
			}
		}
	}
	else
	{
		double halfRootBranchLength = 0.5*node->GetDistanceToParent();
		foreach(N* child, rootChildren)
		{
			m_root->AddChild(child);
			if(child == node)
				child->SetDistanceToParent(halfRootBranchLength);
			else
				child->SetDistanceToParent(halfRootBranchLength + child->GetDistanceToParent());
		}
	}

	QList<N*> children = m_root->GetChildren();
	foreach(N* child, children)
	{
		if(!child->IsLeaf())
			child->SetSupport(node->GetSupport());
	}
}

template <class N>
void Tree<N>::Project(const QStringList& leavesToRetain)
{
	// mark all internal node as active so we can distinguish them from true leaf nodes
	QList<N*> nodes = GetNodes();
	foreach(N* node, nodes)
		node->SetProcessed(!node->IsLeaf());

	// 1. Removes leave nodes from the tree.
	QSet<QString> leavesToRetainSet = leavesToRetain.toSet();
	foreach(N* leaf, GetLeaves())
	{
		if(!leavesToRetainSet.contains(leaf->GetName()))
		{
			leaf->GetParent()->RemoveChild(leaf);
			delete leaf;
		}
	}

	// 2. Collapse any internal nodes that have less than 2 children. This
	// is done in a breadth first manner from the leaf nodes to the root node.
	QList<N*> curNodes = GetLeaves();
	QSet<N*> nextNodes;
	while(!curNodes.empty())
	{
		nextNodes.clear();
		foreach(N* node, curNodes)
		{
			if(!node->IsRoot())
				nextNodes.insert(node->GetParent());

			if(node->IsProcessed() && node->GetNumberOfChildren() == 0)
			{
				if(node->IsRoot())
				{
					// we have a root with no children so just leave it as the sole node in the tree
				}
				else
				{
					// remove this node from the tree
					node->GetParent()->RemoveChild(node);
					nextNodes.remove(node);
					delete node;
				}
			}
			else if(node->IsProcessed() && node->GetNumberOfChildren() == 1)
			{		
				if(node->IsRoot())
				{
					// the root is degenerate so we must make its sole child the new root
					SetRootNode(node->GetChild(0));
					node->GetChild(0)->SetParent(NULL);
					node->GetChild(0)->SetDistanceToParent(VisualNode::NO_DISTANCE);
					nextNodes.remove(node);
					delete node;
				}
				else
				{
					// remove node from tree after assigning its sole child to its parent
					node->GetParent()->AddChild(node->GetChild(0));	
					
					if(node->GetChild(0)->GetDistanceToParent() != VisualNode::NO_DISTANCE)
					{
						// keep track of branch lengths
						node->GetChild(0)->SetDistanceToParent(node->GetChild(0)->GetDistanceToParent() 
																											+ node->GetDistanceToParent()); 
					}

					node->GetParent()->RemoveChild(node);
					nextNodes.remove(node);
					delete node;
				}
			}	
		}

		curNodes = nextNodes.toList();
	}

	CalculateStatistics(SamplesPtr());
}

template <class N>
void Tree<N>::CalculateStatistics(SamplesPtr samples)
{
	m_root->SetDepth(0);
	m_root->SetDistanceToRoot(0.0f);

	// perform depth first traversal to calculate:
	//  1. depth of all nodes
	//  2. distance from each node to the root
	//  3. number of nodes in tree
	//  4. number of leaf nodes in tree
	QStack<N*> stack;
	for(uint i = 0; i < m_root->GetNumberOfChildren(); ++i)
		stack.push(m_root->GetChild(i));

	m_numberOfNodes = 1;	// remember to count the root node
	m_numberOfLeaves = 0;
	while(!stack.isEmpty())
	{
		N* curNode = stack.pop();
		m_numberOfNodes++;

		for(uint i = 0; i < curNode->GetNumberOfChildren(); ++i)
			stack.push(curNode->GetChild(i));

		curNode->SetDepth(curNode->GetParent()->GetDepth() + 1);
		curNode->SetDistanceToRoot(curNode->GetParent()->GetDistanceToRoot() + curNode->GetDistanceToParent());

		if(curNode->IsLeaf())
			m_numberOfLeaves++;
	}

	// perform post-order traversal to calculate:
	//  1. height of all nodes
	//  2. distance to furthest leaf node
	//  3. distance to closest leaf node
	//  4. number of leaf nodes
	//  5. number of sequences
	CalculatePostOrderStatistics(m_root, samples);
}

template <class N>
void Tree<N>::CalculatePostOrderStatistics(N* node, SamplesPtr samples)
{
	if(node->IsLeaf())
	{
		node->SetHeight(0);
		node->SetDistanceToFurthestLeafNode(0.0f);
		node->SetDistanceToClosestLeafNode(0.0f);
		node->SetTotalBranchLength(0.0f);
		node->SetNumberOfLeaves(0);

		if(samples)
		{
			uint numSeqs = 0;
			uint weightedNumSeqs = 0;
			float relativeProp = 0.0f;
			QList<uint> sampleIds = samples->GetSequences()->GetSampleIdsFromSeqId(node->GetId());
			foreach(uint sampleId, sampleIds)
			{
				numSeqs += uint(samples->GetSequences()->GetNumSequences(node->GetId(), sampleId) > 0);
				weightedNumSeqs += samples->GetSequences()->GetNumSequences(node->GetId(), sampleId);
				relativeProp += samples->GetSequences()->GetRelativeProportionOfSeqs(node->GetId(), sampleId);
			}

			node->SetNumberOfSeqs(numSeqs);
			node->SetWeightedNumberOfSeqs(weightedNumSeqs);
			node->SetRelativeProportionOfSeqs(relativeProp);
		}
		else
		{
			node->SetNumberOfSeqs(1);
			node->SetWeightedNumberOfSeqs(1);
			node->SetRelativeProportionOfSeqs(1);
		}

		return;
	}

	node->SetHeight(0);
	node->SetDistanceToFurthestLeafNode(0.0f);
	node->SetDistanceToClosestLeafNode((float)INT_MAX);
	node->SetTotalBranchLength(0.0f);
	node->SetNumberOfLeaves(0);
	node->SetNumberOfSeqs(0);
	node->SetWeightedNumberOfSeqs(0);
	node->SetRelativeProportionOfSeqs(0);
	foreach(N* child, node->GetChildren())
	{
		CalculatePostOrderStatistics(child, samples);

		if(child->GetHeight() >= node->GetHeight())
			node->SetHeight(child->GetHeight() + 1);

		if(child->GetDistanceToFurthestLeafNode() + child->GetDistanceToParent() > node->GetDistanceToFurthestLeafNode())
			node->SetDistanceToFurthestLeafNode(child->GetDistanceToFurthestLeafNode() + child->GetDistanceToParent());

		if(child->GetDistanceToClosestLeafNode() + child->GetDistanceToParent() < node->GetDistanceToClosestLeafNode())
			node->SetDistanceToClosestLeafNode(child->GetDistanceToClosestLeafNode() + child->GetDistanceToParent());

		node->SetTotalBranchLength(node->GetTotalBranchLength() + child->GetTotalBranchLength() + child->GetDistanceToParent());
		
		if(child->IsLeaf())
			node->SetNumberOfLeaves(node->GetNumberOfLeaves() + 1);
		else
			node->SetNumberOfLeaves(node->GetNumberOfLeaves() + child->GetNumberOfLeaves());

		node->SetNumberOfSeqs(node->GetNumberOfSeqs() + child->GetNumberOfSeqs());
		node->SetWeightedNumberOfSeqs(node->GetWeightedNumberOfSeqs() + child->GetWeightedNumberOfSeqs());
		node->SetRelativeProportionOfSeqs(node->GetRelativeProportionOfSeqs() + child->GetRelativeProportionOfSeqs());
	}	
}

#endif	
