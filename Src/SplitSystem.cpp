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

#include "SplitSystem.hpp"

#include "Log.hpp"

#include "NewickIO.hpp"
#include "NexusIO.hpp"
#include "MathUtils.hpp"

#include "Samples.hpp"

SplitSystem::SplitSystem(): m_totalEvolution(1), m_currentRoot(NULL)
{

}

bool SplitSystem::LoadData(const QString& phylogenyFile, const QString& samplesFile, const QString& metadataFile, bool bImplicitlyRooted)
{
	Log::Inst().Debug("SplitSystem::LoadData()");

	// parse sample file	
	if(!GetSamples()->LoadFromSampleFile(samplesFile))
	{
		Log::Inst().Error("Unable to parse environment file.");
		return false;
	}

	// parse metadata file
	if(!GetSamples()->GetMetadata()->Load(metadataFile))
	{
		Log::Inst().Error("Unable to parse metadata file.");
		return false;
	}

	// parse phylogeny file
	QString extension = phylogenyFile.mid(phylogenyFile.lastIndexOf(".")+1);
	extension = extension.toLower();

	if(extension == "new" || extension == "tre" || extension == "tree")
	{
		NewickIO newickIO;
		if(!newickIO.Read(this, phylogenyFile, bImplicitlyRooted))
		{
			Log::Inst().Error("Unable to parse Newick tree file.");
			return false;
		}
	}
	else if(extension == "nxs" || extension == "nex" || extension == "nexus")
	{
		NexusIO nexusIO;
		if(!nexusIO.Read(this, phylogenyFile, bImplicitlyRooted))
		{
			Log::Inst().Error("Unable to parse Nexus tree file.");
			return false;
		}
	}
	else
	{
		Log::Inst().Warning("Unrecognized file extension. Require a Newick (*.new, *.tre, *.tree) tree file or a Nexus (*.nxs, *.new, *.nexus) file with a splits block.");
		return false;
	}

	return true;
}

bool SplitSystem::IsOutgroupMonophyletic() const
{
	foreach(const Split& split, m_splits)
	{
		bool bOutgroupSeqOnLeft, bOutgroupSeqOnRight;
		CheckForOutgroupSeqs(split, bOutgroupSeqOnLeft, bOutgroupSeqOnRight);

		if((bOutgroupSeqOnLeft && split.GetSizeLeftBipartition() > 0) 
				&& (bOutgroupSeqOnRight && split.GetSizeRightBipartition() > 0))
			return false;
	}

	return true;
}

void SplitSystem::Jackknife(uint seqToKeep, bool bWeighted)
{
	QSet<uint> activeSampleIds = GetSamples()->GetActiveSampleIds();
	QVector< QVector<uint> > newAbundancyMatrix(GetSamples()->GetSequences()->GetAbundancyMatrix().size());
	for(int seqId = 0; seqId < newAbundancyMatrix.size(); ++seqId)
		newAbundancyMatrix[seqId] = QVector<uint>(GetSamples()->GetSequences()->GetAbundancyMatrix().at(0).size(), 0);

	foreach(uint sampleId, activeSampleIds)
	{
		uint seqInSample = GetSamples()->GetSequences()->GetNumSequencesInSample(sampleId, bWeighted);

		// create vector with entry for each sampled read
		// e.g., if sequence with ID of 4 is present 10 times, the vector will contain 10 4's
		QVector<uint> readVec(seqInSample);
		uint index = 0;
		for(int seqId = 0; seqId < GetSamples()->GetSequences()->GetAbundancyMatrix().size(); ++seqId)
		{
			// for unweighted jackknife abundance information is ignored
			uint seqCount = GetSamples()->GetSequences()->GetNumSequences(seqId, sampleId);
			if(!bWeighted && seqCount > 0)	// for the unweighted case either the sequences is present or not
					seqCount = 1;

			for(uint i = 0; i < seqCount; ++i)
			{
				readVec[index] = seqId;
				index++;
			}
		}

		// randomly permute the vector
		MathUtils::RandomShuffle<uint>(readVec);

		// subsampled reads are the first seqToKeep ids in the permuted reads vector
		for(uint i = 0; i < qMin<uint>(seqToKeep, seqInSample); ++i)
			newAbundancyMatrix[readVec.at(i)][sampleId]++;

		GetSamples()->GetSample(sampleId).SetNumSequences(qMin<uint>(seqToKeep, seqInSample));
	}

	GetSamples()->GetSequences()->SetAbundancyMatrix(newAbundancyMatrix);
}

void SplitSystem::Print() const
{
	foreach(Split split, m_splits)
	{
		split.Print();
	}
}

