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

#include "stdafx.h"

#include "UniSplit.hpp"

#include "Log.hpp"

#include "StringUtils.hpp"
#include "MathUtils.hpp"
#include "StatsUtils.hpp"
#include "SplitSystem.hpp"
#include "Cluster.hpp"
#include "NewickIO.hpp"
#include "Sample.hpp"

#include "ConsensusTree.hpp"

#ifdef USE_OMP
	#include <omp.h>
#endif

UniSplit::UniSplit(SplitSystemPtr splitSystem): m_splitSystem(splitSystem)
{

}

UniSplit::~UniSplit()
{
	
}

Matrix UniSplit::Run()
{
	if(IsWeighted())
		m_dissimilarityMatrix = CalculateWeightedUniSplit();
	else
		m_dissimilarityMatrix = CalculateUniSplit();

	return m_dissimilarityMatrix;
}

void UniSplit::CalculateBoundsOnUnrootedSystem(Matrix& lowerBound, Matrix& upperBound)
{
	bool bCompatible = m_splitSystem->IsCompatible();
	if(bCompatible)
	{
		CalculateUnrootedBoundsOnTree(lowerBound, upperBound);
	}
	else
	{
		CalculateUnrootedBoundsOnSplitSystem(lowerBound, upperBound);
	}
}

void UniSplit::CalculateUnrootedBoundsOnTree(Matrix& lowerBound, Matrix& upperBound)
{
	/*
	SplitSystemPtr origSplitSystem = m_splitSystem->Clone();

	// Create a tree from the split system. This function sets an arbitrary root for the tree.
	Tree<VisualNode> origTree;
	m_splitSystem->CreateTree(origTree);

	NewickIO newickIO;
	newickIO.Write(origTree, "TestInitialTree.tre");

	// initialize distance matrices
	uint numSamples = m_splitSystem->GetNumSamples();

	lowerBound.resize(numSamples);
	for(int i = 0; i < lowerBound.size(); ++i)
	{
		QVector<double> temp(numSamples, 1.0);
		lowerBound[i] = temp;
	}

	upperBound.resize(numSamples);
	for(int i = 0; i < upperBound.size(); ++i)
	{
		QVector<double> temp(numSamples, 0.0);
		upperBound[i] = temp;
	}

	// calculate distance for all possible rootings of the tree
	QList<VisualNode*> nodes = origTree.GetNodes();
	nodes.removeOne(origTree.GetRootNode());		// we don't want to root on the original "arbitrary" root

	ConsensusTree consensusTree;
	for(int i = 0; i < nodes.size(); ++i)
	{
		Tree<VisualNode>* tree = origTree.Clone();
		tree->Reroot(tree->GetNode(nodes.at(i)->GetId()));
		VisualNode* root = tree->GetRootNode();

		// get children of root and calculate distance with root at either extreme
		QList<VisualNode*> children = root->GetChildren();
		double branchLength = children[0]->GetDistanceToParent() * 2;
		for(uint j = 0; j < 2; ++j)
		{
			children[j]->SetDistanceToParent(0.0);
			children[(j+1) % 2]->SetDistanceToParent(branchLength);

			m_splitSystem->CreateFromTree(tree->GetRootNode());

			Matrix dist = Run();

			QStringList labels = m_splitSystem->GetActiveSampleNames();
			Tree<VisualNode> clusterTree;
			Cluster::UPGMA(dist, labels, clusterTree);
			consensusTree.AddTree(clusterTree);

			AdjustBounds(GetDissimilarityMatrix(), lowerBound, upperBound);
		}
	}

	Tree<VisualNode> majorityRuleTree;
	consensusTree.MajorityRuleTree(majorityRuleTree);

	m_splitSystem = origSplitSystem;
	*/
}

