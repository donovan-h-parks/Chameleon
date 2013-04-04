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

#ifndef _TREE_TOOLS_
#define _TREE_TOOLS_

#include "stdafx.h"

#include "VisualNode.hpp"

/**
 * @brief Methods for obtaining information from a tree. 
 *
 * @see TreeTools for more generic methods.
 */
template<class N> class TreeTools
{
public:
  TreeTools() {}
  virtual ~TreeTools() {}

public:

	/**
	 * @brief Clone subtree starting at the specified node.
	 * @param node Root node of subtree to clone.
	 * @return Cloned tree.
	 */
	static N* CloneSubtree(N* node); 

	/**
	 * @brief Retrieve all leaves from a subtree.
	 * @param node Node that defines the subtree.
	 * @return vector of leaves in the subtree.
	 */
	static QList<N*> GetLeaves(N* node);

	/**
	 * @brief Retrieve all leaves from a subtree.
	 * @param node Node that defines the subtree.
	 * @return vector of leaves in the subtree.
	 */
	static QList<const N*> GetLeaves(const N* node);

	/**
	 * @brief Retrieve all leaves from a subtree.
	 * @param node Node that defines the subtree.
	 * @param leaves A vector of leaves in the subtree.
	 */
	static void GetLeaves(N* node, QList<N*>& leaves);

	/**
	 * @brief Retrieve all leaves from a subtree.
	 * @param node Node that defines the subtree.
	 * @param leaves A vector of leaves in the subtree.
	 */
	static void GetLeaves(const N* node, QList<const N*>& leafList);

	/**
	 * @brief Retrieve all leaf ids from a subtree.
	 * @param node Node that defines the subtree.
	 * @return A vector of ids.
	 */
	static QList<unsigned int> GetLeafIds(N* node);

	/**
	 * @brief Get the id of a leaf given its name in a subtree.
	 *
	 * @param node The node defining the subtree to search.
	 * @param name The name of the node.
	 * @param id The id of the node.
	 */
	static void SearchLeaf(N* node,  const QString& name, unsigned int * & id);

	/**
	 * @brief Retrieve all son nodes from a subtree.
	 * @param node Node that defines the subtree.
	 * @return Vector of nodes in the subtree.
	 */
	static QList<N*> GetNodes(N* node);

	/**
	 * @brief Retrieve all son nodes from a subtree.
	 * @param node Node that defines the subtree.
	 * @return Vector of nodes in the subtree.
	 */
	static QList<const N*> GetNodes(const N* node);

	/**
	 * @brief Retrieve all nodes ids from a subtree.
	 * @param node Bode that defines the subtree.
	 * @return Vector of ids.
	 */
	static QList<int> GetNodesId(N* node);

	/**
	 * @brief Determine if subtree contains a node with a given id.
	 * @param node Node defining the subtree to be searched.
	 * @param name Name to search for.
	 * @return True if the subtree contains a node with the specified id.
	 */
	static bool HasNodeWithId(N* node, unsigned int id);

	/**
	 * @brief Find all nodes in a subtree with a given id.
	 * @param node Node defining the subtree to be searched.
	 * @param id  Id to search for.
	 * @return Vector of nodes with the specified id.
	 */
	static QList<N*> SearchNodeWithId(N* node, unsigned int id);

	/**
	 * @brief Find all nodes in a subtree with a given name.
	 * @param node  Node defining the subtree to be searched.
	 * @param name  The name to search for.
	 * @param nodes Vector of nodes with the specified name.
	 */
	static QList<N*> SearchNodeWithName(N* node, const QString& name);

	/**
	 * @brief Determine if subtree contains a node with a given name.
	 * @param node Node defining the subtree to be searched.
	 * @param name Name to search for.
	 * @return True if the subtree contains a node with the specified name.
	 */
	static bool HasNodeWithName(N* node, const QString& name);

	/**
	 * @brief Tell if a particular node is the root of a tree
	 * @param node Node to check.
	 * @return True if node is the root.
	 */
	static bool IsRoot(N* node) { return node->IsRoot(); }

	/**
	 * @brief Get the number of nodes of a subtree defined by a particular node.
	 * @param node Node defining the subtree to check.
	 * @return Number of leaves.
	 */
	static unsigned int GetNumberOfNodes(N* node);

	/**
	 * @brief Get the leaf names of a subtree defined by a particular node.
	 * @param node Node defining the subtree to check.
	 * @return List of all leaves names.
	 */
	static QStringList GetLeafNames(N* node);

	/**
	 * @brief Get the leaf names of a subtree defined by a particular node.
	 * @param node Node defining the subtree to check.
	 * @param names List containing names of all children nodes.
	 */
	static void GetLeafNames(N* node, QStringList& names);

	/**
	 * @brief Get the depth of the subtree (i.e. the maximum number of children 'generations').
	 *
	 * ex:
	 * <code>
	 *    +----------A
	 *    |
	 * ---+ N1     +-------B
	 *    |        |
	 *    +--------+ N2
	 *             |
	 *             +------C
	 * </code>
	 * Depth of node 'N1' is 2, depth of node 'N2' is 1, depth of leaves is 0.
	 *
	 * @param node Node defining the subtree to check.
	 * @return Depth of the subtree.
	 */
	static unsigned int GetDepth(N* node);

	/**
	 * @brief Get the height of the subtree (i.e. length of longest downward path to a leaf node').
	 * @param node Node defining the subtree to check.
	 * @return Height of the node.
	 */
	static unsigned int GetHeight(N* node);

	/** Get distance to furthest leaf node. */
	static double GetDistToFurthestLeafNode(N* node);

	/** Get distance to root node. */
	static double GetDistToRoot(N* node);

	/** Get distance to closest leaf node. */
	static double GetDistToClosestLeafNode(N* node);

	/** Get average distance to leaf nodes. */
	static double GetAvgDistToLeafNodes(const N* node);

	/** Get distance to ancestral node. */
	static double GetDistToAncestor(const N* offsping, const N* ancestor);

	/**
	 * @brief Tell is a subtree is multifurcating.
	 * @param node Root node of the subtree.
	 * @return True is the subtree contains at least one multifurcating node.
	 */
	static bool IsMultifurcating(N* node);

	/**
	 * @brief Get the path between two nodes.
	 * @param node1 First node.
	 * @param node2 Second node.
	 * @param includeAncestor Flag indicating if common ancestor should be included.
	 * @return A vector with all branch lengths.
	 */
	static QList<N*> GetPathBetweenAnyTwoNodes(N* node1, N* node2, bool includeAncestor = true);

	/**
	 * @brief Get all the branch lengths of a subtree.
	 * @param node Root node of the subtree.
	 * @return A vector with all branch lengths.
	 */
	static QList<double> GetBranchLengths(N* node);

	/**
	 * @brief Get the total length (sum of all branch lengths) of a subtree.
	 * @param node Root node of the subtree.
	 * @return Total length of the subtree.
	 */
	static double GetTotalLength(N* node);

	/**
	 * @brief Set all the branch lengths of a subtree.
	 * @param node Root node of the subtree.
	 * @param brLen Branch length to apply.
	 */
	static void SetBranchLengths(N* node, double brLen);

	/**
	 * @brief Set size of all nodes in the subtree
	 * @param node Root node of the subtree.
	 * @param size Node size to apply.
	 */
	static void SetSize(N* node, int size);

	/**
	 * @brief Set size of all leaf nodes in the subtree
	 * @param node Root node of the subtree.
	 * @param size Node size to apply.
	 */
	static void SetLeafSize(N* node, int size);

	/**
	 * @brief Set size of all internal nodes in the subtree
	 * @param node Root node of the subtree.
	 * @param size Node size to apply.
	 */
	static void SetInternalSize(N* node, int size);
	        
	/**
	 * @brief Multiply all branch lengths by a given factor.
	 * @param node Root node of the subtree to scale.
	 * @param factor Factor to multiply all branch lengths with.
	 */
	static void ScaleTree(N* node, double factor);

	/**
	 * @brief Get the total distance between two nodes.
	 * @param node1 First node.
	 * @param node2 Second node.
	 * @return Sum of all branch distances between the two nodes.
	 */
	static double GetDistanceBetweenAnyTwoNodes(N* node1, N* node2);

	/** Node nodes in post-order traversal order. */
	static QList<N*> PostOrder(N* node); 

private:
	/**
	 * @brief Retrieve all leaf ids from a subtree.
	 * @param node Node that defines the subtree.
	 * @param ids Vector of ids.
	 */
	static void GetLeafIds(N* node, QList<unsigned int> & ids);

	/**
	 * @brief Retrieve all son nodes from a subtree.
	 * @param node Node that defines the subtree.
	 * @param nodes Vector of pointers toward each son node in the subtree.
	 */
	static void GetNodes(N* node, QList<N*>& nodes);

	/**
	 * @brief Retrieve all son nodes from a subtree.
	 * @param node Node that defines the subtree.
	 * @param nodes Vector of pointers toward each son node in the subtree.
	 */
	static void GetNodes(const N* node, QList<const N*>& nodes);

	/**
	 * @brief Retrieve all node ids from a subtree.
	 * @param node The node that defines the subtree.
	 * @param ids Vector of ids.
	 */
	static void GetNodesId(N* node, QList<unsigned int> & ids);

	/**
	 * @brief Find all nodes in a subtree with a given id.
	 * @param node Node defining the subtree to be searched.
	 * @param id  Id to search for.
	 * @param nodes Vector of nodes with the specified id.
	 */
	static void SearchNodeWithId(N* node, unsigned int id, QList<N*> & nodes);

	/**
	 * @brief Find all nodes in a subtree with a given name.
	 * @param node  Node defining the subtree to be searched.
	 * @param name  The name to search for.
	 * @param nodes Vector of nodes with the specified name.
	 */
	static void SearchNodeWithName(N* node, const QString& name, QList<N*>& nodes);

	/** Node nodes in post-order traversal order. */
	static void PostOrder(N* node, QList<N*>& nodes);
};


