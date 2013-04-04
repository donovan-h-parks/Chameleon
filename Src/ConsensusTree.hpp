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

#ifndef _CONSENSUS_TREE_HPP_
#define _CONSENSUS_TREE_HPP_

#include "stdafx.h"

#include "Split.hpp"

#include "Tree.hpp"
#include "VisualNode.hpp"

class ConsensusTree
{
public:
	/** Constructor. */
	ConsensusTree() {}

	/** Destructor. */
	~ConsensusTree() {}

	/** Add tree. */
	void AddTree(const Tree<VisualNode>& tree);

	/** 
	 * @brief Build a majority rule consensus tree.
	 * @param tree Majority rule consensus tree.
	 */
	void MajorityRuleTree(Tree<VisualNode>& tree);

private:
	QString CreateUniqueId(const VisualNode* node);

private:
	/** Forest. */
	QList< Tree<VisualNode> > m_trees;
};

#endif