void UniSplit::CalculateUnrootedBoundsOnSplitSystem(Matrix& lowerBound, Matrix& upperBound)
{
	/*
	SplitSystemPtr origSplitSystem = m_splitSystem->Clone();

	// initialize distance matrices
	uint numSamples = m_splitSystem->GetNumSamples();

	lowerBound.resize(numSamples);
	for(int i = 0; i < lowerBound.size(); ++i)
	{
		QVector<double> temp(numSamples, 1.0);
		lowerBound[i] = temp;
	}

	upperBound.resize(numSamples);
	for(int i = 0; i < upperBound.size(); ++i)
	{
		QVector<double> temp(numSamples, 0.0);
		upperBound[i] = temp;
	}

	// insert root at each split and calculate UniSplit metric
	Matrix dist;
	const QList<Split>& splits = origSplitSystem->GetSplits();
	for(int splitId = 0; splitId < splits.size(); ++splitId)
	{
		// insert root
		Split rootSplit = splits.at(splitId);
		Split newSplit1 = Split(rootSplit.GetId(), rootSplit.GetWeight() / 2, rootSplit.GetSplitArray(), true, false);
		Split newSplit2 = Split(rootSplit.GetId(), rootSplit.GetWeight() / 2, rootSplit.GetSplitArray(), false, true);

		QList<Split> newSplits;
		newSplits.append(newSplit1);
		newSplits.append(newSplit2);

		QList<Split> tempSplits;
		#pragma omp parallel private(tempSplits)
		{
			#pragma omp for schedule(static) nowait
			for(int otherSplitId = 0; otherSplitId < splits.size(); ++otherSplitId)
			{
				QSet<uint> leftRootIds = rootSplit.GetLeftSequenceIds().toSet();
				QSet<uint> rightRootIds = rootSplit.GetRightSequenceIds().toSet();

				if(otherSplitId != splitId)
				{
					Split split = splits.at(otherSplitId);

					// check if root should be on left or right
					QSet<uint> ids;
					bool bRootLeft = false;
					bool bRootRight = false;
					if(split.GetSizeLeftBipartition() > split.GetSizeRightBipartition())
					{
						ids = split.GetRightSequenceIds().toSet();
						if(ids.size() >= leftRootIds.size())
							leftRootIds = leftRootIds.subtract(ids);

						if(leftRootIds.empty())
						{
							bRootRight = true;
						}
						else
						{
							if(ids.size() >= rightRootIds.size())
								rightRootIds = rightRootIds.subtract(ids);

							if(rightRootIds.empty())					
								bRootRight = true;
							else 
								bRootLeft = true;			
						}
					}
					else
					{
						ids = split.GetLeftSequenceIds().toSet();
						if(ids.size() >= leftRootIds.size())
							leftRootIds = leftRootIds.subtract(ids);

						if(leftRootIds.empty())
						{
							bRootLeft = true;
						}
						else
						{
							if(ids.size() >= rightRootIds.size())
								rightRootIds = rightRootIds.subtract(ids);

							if(rightRootIds.empty())					
								bRootLeft = true;
							else 
								bRootRight = true;			
						}
					}

					tempSplits.append(Split(split.GetId(), split.GetWeight(), split.GetSplitArray(), bRootLeft, bRootRight));
				}
			}

			// tabulate results from all threads.
			#pragma omp critical
			{
				newSplits.append(tempSplits);
			}
		}

		m_splitSystem->SetSplits(newSplits);

		if(bWeighted)
			dist = CalculateWeightedUniSplit(bNormalized);
		else
			dist = CalculateUniSplit();

		AdjustBounds(dist, lowerBound, upperBound);
	}

	m_splitSystem = origSplitSystem;
	*/
}

void UniSplit::AdjustBounds(Matrix& dist, Matrix& lowerBound, Matrix& upperBound)
{
	for(int i = 0; i < dist.size(); ++i)
	{
		lowerBound[i][i] = 0;
		upperBound[i][i] = 0;

		for(int j = i+1; j < dist.at(0).size(); ++j)
		{
			if(dist[i][j] < lowerBound[i][j])
			{
				lowerBound[i][j] = dist[i][j];
				lowerBound[j][i] = dist[i][j];
			}

			if(dist[i][j] > upperBound[i][j])
			{
				upperBound[i][j] = dist[i][j];
				upperBound[j][i] = dist[i][j];
			}
		}
	}
}

typedef struct UNISPLIT_DATA
{
	UNISPLIT_DATA(): uniqueI(0.0), uniqueJ(0.0), shared(0.0), root(0.0), external(0.0), outgroup(0.0) {}

	double uniqueI;
	double uniqueJ;
	double shared;
	double root;
	double external;
	double outgroup;
} UniSplitData;