// --- Function implementations -----------------------------------------------

template<class N>
N* TreeTools<N>::CloneSubtree(N* node) 
{
  N* clone = new N(*node);

	clone->RemoveChildren();
  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
		clone->AddChild(TreeTools<N>::CloneSubtree(node->GetChild(i)));
  }

  return clone;
}

template <class N>
bool TreeTools<N>::IsMultifurcating(N* node)
{
  if(node->GetNumberOfChildren() > 2) 
	{
		return true;
	}
	else 
	{
    bool b = false;
    for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
    {
      b = b || IsMultifurcating(node->GetChild(i));
    }
    return b;
  }    
}

template <class N>
unsigned int TreeTools<N>::GetNumberOfNodes(N* node)
{
  unsigned int nbNodes = 1;
  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
    nbNodes += GetNumberOfNodes(node->GetChild(i));
  }
  return nbNodes;
}

template <class N>
QStringList TreeTools<N>::GetLeafNames(N* node)
{
	QStringList names;

  if(node->IsLeaf())
  {
    names.push_back(node->GetName());
  }
  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
		QStringList subNames = GetLeafNames(node->GetChild(i));
		foreach(QString subName, subNames)
		{
			names.push_back(subName);
		}
  }

  return names;   
}

template <class N>
void TreeTools<N>::GetLeafNames(N* node, QStringList& names)
{
  if(node->IsLeaf())
  {
    names.push_back(node->GetName());
  }

  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
		GetLeafNames(node->GetChild(i), names);
  } 
}