void SplitSystem::CheckForOutgroupSeqs(const Split& split, bool& bOutgroupSeqOnLeft, bool& bOutgroupSeqOnRight) const
{
	bOutgroupSeqOnLeft = split.IsOutgroupSeqOnLeft();
	bOutgroupSeqOnRight = split.IsOutgroupSeqOnRight();
}

bool SplitSystem::IsCompatible()
{
	for(int i = 0; i < m_splits.size()-1; ++i)
	{
		QSet<uint> iLeft;
		foreach(uint id, m_splits.at(i).GetLeftSequenceIds())
			iLeft.insert(id);

		QSet<uint> iRight;
		foreach(uint id, m_splits.at(i).GetRightSequenceIds())
			iRight.insert(id);

		bool bCompatible = false;
		for(int j = i+1; j < m_splits.size(); ++j)
		{
			QSet<uint> jLeft;
			foreach(uint id, m_splits.at(j).GetLeftSequenceIds())
				jLeft.insert(id);

			QSet<uint> jRight;
			foreach(uint id, m_splits.at(j).GetRightSequenceIds())
				jRight.insert(id);

			QSet<uint> intersectionLeft = iLeft;
			if(intersectionLeft.intersect(jLeft).empty())
			{
				bCompatible = true;
				break;
			}

			intersectionLeft = iLeft;
			if(intersectionLeft.intersect(jRight).empty())
			{
				bCompatible = true;
				break;
			}

			QSet<uint> intersectionRight = iRight;
			if(intersectionRight.intersect(jLeft).empty())
			{
				bCompatible = true;
				break;
			}

			intersectionRight = iRight;
			if(intersectionRight.intersect(jRight).empty())
			{
				bCompatible = true;
				break;
			}
		}

		if(!bCompatible)
			return false;
	}

	return true;
}

bool splitSizeLessThan(const Split& s1, const Split& s2)
{
	uint s1Size = s1.GetSize();
	uint s2Size = s2.GetSize();

	return s1Size < s2Size;
}

void SplitSystem::CreateTree(Tree<VisualNode>& tree)
{
	QList<Split> splits = m_splits;

	// sort splits according to size of each split
	qSort(splits.begin(), splits.end(), splitSizeLessThan);

	// find implicit root in tree (i.e., set of identical splits).
	bool bFound = false;
	for(int i = 0; i < splits.size() && !bFound; ++i)
	{
		Split iSplit = splits.at(i);
		for(int j = i+1; j < splits.size() && !bFound; ++j)
		{
			Split jSplit = splits.at(j);

			// the identical splits will actually be complements of each other as the left
			// and right bipartitions will be swapped
			QBitArray count = iSplit.GetSplitArray() ^ jSplit.GetSplitArray();
			if(count.count(false) == 0)
			{
				splits[i].SetWeight(splits.at(i).GetWeight() + splits.at(j).GetWeight());
				splits.removeAt(j);
				bFound = true;
			}
		}
	}

	// Create tree starting from leaf nodes and working towards root.
	QList<VisualNode*> topNodes;
	int nodeId = splits.at(0).GetSplitArray().size();
	for(int i = 0; i < splits.size(); ++i)
	{
		Split curSplit = splits.at(i);

		QVector<uint> ids = splits.at(i).GetSequencesIdsInSmallestBipartition();
		if(ids.size() == 1)
		{
			//process leaf node
			VisualNode* leaf = new VisualNode(ids.at(0));

			QString seqName;
			GetSamples()->GetSequences()->GetSequenceName(ids.at(0), seqName);
			leaf->SetName(seqName);
			leaf->SetDistanceToParent(curSplit.GetWeight());
			topNodes.push_back(leaf);
		}
		else
		{
			QSet<uint> idSet;
			foreach(uint id, ids)
				idSet.insert(id);

			// process internal node
			VisualNode* node = new VisualNode(nodeId++);
			node->SetDistanceToParent(curSplit.GetWeight());
			node->SetName("Node" + QString::number(nodeId));
			QStack<uint> nodesToRemove;
			for(int j = 0; j < topNodes.size(); ++j)
			{
				VisualNode* topNode = topNodes.at(j);

				QList<uint> childrenIds;
				if(topNode->IsLeaf())
					childrenIds.push_back(topNode->GetId());
				else
					childrenIds = TreeTools<VisualNode>::GetLeafIds(topNode);

				if(childrenIds.toSet().subtract(idSet).empty())
				{
					idSet -= childrenIds.toSet();
					nodesToRemove.push(j);
					node->AddChild(topNode);
				}
				
				if(idSet.empty())
					break;
			}

			while(!nodesToRemove.empty())
			{
				topNodes.removeAt(nodesToRemove.pop());
			}

			topNodes.push_back(node);
		}
	}

	VisualNode* root = new VisualNode(nodeId++);
	root->SetName("Root");
	tree.SetRootNode(root);

	VisualNode* internalNode = new VisualNode(nodeId++);
	internalNode->SetName("internalNode");
	for(int i = 0; i < topNodes.size()-1; ++i)
		internalNode->AddChild(topNodes.at(i));

	internalNode->SetDistanceToParent(topNodes.at(topNodes.size()-1)->GetDistanceToParent()*0.5);
	topNodes.at(topNodes.size()-1)->SetDistanceToParent(internalNode->GetDistanceToParent());

	root->AddChild(topNodes.at(topNodes.size()-1));
	root->AddChild(internalNode);
}