Matrix UniSplit::CalculateUniSplit()
{
	QList<uint> activeSamples = m_splitSystem->GetSamples()->GetActiveSampleIds().toList();
	uint numActiveSamples = activeSamples.size();

	QVector< QVector< UniSplitData > > matrix(numActiveSamples, QVector<UniSplitData>(numActiveSamples));

	const QList<Split>& splits = m_splitSystem->GetSplits();
	QVector< QVector< UniSplitData > > tempMatrix;
	#pragma omp parallel private(tempMatrix)
	{
		tempMatrix.resize(numActiveSamples);
		for(uint i = 0; i < numActiveSamples; ++i)
			tempMatrix[i].resize(numActiveSamples);

		#pragma omp for schedule(static) nowait
		for(int splitId = 0; splitId < splits.size(); ++splitId)
		{
			QVector<uint> leftSeqCounts, rightSeqCounts;
			bool bOutgroupSeqOnLeft, bOutgroupSeqOnRight;
			if(CalculateSeqsInSample(splits.at(splitId), leftSeqCounts, rightSeqCounts, bOutgroupSeqOnLeft, bOutgroupSeqOnRight))
			{
				// Determined unique and shared evolution for all pairs of samples.
				double weight = splits.at(splitId).GetWeight();
				if(bOutgroupSeqOnLeft)
				{
					for(uint i = 0; i < numActiveSamples; ++i)
					{
						uint iIndex = activeSamples.at(i);

						for(uint j = i+1; j < numActiveSamples; ++j)
						{
							uint jIndex = activeSamples.at(j);

							// outgroup is on the left side
							uint ingroupTaxaOnLeft = splits.at(splitId).GetSizeLeftBipartition();

							if(rightSeqCounts.at(iIndex) > 0 && rightSeqCounts.at(jIndex) == 0)
								tempMatrix[i][j].uniqueI += weight;
							else if(rightSeqCounts.at(iIndex) == 0 && rightSeqCounts.at(jIndex) > 0)
								tempMatrix[i][j].uniqueJ += weight;
							else if(rightSeqCounts.at(iIndex) > 0 && rightSeqCounts.at(jIndex) > 0 && leftSeqCounts.at(iIndex) + leftSeqCounts.at(jIndex) > 0)
								tempMatrix[i][j].shared += weight;
							else if(leftSeqCounts.at(iIndex) == 0 && leftSeqCounts.at(jIndex) == 0 && ingroupTaxaOnLeft > 0)
								tempMatrix[i][j].root += weight;
							else if(rightSeqCounts.at(iIndex) == 0 && rightSeqCounts.at(jIndex) == 0)
								tempMatrix[i][j].external += weight;
							else
								tempMatrix[i][j].outgroup += weight;
						}
					}
				}
				else if(bOutgroupSeqOnRight)
				{
					for(uint i = 0; i < numActiveSamples; ++i)
					{
						uint iIndex = activeSamples.at(i);

						for(uint j = i+1; j < numActiveSamples; ++j)
						{
							uint jIndex = activeSamples.at(j);

							// outgroup is on the right side
							uint ingroupTaxaOnRight = splits.at(splitId).GetSizeRightBipartition();

							if(leftSeqCounts.at(iIndex) > 0 && leftSeqCounts.at(jIndex) == 0)
								tempMatrix[i][j].uniqueI += weight;
							else if(leftSeqCounts.at(iIndex) == 0 && leftSeqCounts.at(jIndex) > 0)
								tempMatrix[i][j].uniqueJ += weight;
							else if(leftSeqCounts.at(iIndex) > 0 && leftSeqCounts.at(jIndex) > 0 && rightSeqCounts.at(iIndex) + rightSeqCounts.at(jIndex) > 0)
								tempMatrix[i][j].shared += weight;
							else if(rightSeqCounts.at(iIndex) == 0 && rightSeqCounts.at(jIndex) == 0 && ingroupTaxaOnRight > 0)
								tempMatrix[i][j].root += weight;
							else if(leftSeqCounts.at(iIndex) == 0 && leftSeqCounts.at(jIndex) == 0)
								tempMatrix[i][j].external += weight;
							else
								tempMatrix[i][j].outgroup += weight;
						}
					}
				}
				else
				{
					Log::Inst().Error("Split does not specify an outgroup.");
				}
			}
		}

		// tabulate results from all threads.
		#pragma omp critical
		{
			for(uint i = 0; i < numActiveSamples; ++i)
			{
				for(uint j = i+1; j < numActiveSamples; ++j)
				{
					matrix[i][j].uniqueI += tempMatrix[i][j].uniqueI;
					matrix[i][j].uniqueJ += tempMatrix[i][j].uniqueJ;
					matrix[i][j].shared += tempMatrix[i][j].shared;
					matrix[i][j].root += tempMatrix[i][j].root;
					matrix[i][j].external += tempMatrix[i][j].external;
					matrix[i][j].outgroup += tempMatrix[i][j].outgroup;
				}
			}
		}
	}

	// Calculate UniSplit distance.
	QVector< QVector< double > > results(numActiveSamples, QVector< double >(numActiveSamples));
	for(uint i = 0; i < numActiveSamples; ++i)
	{
		results[i][i] = 0.0;

		for(uint j = i+1; j < numActiveSamples; ++j)
		{
			double dist = (matrix[i][j].uniqueI + matrix[i][j].uniqueJ);
			if(GetSplitsToConsider() == COMMON_SPLIT_SET)
				dist /= matrix[i][j].uniqueI + matrix[i][j].uniqueJ + matrix[i][j].shared;
			else if(GetSplitsToConsider() == COMPLETE_LINEAGE)
				dist /= (matrix[i][j].uniqueI + matrix[i][j].uniqueJ + matrix[i][j].shared + matrix[i][j].root);
			else if(GetSplitsToConsider() == ALL_SPLITS)
				dist /= (matrix[i][j].uniqueI + matrix[i][j].uniqueJ + matrix[i][j].shared + matrix[i][j].root + matrix[i][j].external);

			results[i][j] = dist;
			results[j][i] = dist;
		}
	}

	return results;
}

