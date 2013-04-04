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

#include "Cluster.hpp"
#include "NeighbourJoining.hpp"


void Cluster::SupportTree(const Tree<VisualNode>& origTree, const QList< Tree<VisualNode> >& supportTrees)
{
	// initialize bootstrap counts to 0
	QList<VisualNode*> inputNodes = origTree.GetNodes();
	foreach(VisualNode* inputNode, inputNodes)
	{
		inputNode->SetSupport(0);
	}

	// find all matching splits in the input tree to each of the bootstrap trees
	for(int i = 0; i < supportTrees.size(); ++i)
	{
		QList<VisualNode*> supportNodes = supportTrees.at(i).GetNodes();
		foreach(VisualNode* inputNode, inputNodes)
		{
			QList<VisualNode*> inputLeafNodes = TreeTools<VisualNode>::GetLeaves(inputNode);
			foreach(VisualNode* supportNode, supportNodes)
			{
				QList<VisualNode*> supportLeafNodes = TreeTools<VisualNode>::GetLeaves(supportNode);

				// check if nodes have the same children (i.e., we have an identical split of the taxa)
				if(inputLeafNodes.size() == supportLeafNodes.size())
				{
					bool bIndenticalSplit = true;
					if(inputLeafNodes.size() != 0)
					{
						// internal node
						foreach(VisualNode* inputLeaf, inputLeafNodes)
						{
							bool bMatch = false;
							foreach(VisualNode* supportLeaf, supportLeafNodes)
							{
								if(inputLeaf->GetName() == supportLeaf->GetName())
								{
									bMatch = true;
									break;
								}
							}

							if(!bMatch)
							{
								bIndenticalSplit = false;
								break;
							}
						}
					}
					else
					{
						// leaf node
						bIndenticalSplit = (inputNode->GetName() == supportNode->GetName());
					}

					if(bIndenticalSplit)
					{
						inputNode->SetSupport(inputNode->GetSupport() + 1);
					}
				}
			}
		}
	}

	if(supportTrees.size() > 0)
	{
		foreach(VisualNode* inputNode, inputNodes)
		{
			double support = inputNode->GetSupport();			
			support = int((support/supportTrees.size())*100 + 0.5);			
			inputNode->SetSupport((int)support);
		}
	}
}


void Cluster::Clustering(CLUSTER_TYPE clusterType, const Matrix& _distMatrix, const QStringList& labels, Tree<VisualNode>& tree)
{
	if(clusterType == NEIGHBOUR_JOINING)
	{
		NJ(_distMatrix, labels, tree);
	}
	else
	{
		// keep original distance matrix unmodified
		Matrix distMatrix = _distMatrix;

		// create initial singleton clusters
		QList< VisualNode* > clusters;
		uint nodeId = 0;
		for(int i = 0; i < labels.size(); ++i)
		{
			VisualNode* node = new VisualNode(nodeId, labels.at(i));
			clusters.push_back(node);
			node->SetNumberOfLeaves(1);
			nodeId++;
		}

		// perform hierarchical clustering
		while(distMatrix.size() > 1)
		{
			// find nearest clusters
			uint row = 0, col = 0;
			FindNearestClusters(distMatrix, row, col);
			
			// update distance matrix 
			double dist = distMatrix.at(row).at(col);
			UpdateDistanceMatrix(clusterType, distMatrix, clusters, row, col);

			// update clusters in the cluster tree
			UpdateClusters(clusters, row, col, dist, nodeId);
		}

		if(clusters.size() != 1)
		{
			Log::Inst().Error("Error in clustering algorithm. Cluster size != 1.");
			return;
		}

		tree.SetRootNode(clusters.at(0));
	}

		// set name of tree to reflect clustering method
	if(clusterType == Cluster::COMPLETE_LINKAGE)
		tree.SetName("Complete linkage");
	else if(clusterType == Cluster::SINGLE_LINKAGE)
		tree.SetName("Single linkage");
	else if(clusterType == Cluster::AVERAGE_LINKAGE)
		tree.SetName("Average linkage (UPGMA)");
	else if(clusterType == Cluster::NEIGHBOUR_JOINING) 
		tree.SetName("Neighbour joining");

	tree.CalculateStatistics(SamplesPtr());
}

void Cluster::FindNearestClusters(Matrix& distMatrix, uint& row, uint& col)
{
	double minEntry = DBL_MAX;

	for(int i = 0; i < distMatrix.size()-1; ++i)
	{
		for(int j = i+1; j < distMatrix.at(i).size(); ++j)
		{
			if(distMatrix.at(i).at(j) < minEntry)
			{
				row = i;
				col = j;
				minEntry = distMatrix.at(i).at(j);
			}
		}
	}
}

double Cluster::GetDistanceToNode(VisualNode* node)
{
	QList<VisualNode*> leafNodes = TreeTools<VisualNode>::GetLeaves(node);
	
	// trace path from leaf node up to given node
	double dist = 0;
	VisualNode* curNode = leafNodes.at(0);
	while(curNode != node)
	{
		dist += curNode->GetDistanceToParent();
		curNode = curNode->GetParent();
	}

	return dist;
}

