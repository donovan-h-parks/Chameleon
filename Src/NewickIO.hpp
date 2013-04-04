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

#ifndef _NEWICK_IO_
#define _NEWICK_IO_

#include "stdafx.h"

#include "Tree.hpp"
#include "VisualNode.hpp"

class SplitSystem;

/**
 * @brief Populate a split system from a Newick formatted tree.
 */
class NewickIO
{
public:		
	/** Constructor. */
	NewickIO() {}

	/**
	* @param Build tree structure from a file containing a Newick formatted tree.
	*
	* @param tree Tree to populate from file.
	* @param filename Path to file containing Newick formatted tree.
	* @return True if tree built successfully, else false if reading file failed.
	*/
	bool Read(Tree<VisualNode>& tree, const QString& filename);
	
	/**
	* @brief Parse a string in Newick format and convert it into a tree and split system.
	*
	* @param tree Tree to populate.
	* @param newickStr String containing tree in Newick format.
	* @param bImplicitlyRooted Flag indicating if the tree should be treated as implicitly rooted.
	* @param splitSystem Split system to populate.
	* @return True if structures populated successfully, else false if reading file failed.
	*/
	bool ParseNewickString(Tree<VisualNode>& tree, SplitSystem *const splitSystem, const QString& newickStr, bool bImplicitlyRooted);

	/**
	* @breif Populate split system from Newick formatted tree.
	*
	* @param splitSystem Split system to populate from file.
	* @param filename Path to file containing Newick formatted tree.
	* @param bImplicitlyRooted Flag indicating if the tree should be treated as implicitly rooted.
	* @return True if split system populated successfully, else false if reading file failed.
	*/
	bool Read(SplitSystem *const splitSystem, const QString& filename, bool bImplicitlyRooted);

		/**
   * @brief Write phylogenetic tree to file.
   *
	 * @param tree Tree to write out to file.
   * @param filename The file path.
   */
	void Write(Tree<VisualNode>& tree, const QString& filename) const;

		/**
   * @brief Write phylogenetic tree to string.
   *
	 * @param tree Tree to write out to file.
   * @param newickStr String to set to Newick formatted tree representation of the input tree.
   */
	void CreateNewickStr(Tree<VisualNode>& tree, QString& newickStr) const;

protected:
 /**
	* @brief Parse a string in Newick format and convert it into a tree and split system.
	*
	* @param tree Tree to populate from file.
	* @param splitSystem Split system to populate from file.
	* @param filename Path to file containing Newick formatted tree.
	* @param bImplicitlyRooted Flag indicating if the tree should be treated as implicitly rooted.
	* @return True if structures populated successfully, else false if reading file failed.
	*/
	bool ParseNewickFile(Tree<VisualNode>& tree, SplitSystem *const splitSystem, const QString& filename, bool bImplicitlyRooted);

 /**
	* @brief Parse Newick string information about a node.
	*
	* @param node Node to associate information with.
	* @param nodeInfo Node data obtained from Newick string.
	* @return bLeafNode Flag indicating if node represents a leaf node (true) or internal node (false).
	*/
	void ParseNodeInfo(VisualNode* node, QString& nodeInfo, bool bLeafNode);

	/**
   * @brief Write phylogenetic tree to file.
   *
	 * @param tree Tree to write out to file.
   * @param out Stream to write tree to in Newick format.
   */
	void Write(Tree<VisualNode>& tree, QTextStream& out) const;

	/**
	 * @brief Write elements of a node to file in Newick format.
	 *
	 * @param tree Tree to write out to file.
	 * @param out The output stream.
	 * @param child Child node.
	 */
	void WriteElements(Tree<VisualNode>& tree, QTextStream& out, VisualNode* child) const;

	/**
	 * @brief Write each node to file in Newick format.
	 *
	 * @param tree Tree to write out to file.
	 * @param out The output stream.
	 * @param parent Parent node.
	 */
	void WriteNodes(Tree<VisualNode>& tree, QTextStream& out, VisualNode* parent) const;
};

#endif