typedef struct UNISPLIT_DATA_WEIGHTED
{
	UNISPLIT_DATA_WEIGHTED(): uniqueEvolution(0.0), normFactor(0.0) {}

	double uniqueEvolution;
	double normFactor;
} UniSplitDataWeighted;

Matrix UniSplit::CalculateWeightedUniSplit()
{
	QList<uint> activeSamples = m_splitSystem->GetSamples()->GetActiveSampleIds().toList();
	uint numActiveSamples = activeSamples.size();

	QVector< QVector< UniSplitDataWeighted > > matrix(numActiveSamples);
	for(int i = 0; i < matrix.size(); ++i)
		matrix[i] = QVector<UniSplitDataWeighted>(numActiveSamples);

	const QList<Split>& splits = m_splitSystem->GetSplits();
	QVector< QVector< UniSplitDataWeighted > > tempMatrix;
	#pragma omp parallel private(tempMatrix)
	{
		tempMatrix.resize(numActiveSamples);
		for(uint i = 0; i < numActiveSamples; ++i)
			tempMatrix[i].resize(numActiveSamples);

		#pragma omp for schedule(static) nowait
		for(int splitId = 0; splitId < splits.size(); ++splitId)
		{
			QVector<uint> leftSeqCounts, rightSeqCounts;
			bool bOutgroupSeqOnLeft, bOutgroupSeqOnRight;
			if(CalculateSeqsInSample(splits.at(splitId), leftSeqCounts, rightSeqCounts, bOutgroupSeqOnLeft, bOutgroupSeqOnRight))
			{
				// Determined unique evolution along with total evolution within the network for all pairs of samples.
				for(uint i = 0; i < numActiveSamples; ++i)
				{
					uint iIndex = activeSamples.at(i);

					for(uint j = i+1; j < numActiveSamples; ++j)
					{		
						uint jIndex = activeSamples.at(j);

						double normSeqCountI, normSeqCountJ;

						if(bOutgroupSeqOnLeft)
						{
							normSeqCountI = double(rightSeqCounts.at(iIndex)) / m_splitSystem->GetSamples()->GetSequences()->GetNumSequencesInSample(iIndex);
							normSeqCountJ = double(rightSeqCounts.at(jIndex)) / m_splitSystem->GetSamples()->GetSequences()->GetNumSequencesInSample(jIndex);
						}
						else
						{
							normSeqCountI = double(leftSeqCounts.at(iIndex)) / m_splitSystem->GetSamples()->GetSequences()->GetNumSequencesInSample(iIndex);	
							normSeqCountJ = double(leftSeqCounts.at(jIndex)) / m_splitSystem->GetSamples()->GetSequences()->GetNumSequencesInSample(jIndex);
						}

						tempMatrix[i][j].uniqueEvolution += splits.at(splitId).GetWeight()*fabs(normSeqCountI - normSeqCountJ);

						// Calculate normalization factor. This is just the weighted sum of split weights, 
						// where the weighting is the proportion of sequences 'descendant' from that split.
						if(GetSplitsToConsider() == COMMON_SPLIT_SET)
						{
							double shared = std::min(normSeqCountI, normSeqCountJ);
							tempMatrix[i][j].normFactor += splits.at(splitId).GetWeight()*std::min(shared, 1 - shared); 
							tempMatrix[i][j].normFactor += splits.at(splitId).GetWeight()*fabs(normSeqCountI - normSeqCountJ);
						}
						else if(GetSplitsToConsider() == COMPLETE_LINEAGE)
						{
							tempMatrix[i][j].normFactor += splits.at(splitId).GetWeight()*(normSeqCountI + normSeqCountJ);
							tempMatrix[i][j].normFactor += splits.at(splitId).GetWeight()*fabs(normSeqCountI - normSeqCountJ);
						}
						else if(GetSplitsToConsider() == NORMALIZED_WEIGHTED_UNIFRAC)
						{
							tempMatrix[i][j].normFactor += splits.at(splitId).GetWeight()*(normSeqCountI + normSeqCountJ);
						}
					}
				}
			}
		}

		// tabulate results from all threads.
		#pragma omp critical
		{
			for(uint i = 0; i < numActiveSamples; ++i)
			{
				for(uint j = i+1; j < numActiveSamples; ++j)
				{
					matrix[i][j].uniqueEvolution += tempMatrix[i][j].uniqueEvolution;
					matrix[i][j].normFactor += tempMatrix[i][j].normFactor;
				}
			}
		}
	}

	// Calculate normalization factor for 'complete network' measure
	double allSplitNorm = 0.0;
	if(GetSplitsToConsider() == ALL_SPLITS && IsNormalized())	
	{		
		for(int splitId = 0; splitId < splits.size(); ++splitId)
		{
			double minProp = INT_MAX;
			double maxProp = INT_MIN;

			QVector<uint> leftSeqCounts, rightSeqCounts;
			bool bOutgroupSeqOnLeft, bOutgroupSeqOnRight;
			if(CalculateSeqsInSample(splits.at(splitId), leftSeqCounts, rightSeqCounts, bOutgroupSeqOnLeft, bOutgroupSeqOnRight))
			{
				for(uint i = 0; i < numActiveSamples; ++i)
				{
					uint iIndex = activeSamples.at(i);

					double prop = double(leftSeqCounts.at(iIndex)) / m_splitSystem->GetSamples()->GetSequences()->GetNumSequencesInSample(iIndex);
					minProp = std::min(minProp, prop);
					maxProp = std::max(maxProp, prop);
				}

				allSplitNorm += (maxProp - minProp)*splits.at(splitId).GetWeight();
			}
		}
	}

	// Calculate weighted UniSplit distance.
	QVector< QVector< double > > results(numActiveSamples, QVector<double>(numActiveSamples));
	for(uint i = 0; i < numActiveSamples; ++i)
	{
		results[i][i] = 0.0;

		for(uint j = i+1; j < numActiveSamples; ++j)
		{
			double dist;
			if(IsNormalized())
			{
				if(GetSplitsToConsider() == ALL_SPLITS)
					dist = matrix[i][j].uniqueEvolution / allSplitNorm;
				else if(GetSplitsToConsider() == NORMALIZED_WEIGHTED_UNIFRAC)
					dist = matrix[i][j].uniqueEvolution / matrix[i][j].normFactor;
				else
					dist = 2.0*matrix[i][j].uniqueEvolution / matrix[i][j].normFactor;
			}
			else
			{
				// since weights are originally normalized so total evolution in 
				// network is unity, we need to multiply by this factor to indicate
				// the amount of evolution in the network that is unique to any pair of samples
				dist = matrix[i][j].uniqueEvolution * m_splitSystem->GetTotalEvolution();
			}

			results[i][j] = dist;
			results[j][i] = dist;		
		}
	}

	return results;
}

