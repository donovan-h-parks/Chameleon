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
//
// Based on the 'simpleNJ' code from the RapidNJ project: 
//  http://birc.au.dk/Software/RapidNJ/
//=======================================================================

#ifndef _NEIGHBOUR_JOINING_
#define _NEIGHBOUR_JOINING_

#include "stdafx.h"

#include "Tree.hpp"
#include "VisualNode.hpp"

class NeighbourJoining
{
 public:
	/** Constructor. */
	NeighbourJoining() {}

	/** Destructor. */
	~NeighbourJoining();

	/** 
	 * @brief Build neighbour joining (NJ) tree from a distance matrix.
	 * @param distMatrix Matrix indicating pairwise distance between objects.
	 * @param labels Labels identifying each row/col of the distance matrix.
	 * @param tree Resulting NJ tree.
	 */
	void BuildTree(Matrix& distMatrix, const QStringList& labels, Tree<VisualNode>& tree);
  
private:
	double* m_separationSums;
	double* m_separations;	
	int m_rowIndex, m_colIndex;

	int m_numActiveClusters;
	bool* m_activeClusters;

	uint m_nodeId;

	void FindNearestClusters(Matrix& distMatrix);
	void UpdateClusters(Matrix& distMatrix, QList<VisualNode*>& clusters);
	void UpdateDistanceMatrix(Matrix& distMatrix);
};

#endif