bool SplitSystem::CreateFromTree(VisualNode* root)
{
	Log::Inst().Debug("Entering SplitSystem::CreateFromTree()");

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

	if(m_currentRoot == root)
	{
		QApplication::restoreOverrideCursor();
		return true;
	}

	m_currentRoot = root;

	m_splits.clear();

	// count sequence from each sample and flag active sequences
	for(uint i = 0; i < GetSamples()->GetNumSamples(); ++i)
		GetSamples()->GetSample(i).SetNumSequences(0);

	GetSamples()->GetSequences()->SetActiveStateOfSeqs(false);

	QList<VisualNode*> leaves = TreeTools<VisualNode>::GetLeaves(root);
	uint numberOfLeaves = 0;
	foreach(VisualNode* leaf, leaves)
	{
		if(GetSamples()->GetSequences()->IsOutgroupSequence(leaf->GetName()))
			continue;

		GetSamples()->GetSequences()->SetSequenceToActive(leaf->GetId());

		QVector<uint> seqsInSamples = GetSamples()->GetSequences()->GetAbundancyMatrix()[leaf->GetId()];
		for(uint sampleId = 0; sampleId < GetSamples()->GetNumSamples(); ++sampleId)
			GetSamples()->GetSample(sampleId).SetNumSequences(GetSamples()->GetSample(sampleId).GetNumSequences() + seqsInSamples[sampleId]);

		numberOfLeaves++;
	}

	// determine total evolution in tree
	QList<VisualNode*> nodes = TreeTools<VisualNode>::GetNodes(root); 
	double totalEvolution = 0;
	foreach(VisualNode* node, nodes)
	{
		if(node != root)
			totalEvolution += node->GetDistanceToParent();
	}
	SetTotalEvolution(totalEvolution);

	// determine split for each node in the tree
	QList<Split> tempSplits;
	#pragma omp parallel private(tempSplits)
	{
		#pragma omp for schedule(static) nowait
		for(int i = 0; i < nodes.size(); ++i)
		{
			VisualNode* node = nodes.at(i);

			uint numSeqOnLeft = 0;
			if(node != root)
			{
				// bit array indicates the id of sequences on the left (1) and right (0) of the split
				uint outgroupSeqOnLeft = 0;
				QBitArray split(GetSamples()->GetSequences()->GetNumSequences()); 
				if(node->IsLeaf())
				{
					uint id = node->GetId();
					if(id < GetSamples()->GetSequences()->GetNumSequences())
					{
						split.setBit(id);
						numSeqOnLeft = 1;
					}
					else
					{
						if(id == Tree<VisualNode>::ROOT_ID)
							outgroupSeqOnLeft++;
						else
							Log::Inst().Error("Bug: Invalid leaf id detected in SplitSystem::CreateFromTree(Tree<VisualNode>& tree, bool bImplicitlyRooted)");
					}					
				}
				else
				{
					QList<uint> leafIds = TreeTools<VisualNode>::GetLeafIds(node);
					foreach(uint id, leafIds)
					{
						if(id < GetSamples()->GetSequences()->GetNumSequences())
						{
							split.setBit(id);
							numSeqOnLeft++;
						}
						else
						{							
							if(id == Tree<VisualNode>::ROOT_ID)
								outgroupSeqOnLeft++;
							else
								Log::Inst().Error("Bug: Invalid leaf id detected in SplitSystem::CreateFromTree(Tree<VisualNode>& tree, bool bImplicitlyRooted)");
						}		
					}
				}

				bool bOutgroupSeqOnLeft = (outgroupSeqOnLeft > 0);
				bool bOutgroupSeqOnRight = (GetSamples()->GetSequences()->GetNumberOutgroupSeq() != outgroupSeqOnLeft);
				tempSplits.push_back(Split(node->GetId(), node->GetDistanceToParent() / totalEvolution, split, bOutgroupSeqOnLeft, bOutgroupSeqOnRight, numSeqOnLeft, numberOfLeaves - numSeqOnLeft));
			}
		}

		// tabulate results from all threads.
		#pragma omp critical
		{
			AddSplits(tempSplits);
		}
	}

	QApplication::restoreOverrideCursor();

	Log::Inst().Debug("Leaving SplitSystem::CreateFromTree()");

	return true;
}