bool UniSplit::CalculateSeqsInSample(const Split& split, QVector<uint>& leftSeqCounts, QVector<uint>& rightSeqCounts,
																			bool& bOutgroupSeqOnLeft, bool& bOutgroupSeqOnRight)
{
	uint numSamples = m_splitSystem->GetSamples()->GetNumSamples();

	const QBitArray splitArray = split.GetSplitArray();
	uint sizeLeftBipartition = split.GetSizeLeftBipartition();
	uint sizeRightBipartition = split.GetSizeRightBipartition();

	m_splitSystem->CheckForOutgroupSeqs(split, bOutgroupSeqOnLeft, bOutgroupSeqOnRight);

	// If there are outgroup sequences present on both sides of the split,
	// the direction of evolution is unclear. As such, we ignore the split.
	if(bOutgroupSeqOnLeft && bOutgroupSeqOnRight)
		return false;

	// If a subset consists entirely of outgroup sequences this split should not contribute
	// to the calculated distance
	if(sizeLeftBipartition == (uint)splitArray.size() || sizeRightBipartition == (uint)splitArray.size())
		return false;

	leftSeqCounts = QVector<uint>(numSamples, 0);
	rightSeqCounts = QVector<uint>(numSamples, 0);
	if(sizeLeftBipartition < sizeRightBipartition)
	{
		if(sizeLeftBipartition == 1 && split.IsOutgroupSeqOnRight())
		{
			// The id of a split is always set to the sequence id for trivial splits. This has been done
			// to permit trivial splits to be efficently processed using this check.
			QVector<uint> data;
			bool bActiveSeq = m_splitSystem->GetSamples()->GetSequences()->GetSequenceAbundanceInSamples(split.GetId(), data);
			if(bActiveSeq)
			{
				for(uint j = 0; j < numSamples; ++j)
				{
					leftSeqCounts[j] += data.at(j);
				}
			}
		}
		else
		{
			for(int i = 0; i < splitArray.size(); ++i)
			{		
				if(splitArray.testBit(i))
				{
					QVector<uint> data;
					bool bActiveSeq = m_splitSystem->GetSamples()->GetSequences()->GetSequenceAbundanceInSamples(i, data);
					if(bActiveSeq)
					{
						for(uint j = 0; j < numSamples; ++j)
						{
							leftSeqCounts[j] += data.at(j);
						}
					}
				}			
			}
		}

		for(uint j = 0; j < numSamples; ++j)
			rightSeqCounts[j] = m_splitSystem->GetSamples()->GetSequences()->GetNumSequencesInSample(j) - leftSeqCounts.at(j);
	}		
	else
	{
		if(sizeRightBipartition == 1 && split.IsOutgroupSeqOnLeft())
		{
			// The id of a split is always set to the sequence id for trivial splits. This has been done
			// to permit trivial splits to be efficently processed using this check.
			QVector<uint> data;
			bool bActiveSeq = m_splitSystem->GetSamples()->GetSequences()->GetSequenceAbundanceInSamples(split.GetId(), data);
			if(bActiveSeq)
			{
				for(uint j = 0; j < numSamples; ++j)
				{
					rightSeqCounts[j] += data.at(j);
				}
			}
		}
		else
		{
			for(int i = 0; i < splitArray.size(); ++i)
			{		
				if(!splitArray.testBit(i))
				{
					QVector<uint> data;
					bool bActiveSeq =m_splitSystem->GetSamples()->GetSequences()->GetSequenceAbundanceInSamples(i, data);
					if(bActiveSeq)
					{
						for(uint j = 0; j < numSamples; ++j)
						{
							rightSeqCounts[j] += data.at(j);
						}
					}
				}
			}
		}

		for(uint j = 0; j < numSamples; ++j)
			leftSeqCounts[j] = m_splitSystem->GetSamples()->GetSequences()->GetNumSequencesInSample(j) - rightSeqCounts.at(j);
	}		

	return true;
}

