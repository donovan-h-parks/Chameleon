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

#ifndef _UNISPLIT_
#define _UNISPLIT_

#include "stdafx.h"

#include "Tree.hpp"
#include "VisualNode.hpp"
#include "Cluster.hpp"

/**
 * @class UniSplit
 * @brief Implements the UniSplit phylogenetic distance measure.
 */
class UniSplit 
{
public:
	enum MEASURE_TYPE { UNWEIGHTED = 0, WEIGHTED, WEIGHTED_NORMALIZED };
	enum SPLITS_TO_CONSIDER { NO_SPLITS, COMMON_SPLIT_SET, COMPLETE_LINEAGE, ALL_SPLITS, NORMALIZED_WEIGHTED_UNIFRAC };

public:
	/** Constructor. */
	UniSplit(SplitSystemPtr splitSystem);

	/** Destructor. */
	~UniSplit();

	/** Set type of analysis to perform. */
	void SetMeasureType(MEASURE_TYPE type) { m_measureType = type; }

	/** Get type of analysis performed. */
	MEASURE_TYPE GetMeasureType() { return m_measureType; }

	/** Set splits to consider during analysis. */
	void SetSplitsToConsider(SPLITS_TO_CONSIDER splits) { m_splitsToConsidered = splits; }

	/** Get splits considered during analysis. */
	SPLITS_TO_CONSIDER GetSplitsToConsider() { return m_splitsToConsidered; }

	/** Determine if a weighted analysis is being performed. */
	bool IsWeighted() { return m_measureType == WEIGHTED || m_measureType == WEIGHTED_NORMALIZED; }
	
	/** Determine if measure is normalized. */
	bool IsNormalized() { return m_measureType == WEIGHTED_NORMALIZED; }

	QString GetMethodMessage() const;

	/**
	 * @brief Calculate distance between all pairs of samples. 
	 */
	Matrix Run();

	/**
	 * @brief Calculate lower and upper bounds on an unrooted split system.
	 * @param lowerBound Matrix indicating the minimal distance between samples.
	 * @param upperBound Matrix indicating the maximum distance between sampels.
	 */
	void CalculateBoundsOnUnrootedSystem(Matrix& lowerBound, Matrix& upperBound);


	 /** 
	  * @breik Perform jackknife analysis. 
		* @param clusterType Type of clustering to perform.
		* @param iterations Number of jackknife iterations to perform.
	 */
	 void Jackknife(Cluster::CLUSTER_TYPE clusterType, uint iterations, uint seqToKeep);
	 
	/**
	 * @brief Perform Monte Carlo significance test between the specified samples.
	 * @param iterations Number of iterations to perform when creating probability density function.
	 * @param signMatrix Matrix indicating p-value for all pairs of samples.
	 */
	void SignificanceTest(uint iterations, Matrix& signMatrix);

	/**
	 * @brief Perform hierarchical clustering on dissimilarity matrix.
	 * @param clusterType Type of clustering to perform.
	 */
	void Cluster(Cluster::CLUSTER_TYPE clusterType);

	/** Get dissimilarity matrix. */
	Matrix GetDissimilarityMatrix() const { return m_dissimilarityMatrix; }

	/** Get tree for compatible split system. */
	Tree<VisualNode>* GetClusterTree() { return &m_clusterTree; }

protected:
	/** Calculate unweighted UniSplit distance between all pairs of samples. */
	Matrix CalculateUniSplit();

	/** Calculate weighted UniSplit distance between all pairs of samples. */
	Matrix CalculateWeightedUniSplit();

	/** 
	 * @brief Calculate number of sequences in each sample from both bipartitions. 
	 * @param split Split indicating bipartition of sequences.
	 * @param leftSeqCounts Vector indicating number of sequences in each sample for left bipartition.
	 * @param rightSeqCounts Vector indicating number of sequences in each sample for right bipartition.
	 * @param bOutgroupSeqOnLeft Flag indicating if there are outgroup sequences in left bipartition.
	 * @param bOutgroupSeqOnRight Flag indicating if there are outgroup sequences in right bipartition.
	 * @return False if outgroup sequences are on both sides of the split or one side of the split is completely
	 *					comprised of outgroup sequences. True for all other splits.
	 */
	bool CalculateSeqsInSample(const Split& split, QVector<uint>& leftSeqCounts, QVector<uint>& rightSeqCounts,
															bool& bOutgroupSeqOnLeft, bool& bOutgroupSeqOnRight);

	/**
	 * @brief Calculate lower and upper bounds on an compatible unrooted split system.
	 * @param lowerBound Matrix indicating the minimal distance between samples.
	 * @param upperBound Matrix indicating the maximum distance between sampels.
	 */
	void CalculateUnrootedBoundsOnTree(Matrix& lowerBound, Matrix& upperBound);

	/**
	 * @brief Calculate lower and upper bounds on a incompatible unrooted split system.
	 * @param lowerBound Matrix indicating the minimal distance between samples.
	 * @param upperBound Matrix indicating the maximum distance between sampels.
	 */
	void CalculateUnrootedBoundsOnSplitSystem(Matrix& lowerBound, Matrix& upperBound);

	/** Adjust bounds of lower and upper distance matrices. */
	void AdjustBounds(Matrix& dist, Matrix& lowerBound, Matrix& upperBound);

	/**
	 * @brief Perform Monte Carlo significance test between all pairs of samples.
	 * @param sampleId1 First sample to calculate significance between.
	 * @param sampleId2 Second sample to calculate significance between.
	 * @param iterations Number of iterations to perform when creating probability density function..
	 * @param pdf List of distance comprisong null distribution.
	 */
	 void SignificanceTest(uint sampleId1, uint sampleId2, uint iterations, QList<double>& pdf);

protected:
	/** All splits within a splits network. */
	SplitSystemPtr m_splitSystem;

	/** Type of analysis to perform. */
	MEASURE_TYPE m_measureType;

	/** Splits to consider during analysis. */
	SPLITS_TO_CONSIDER m_splitsToConsidered;

	/** Resulting dissimilarity matrix. */
	Matrix m_dissimilarityMatrix;

	/** Resulting cluster tree. */
	Tree<VisualNode> m_clusterTree;
};

#endif

