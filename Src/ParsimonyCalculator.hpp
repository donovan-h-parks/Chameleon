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

#ifndef _PARSIMONY_CALCULATOR_
#define _PARSIMONY_CALCULATOR_

#include "stdafx.h"

#include "Tree.hpp"
#include "VisualNode.hpp"

typedef struct sCHARACTER_DATA
{
	sCHARACTER_DATA(): score(0), bPresent(false) {}

	uint score;
	bool bPresent;
} CharacterData;

typedef struct sPARSIMONY_DATA
{
	sPARSIMONY_DATA(): nodeScore(0), consistencyIndex(0) {}

	float GetConsistencyIndex() { return consistencyIndex; }
	uint GetNodeScore() { return nodeScore; }
	uint GetScore(const QString& character) { return characterScores[character].score; }

	QMap<QString, CharacterData> characterScores;

	uint nodeScore;
	float consistencyIndex;
	QSet<QString> parsimoniousCharacters;

	static QString field;
} ParsimonyData;

/**
 * @brief Calculates parsimony score (i.e., minimum number of changes required to explain the data)
 *				and assignment of internal labels leading to this parsimony score using the Sankoff algorithm.
 */
class ParsimonyCalculator
{
public:
	/** Constructor. */
	ParsimonyCalculator() {}

	/** Destructor. */
	~ParsimonyCalculator() {}

	/** Calculate parismony score and assignment of labels giving this score. */

	/** 
	 * @brief Calculate parismony score and assignment of labels giving this score.
	 * @param tree Tree to calculate parsimony scores for.
	 * @param samples Indicates how sequences in the tree are partitioned into samples.
	 * @param field Field to calculate parsimony for.
	 * @param bPhylogeny Flag indicating if the input tree is a phylogeny (leaves = seq ids) or a cluster tree (leaves = sample ids)
	 */
	uint Calculate(Tree<VisualNode>* tree, SamplesPtr samples, const QString& field, bool bPhylogeny);

protected:
	/** Propagate parsimony scores up tree.*/
	void CalculateUp(Tree<VisualNode>*  tree, const QString& field, const QStringList& characters);

	/** Propagate most parsimonious character states down tree. */
	void CalculateDown(Tree<VisualNode>*  tree, const QString& field, const QStringList& characters);

protected:
	/** Parsimony data for each node (indexed by node id). */
	QMap<uint, ParsimonyData> m_parsimonyData;	
};

#endif