void UniSplit::SignificanceTest(uint iterations, Matrix& signMatrix)
{
	Matrix origDistMatrix = Run();
	signMatrix.resize(m_splitSystem->GetSamples()->GetNumSamples());
	for(int i = 0; i < signMatrix.size(); ++i)
		signMatrix[i] = QVector<double>(m_splitSystem->GetSamples()->GetNumSamples(), 1.00);

	for(uint i = 0; i < m_splitSystem->GetSamples()->GetNumSamples(); ++i)
	{
		for(uint j = i+1; j < m_splitSystem->GetSamples()->GetNumSamples(); ++j)
		{
			QList<double> pdf;
			SignificanceTest(i, j, iterations, pdf);
			
			double pValue = StatsUtils::MonteCarloSign(origDistMatrix.at(i).at(j), pdf, StatsUtils::GreaterTest);
			signMatrix[i][j] = pValue;
			signMatrix[j][i] = pValue;
		}
	}
}

void UniSplit::SignificanceTest(uint sampleId1, uint sampleId2, uint iterations, QList<double>& pdf)
{
	/*
	// setup vector of sample labels
	uint seqInSample1 = m_splitSystem->GetNumSequencesInSample(sampleId1, IsWeighted());
	uint seqInSample2 = m_splitSystem->GetNumSequencesInSample(sampleId2, IsWeighted());
	QVector<uint> sampleLabels(seqInSample1, 0);
	sampleLabels.insert(seqInSample1, seqInSample2, 1);

	// modify split system to contain only the two samples of interest
	QVector< QVector<uint> > originalAbundancyMatrix = m_splitSystem->GetAbundancyMatrix();	// BAD!!! this doesn't recognize the active set!
	QList<Sample> originalSamples;
	m_splitSystem->GetDeepCopyOfSamples(originalSamples);

	QVector< QVector<uint> > newAbundancyMatrix(originalAbundancyMatrix.size());
	for(int i = 0; i < newAbundancyMatrix.size(); ++i)
		newAbundancyMatrix[i] = QVector<uint>(2, 0);

	QList<Sample> newSamples;
	newSamples.push_back(originalSamples.at(sampleId1));
	newSamples.push_back(originalSamples.at(sampleId2));
	m_splitSystem->SetSamples(newSamples);

	// Randomly permute sample labels and calculate distance between samples.
	for(uint i = 0; i < iterations; ++i)
	{
		// randomly permute sample labels
		MathUtils::RandomShuffle<uint>(sampleLabels);

		// create new abundance matrix
		uint index = 0;
		for(int seqId = 0; seqId < newAbundancyMatrix.size(); ++seqId)
		{
			newAbundancyMatrix[seqId][0] = 0;
			newAbundancyMatrix[seqId][1] = 0;

			uint totalSeq = 0;
			if(IsWeighted())
			{
				totalSeq = originalAbundancyMatrix.at(seqId).at(sampleId1) + originalAbundancyMatrix.at(seqId).at(sampleId2);
			}
			else
			{
				if(originalAbundancyMatrix.at(seqId).at(sampleId1) > 0)
					totalSeq++;

				if(originalAbundancyMatrix.at(seqId).at(sampleId2) > 0)
					totalSeq++;
			}

			for(uint j = 0; j < totalSeq; ++j)
			{
				newAbundancyMatrix[seqId][sampleLabels.at(index)]++;
				index++;
			}
		}

		// calculate distance between samples with permutated labels
		m_splitSystem->SetAbundancyMatrix(newAbundancyMatrix);

		Matrix dist = Run();
		pdf.push_back(dist.at(0).at(1));
	}

	// set split system and UniSplit results back to those for the original data
	m_splitSystem->SetAbundancyMatrix(originalAbundancyMatrix);
	m_splitSystem->SetSamples(originalSamples);
	Run();
	*/
}