template <class N>
unsigned int TreeTools<N>::GetDepth(N* node)
{
  unsigned int d = 0;
  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
    unsigned int c = GetDepth(node->GetChild(i)) + 1;
    if( c > d) d = c;
  }
  return d;
}

template <class N>
unsigned int TreeTools<N>::GetHeight(N* node)
{
  unsigned int h = 0;
  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
    unsigned int c = height((N*)node->GetChild(i)) + 1;
    if( c > h) 
			h = c;
  }

  return h;
}

template <class N>
double TreeTools<N>::GetDistToFurthestLeafNode(N* node)
{
  double d = 0;
  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
    N* child = node->GetChild(i);
    double dist = 0;
		if(child->GetDistanceToParent() != VisualNode::NO_DISTANCE) 
			dist = child->GetDistanceToParent();
    else 
		{
			// node without branch length
			assert(false);
		}

    double c = GetDistToFurthestLeafNode(child) + dist;
    if(c > d) 
			d = c;
  }

  return d;	
}

template <class N>
double TreeTools<N>::GetDistToRoot(N* node)
{
	double dist = 0.0f;
	N* parent = node;
	while(!parent->IsRoot())
	{
		dist += parent->GetDistanceToParent();
		parent = parent->GetParent();
	}

  return dist;	
}

template <class N>
double TreeTools<N>::GetDistToClosestLeafNode(N* node)
{
	QList<N*> leaves = TreeTools<N>::GetLeaves(node);

	double dist = INT_MAX;
	foreach(N* leaf, leaves)
	{
		double d = TreeTools<N>::GetDistToAncestor(leaf, node);
		if(d < dist)
			dist = d;
	}

  return dist;	
}

template <class N>
QList<const N*> TreeTools<N>::GetLeaves(const N* node)
{
	QList<const N*> leafList;
	GetLeaves(node, leafList);
	return leafList;
}

template <class N>
void TreeTools<N>::GetLeaves(const N* node, QList<const N*>& leafList)
{
	if(node->IsLeaf())
		leafList.push_back(node);
	else
	{
		for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
			GetLeaves(node->GetChild(i), leafList);
	}
}

