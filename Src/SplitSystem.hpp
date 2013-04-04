//=======================================================================
// Author: Donovan Parks
//
// Copyright 2009 Donovan Parks
//
// This file is part of Chameleon.

// Chameleon is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Chameleon is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with Chameleon. If not, see <http://www.gnu.org/licenses/>.
//=======================================================================

#ifndef _SPLIT_SYSTEM_
#define _SPLIT_SYSTEM_

#include "stdafx.h"

#include "Split.hpp"
#include "Tree.hpp"
#include "VisualNode.hpp"
#include "System.hpp"

/**
 * @class SplitSystem
 * @brief Holds data and functions for a collection of splits.
 */
class SplitSystem: public System
{
public:
	/** Constructor. */
	SplitSystem();

	/** Destructor. */
	~SplitSystem() {}

	/** 
	 * @brief Populate split system.
	 * @param phylogenyFile Filename of file containing phylogenetic data.
	 * @param samplesFile Filename of file containing sample data.
	 * @param metadataFile Filename of file containing metadata.
	 * @param bImplicitlyRooted Flag indicating if a tree should be considered rooted or unrooted.
	 * @return True if data loaded successfully, otherwise false.
	 */
	bool LoadData(const QString& phylogenyFile, const QString& samplesFile, const QString& metadataFile, bool bImplicitlyRooted = true);

	/** Clone split system. */
	SplitSystemPtr Clone() const { return SplitSystemPtr(new SplitSystem(*this)); }

	/** Get number of splits. */
	uint GetNumSplits() const { return m_splits.size(); }

	/** Get splits. */
	const QList<Split>& GetSplits() const { return m_splits; }

	/** 
	 * @brief Get a desired split.
	 * @param index Index of desired split.
	 * @return Split at given index.
	 */
	const Split& GetSplit(uint index) const { return m_splits.at(index); }

	/** Add split. */
	void AddSplit(const Split& split) { m_splits.push_back(split); }

	/** Add splits. */
	void AddSplits(const QList<Split>& splits) { m_splits.append(splits); }

	/** Set splits. */
	void SetSplits(const QList<Split>& splits) { m_splits = splits; }

	/** Outgroup sequences in each bipartion of a split. */
	void CheckForOutgroupSeqs(const Split& split, bool& bOutgroupSeqOnLeft, bool& bOutgroupSeqOnRight) const;

	/** Check that outgroup is monophyletic. */
	bool IsOutgroupMonophyletic() const;

	/** Jackknife split system so each sample contains the specified number of sequences. */
	void Jackknife(uint seqToKeep, bool bWeighted);

	/** Print split system to log. */
	void Print() const;

	/** Set total evolution represented in split system. */
	void SetTotalEvolution(double evolution) { m_totalEvolution = evolution; }

	/** Get total evolution represented in split system. */
	double GetTotalEvolution() { return m_totalEvolution; }
	
	/** Check if split system is compatible. */
	bool IsCompatible();

	/** Create tree from split system. Note: this function assumes the split system is compatible (see IsCompatible()). */
	void CreateTree(Tree<VisualNode>& tree);

	/** Get tree for compatible split system. */
	Tree<VisualNode>* GetTree() { return &m_tree; }

	/**
   * @brief Parse splits from a tree structure.
   *
   * @param root Root node of (sub)tree to build split system from.
	 * @return True if split system created successfully, otherwise false.
   */
	bool CreateFromTree(VisualNode* root);

private:
	/** Tree representation for complete compatible split systems. */
	Tree<VisualNode> m_tree;

	/** Current root of split system. */
	VisualNode* m_currentRoot;

	/** Set of currently active splits. */
	QList<Split> m_splits;

	/** Total evolution represented in split system. */
	double m_totalEvolution;
};

#endif