void Cluster::UpdateClusters(QList<VisualNode*>& clusters, uint row, uint col, double value, uint& nodeId)
{
	// create new node
	VisualNode* node = new VisualNode(nodeId);
	nodeId++;

	// set children of this node
	node->AddChild(clusters.at(row));
	node->AddChild(clusters.at(col));
	node->SetNumberOfLeaves(clusters.at(row)->GetNumberOfLeaves() + clusters.at(col)->GetNumberOfLeaves());

	// set distance from children to parent
	clusters.at(row)->SetDistanceToParent(value - GetDistanceToNode(clusters.at(row)));
	clusters.at(col)->SetDistanceToParent(value - GetDistanceToNode(clusters.at(col)));

	// add in new cluster to cluster vector and remove children clusters
	clusters[row] = node;
	clusters.removeAt(col);
}

void Cluster::UpdateDistanceMatrix(CLUSTER_TYPE clusterType, Matrix& distMatrix, QList<VisualNode*>& clusters, uint row, uint col)
{
	// find distance from each element to the new cluster
	QList< double > dist;
	for(int i = 0; i < distMatrix.size(); ++i)
	{
		dist.push_back(distMatrix.at(row).at(i));
	}

	for(int i = 0; i < distMatrix.size(); ++i)
	{
		if(clusterType == COMPLETE_LINKAGE)
		{
			if(distMatrix.at(col).at(i) > dist.at(i))
				dist[i] = distMatrix.at(col).at(i);
		}
		else if(clusterType == SINGLE_LINKAGE)
		{
			if(distMatrix.at(col).at(i) < dist.at(i))
				dist[i] = distMatrix.at(col).at(i);
		}
		else if(clusterType == AVERAGE_LINKAGE)
		{
			uint sizeClusterI = clusters.at(row)->GetNumberOfLeaves();
			uint sizeClusterJ = clusters.at(col)->GetNumberOfLeaves();
			dist[i] = (sizeClusterI*dist[i] + sizeClusterJ*distMatrix.at(col).at(i)) / (sizeClusterI + sizeClusterJ);
		}
	}

	// update distance matrix (place new cluster at the row position)
	for(int i = 0; i < distMatrix.size(); ++i)
	{
		if(row != (uint)i)
		{
			distMatrix[row][i] = dist.at(i);
			distMatrix[i][row] = dist.at(i);
		}
		else
			distMatrix[row][i] = 0;
	}

	// remove 'col' cluster from distance matrix
	distMatrix.remove(col);
	for(int i = 0; i < distMatrix.size(); ++i)
	{
		distMatrix[i].remove(col);
	}
}

void Cluster::NJ(const Matrix& _distMatrix, const QStringList& labels, Tree<VisualNode>& tree)
{
	// keep original distance matrix unmodified
	Matrix distMatrix = _distMatrix;

	NeighbourJoining nj;
	nj.BuildTree(distMatrix, labels, tree);
}

double Cluster::CopheneticCorrelation(const Matrix& observedDistMatrix, const Tree<VisualNode>& tree)
{
	// calculate cophenetic distance matrix
	QList<VisualNode*> leaves = tree.GetLeaves();
	Matrix copheneticMatrix(leaves.size());
	for(int i = 0; i < leaves.size(); ++i)
		copheneticMatrix[i].resize(leaves.size());

	for(int i = 0; i < leaves.size(); ++i)
	{
		copheneticMatrix[i][i] = 0.0;
		for(int j = i+1; j < leaves.size(); ++j)
		{
			// cluster trees represents distances as the distance to the MRCA node
			// which is half the distance between a pair of nodes
			copheneticMatrix[i][j] = 0.5*TreeTools<VisualNode>::GetDistanceBetweenAnyTwoNodes(leaves.at(i), leaves.at(j));
			copheneticMatrix[j][i] = copheneticMatrix[i][j];
		}
	}

	// calculate mean distances
	double meanObsDist = 0.0;
	double meanCopheneticDist = 0.0;
	uint dists = 0;
	for(int i = 0; i < observedDistMatrix.size(); ++i)
	{
		for(int j = i+1; j < observedDistMatrix.size(); ++j)
		{
			meanObsDist += observedDistMatrix[i][j];
			meanCopheneticDist += copheneticMatrix[i][j];
			dists++;
		}
	}
	
	meanObsDist /= dists;
	meanCopheneticDist /= dists;

	// calculate cophenetic correlation
	double crossCorrelation = 0.0;
	double stdDevObs = 0.0;
	double stdDevCophenetic = 0.0;

	for(int i = 0; i < observedDistMatrix.size(); ++i)
	{
		for(int j = i+1; j < observedDistMatrix.size(); ++j)
		{
			double obsDist = observedDistMatrix[i][j] - meanObsDist;
			double copheneticDist = copheneticMatrix[i][j] - meanCopheneticDist;

			crossCorrelation += obsDist*copheneticDist;
			stdDevObs += obsDist*obsDist;
			stdDevCophenetic += copheneticDist*copheneticDist;
		}
	}

	double corr = crossCorrelation / sqrt(stdDevObs*stdDevCophenetic);

	return corr;
}