template <class N>
double TreeTools<N>::GetAvgDistToLeafNodes(const N* node)
{
	QList<const N*> leaves = TreeTools<N>::GetLeaves(node);

	double dist = 0;
	foreach(const N* leaf, leaves)
	{
		double d = TreeTools<N>::GetDistToAncestor(leaf, node);
		dist += d;
	}

  return dist / leaves.size();	
}

template <class N>
double TreeTools<N>::GetDistToAncestor(const N* offspring, const N* ancestor)
{
	double dist = 0.0f;
	const N* curNode = offspring;
	while(curNode != ancestor)
	{
		dist += curNode->GetDistanceToParent();
		curNode = curNode->GetParent();
	}

  return dist;	
}

template <class N>
QList<double> TreeTools<N>::GetBranchLengths(N* node)
{
  QList<double> brLen;

  if(node->GetDistanceToParent() != VisualNode::NO_DISTANCE) 
	{
		brLen.push_back(node->GetDistanceToParent());
	}
  else 
	{
		// no branch length
		assert(false);
	}

  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
    QList<double> sonBrLen = GetBranchLengths(node->GetChild(i));
    for(unsigned int j = 0; j < sonBrLen.size(); j++) 
			brLen.push_back(sonBrLen[j]);
  }

  return brLen;
}

template <class N>
double TreeTools<N>::GetTotalLength(N* node)
{
	if(node->GetDistanceToParent() != VisualNode::NO_DISTANCE)
	{
		double length = node->GetDistanceToParent();
		for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
		{
			length += GetTotalLength(node->GetChild(i));
		}
		return length;
	}

	return VisualNode::NO_DISTANCE;
}

template <class N>
void TreeTools<N>::SetBranchLengths(N* node, double brLen)
{
	node->SetDistanceToParent(brLen);
  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
    SetBranchLengths(node->GetChild(i), brLen);
  }
}

template <class N>
void TreeTools<N>::SetSize(N* node, int size)
{
	node->SetSize(size);

  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
    SetSize(node->GetChild(i), size);
  }
}

template <class N>
void TreeTools<N>::SetLeafSize(N* node, int size)
{
	if(node->IsLeaf())
		node->SetSize(size);

  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
    SetLeafSize(node->GetChild(i), size);
  }
}

template <class N>
void TreeTools<N>::SetInternalSize(N* node, int size)
{
	if(!node->IsLeaf())
		node->SetSize(size);

  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
    SetInternalSize(node->GetChild(i), size);
  }
}

template <class N>
void TreeTools<N>::ScaleTree(N* node, double factor)
{
  if(!node->IsRoot())
  {
		if(node->GetDistanceToParent() != VisualNode::NO_DISTANCE)
			node->SetDistanceToParent(node->GetDistanceToParent() * factor);
  }

  for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
  {
    ScaleTree(node->GetChild(i), factor);
  }
}

template <class N>
QList<N*> TreeTools<N>::GetPathBetweenAnyTwoNodes(N* node1, N* node2, bool includeAncestor)
{
  QList<N*> path;
  QList<N*> pathMatrix1;
  QList<N*> pathMatrix2;

  N* nodeUp = node1;
  while(!nodeUp->IsRoot())  
	{ 
    pathMatrix1.push_back(nodeUp);
		nodeUp = nodeUp->GetParent();
  }
  pathMatrix1.push_back(nodeUp); // The root.

  nodeUp = node2;
  while(!nodeUp->IsRoot())  
	{
    pathMatrix2.push_back(nodeUp);
    nodeUp = nodeUp->GetParent();
  }
  pathMatrix2.push_back(nodeUp); // The root.
  // Must check that the two nodes have the same root!!!

  int tmp1 = pathMatrix1.size() - 1;
  int tmp2 = pathMatrix2.size() - 1;

  while((tmp1 >= 0) && (tmp2 >= 0)) 
	{
    if (pathMatrix1[tmp1] != pathMatrix2[tmp2]) break;
    tmp1--; tmp2--;
  }

  for (int y = 0; y <= tmp1; ++y) 
		path.push_back(pathMatrix1[y]);

  if(includeAncestor) 
		path.push_back(pathMatrix1[tmp1 + 1]); // pushing once, the Node that was common to both.

  for (int j = tmp2; j >= 0; --j) 
	{
    path.push_back(pathMatrix2[j]);
  }
  return path;
}

template <class N>
double TreeTools<N>::GetDistanceBetweenAnyTwoNodes(N* node1, N* node2)
{
  QList<N*> path = GetPathBetweenAnyTwoNodes(node1, node2, false);
  double d = 0;
	foreach(N* n, path)
  {
		d += n->GetDistanceToParent();
  }
  return d;
}