void UniSplit::Jackknife(Cluster::CLUSTER_TYPE clusterType, uint iterations, uint seqToKeep)
{
	if(m_dissimilarityMatrix.size() == 0)
	{
		QMessageBox::information(0, "UniSplit", "Phylogenetic diversity measure must be run first.", QMessageBox::Ok);
		return;
	}

	// get name of each sample
	QStringList orderedLabels = m_splitSystem->GetSamples()->GetActiveSampleNames();

	// perform clustering of original data
	Cluster::Clustering(clusterType, m_dissimilarityMatrix, orderedLabels, m_clusterTree);

	// At this point, the leaf nodes will be labelled 0 to <number of samples-1>.
	// However, they will not correspond correctly to the actual sample id of
	// each leaf node so here we reset the sample ids.
	QList<VisualNode*> leaves = m_clusterTree.GetLeaves();
	foreach(VisualNode* leaf, leaves)
	{
		Sample sample;
		uint sampleId;
		if(m_splitSystem->GetSamples()->GetSample(leaf->GetName(), sample))
			sampleId = sample.GetId();
		else
			Log::Inst().Error("Invalid sample specified when performing jackknifing: " + leaf->GetName());

		leaf->SetId(sampleId);
	}

	// calculate the cophenetic correlation between the distance matrix and resulting cophenetic matrix
	double corr = Cluster::CopheneticCorrelation(m_dissimilarityMatrix, m_clusterTree);
	Log::Inst().Write("Cophenetic correlation = " + QString::number(corr));

	// Perform jackknife replications. On each replicate, the specified
	// number of reads will be randomly selected from each community
	// without replacement.	
	QProgressDialog progress("Calculating jackknife values...", "Cancel", 0, iterations, 0);
	progress.setWindowModality(Qt::ApplicationModal);

	QVector< QVector<uint> > originalAbundancyMatrix = m_splitSystem->GetSamples()->GetSequences()->GetAbundancyMatrix();
	
	QList< Tree<VisualNode> > jackknifeTrees;
	for(uint i = 0; i < iterations; ++i)
	{
		progress.setValue(i);

		if(progress.wasCanceled())
			break;

		// save new copy of original sample data
		QList<Sample> originalSamples;
		m_splitSystem->GetSamples()->GetDeepCopyOfSamples(originalSamples);

		// jackknife split system
		m_splitSystem->Jackknife(seqToKeep, IsWeighted());
		Matrix distMatrix = Run();

		Tree<VisualNode> tree;
		Cluster::Clustering(clusterType, distMatrix, orderedLabels, tree);
		jackknifeTrees.push_back(tree);

		// restore original split system
		m_splitSystem->GetSamples()->GetSequences()->SetAbundancyMatrix(originalAbundancyMatrix);
		m_splitSystem->GetSamples()->SetSamples(originalSamples);
	}
	progress.setValue(iterations);

	Cluster::SupportTree(m_clusterTree, jackknifeTrees);

	if(iterations > 0)
		Run(); // restore original dissimilarity matrix by running analysis on original data set
}

void UniSplit::Cluster(Cluster::CLUSTER_TYPE clusterType)
{
	// get name of each sample
	QStringList orderedLabels = m_splitSystem->GetSamples()->GetActiveSampleNames();

	// perform clustering of original data
	Cluster::Clustering(clusterType, m_dissimilarityMatrix, orderedLabels, m_clusterTree);
}

QString UniSplit::GetMethodMessage() const
{
	QString message;
	if(m_measureType == UNWEIGHTED)
		message += "Unweighted";
	else if(m_measureType == WEIGHTED || m_measureType == WEIGHTED_NORMALIZED)
		message += "Weighted";

	if(m_splitsToConsidered == COMMON_SPLIT_SET)
		message += ", common split set";
	else if(m_splitsToConsidered == COMPLETE_LINEAGE)
		message += ", complete lineage";
	else if(COMPLETE_LINEAGE == ALL_SPLITS)
		message += ", all splits";
	else
		message += ", UniFrac";

	if(m_measureType == WEIGHTED_NORMALIZED)
		message += "(normalized)";

	return message;
}