template <class N>
QList<N*> TreeTools<N>::GetLeaves(N* node)
{
	QList<N*> leaves;
	GetLeaves(node, leaves);
	return leaves;
}

template <class N>
void TreeTools<N>::GetLeaves(N* node, QList<N*>& leaves)
{
	if(node->IsLeaf())
	{
		leaves.push_back(node);
	}
	else
	{
		for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
		{
			GetLeaves(node->GetChild(i), leaves);
		}
	}
}

template <class N>
QList<unsigned int> TreeTools<N>::GetLeafIds(N* node)
{
	QList<unsigned int> ids;
	GetLeafIds(node, ids);
	return ids;
}

template <class N>
void TreeTools<N>::GetLeafIds(N* node, QList<unsigned int> & ids)
{
	if(node->IsLeaf()) {
		ids.push_back(node->GetId());
	}
	for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++) {
		GetLeafIds(node->GetChild(i), ids);
	}
}

template <class N>
void TreeTools<N>::SearchLeaf(N* node,  const QString& name, unsigned int * & id)
{
	if(node->IsLeaf())
	{
		if(node->GetName() == name)
		{
			id = new unsigned int(node->GetId());
			return;
		}
	}

	for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
	{
		SearchLeaf(node->GetChild(i), name, id);
	}
}

template <class N>
QList<N*> TreeTools<N>::GetNodes(N* node)
{
	QList<N*> nodes;
	GetNodes(node, nodes);
	return nodes;
}

template <class N>
QList<const N*> TreeTools<N>::GetNodes(const N* node)
{
	QList<const N*> nodes;
	GetNodes(node, nodes);
	return nodes;
}

template <class N>
void TreeTools<N>::GetNodes(N* node, QList<N*>& nodes)
{
	for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
	{
		GetNodes(node->GetChild(i), nodes);
	}

	nodes.push_back(node);
}

template <class N>
void TreeTools<N>::GetNodes(const N* node, QList<const N*>& nodes)
{
	for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
	{
		GetNodes(node->GetChild(i), nodes);
	}

	nodes.push_back(node);
}

template <class N>
QList<int> TreeTools<N>::GetNodesId(N* node)
{
	QList<int> ids;
	GetNodesId(node, ids);
	return ids;
}

template <class N>
void TreeTools<N>::GetNodesId(N* node, QList<unsigned int> & ids)
{
	for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
	{
		GetNodesId(node->GetChild(i), ids);
	}
	ids.push_back(node->GetId());
}

template <class N>
bool TreeTools<N>::HasNodeWithId(N* node, unsigned int id)
{
	if(node->GetId() == id) return true;
	else
	{
		for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
		{
			if(HasNodeWithId(node->GetChild(i), id)) return true;
		}
		return false;
	}
}

template <class N>
QList<N*> TreeTools<N>::SearchNodeWithId(N* node, unsigned int id)
{
	QList<N*> nodes;
	SearchNodeWithId(node, id, nodes);
	return nodes;    
}

template <class N>
void TreeTools<N>::SearchNodeWithId(N* node, unsigned int id, QList<N*> & nodes)
{
	for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
	{
		SearchNodeWithId(node->GetChild(i), id, nodes);
	}

	if(node->GetId() == id) 
		nodes.push_back(node);
}

template <class N>
QList<N*> TreeTools<N>::SearchNodeWithName(N* node, const QString& name)
{
	QList<N*> nodes;
	SearchNodeWithName(node, name, nodes);
	return nodes;    
}

template <class N>
void TreeTools<N>::SearchNodeWithName(N* node, const QString& name, QList<N*>& nodes)
{
	for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
	{
		SearchNodeWithName(node->GetChild(i), name, nodes);
	}

	if(node->GetName() == name) 
		nodes.push_back(node);
}

template <class N>
bool TreeTools<N>::HasNodeWithName(N* node, const QString& name)
{
	if(node->GetName() == name) 
	{
		return true;
	}
	else
	{
		for(unsigned int i = 0; i < node->GetNumberOfChildren(); i++)
		{
			if(HasNodeWithName(node->GetChild(i), name)) 
				return true;
		}
		return false;
	}
}

template <class N>
QList<N*> TreeTools<N>::PostOrder(N* node)
{
	QList<N*> nodes;
	PostOrder(node, nodes);

	return nodes;
}

template <class N>
void TreeTools<N>::PostOrder(N* node, QList<N*>& nodes)
{
	foreach(N* child, node->GetChildren())
		PostOrder(child, nodes);

	nodes.append(node);
}

#endif 

