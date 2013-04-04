//=======================================================================
// Author: Donovan Parks
//
// Copyright 2011 Donovan Parks
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

#include "ISOMAP.hpp"

#include "PCoA.hpp"

#include "dgraph.h"
#include "dijkstra.h"   
#include "fheap.h" 

#include "Metadata.hpp"

void Isomap::Project(const Matrix& dissMatrix, const QString& neighbourhoodMethod, const QString& neighbourhoodField, double value)
{
	// --- Find geodesic distances between data points ---
	m_neighbourhoodGraph = NeighbourhoodGraph(dissMatrix, neighbourhoodMethod, neighbourhoodField, value);
	Matrix geoDissMatrix = ShortestPathDijkstra(m_neighbourhoodGraph);

	// --- Apply PCoA to distance matrix ---
	m_pcoa.Project(geoDissMatrix);

	Matrix projectedData = m_pcoa.GetProjectedData();
	Matrix ed;
	for(int i = 0; i < projectedData.size(); ++i)
	{
		QVector<double> row;
		for(int j = 0; j < projectedData.size(); ++j)
		{
			double dist = 0;
			for(int k = 0; k < projectedData.size(); ++k)
			{
				dist += (projectedData[i][k] - projectedData[j][k])*(projectedData[i][k] - projectedData[j][k]);
			}
			row.push_back(dist);
		}

		ed.push_back(row);
	}

	QVector<double> eigenValues = m_pcoa.GetEigenvalues();
	QVector<double> variance = m_pcoa.GetVariance();
	QVector<double> sumVariance = m_pcoa.GetSumVariance();

}

void Isomap::ProjectSingleManifold(const Matrix& dissMatrix, const QString& neighbourhoodMethod, const QString& neighbourhoodField, double value)
{
	// --- Find geodesic distances between data points ---
	Matrix geoDissMatrix = ShortestConnectedGraph(dissMatrix, neighbourhoodMethod, neighbourhoodField, value);

	// --- Apply PCoA to distance matrix ---
	m_pcoa.Project(geoDissMatrix);
}

Matrix Isomap::NeighbourhoodGraph(const Matrix& dissMatrix, const QString& neighbourhoodMethod, const QString& neighbourhoodField, double value)
{
	if(neighbourhoodMethod == "Fixed number of neighbours")
		return NearestNeighbourNG(dissMatrix, (uint)value);
	else if(neighbourhoodMethod == "Sample dissimilarity")
		return SampleDissimilarityNG(dissMatrix, value);
	else if(neighbourhoodMethod == "Quantitative factor")
		return QuantitativeFactorNG(dissMatrix, neighbourhoodField, value);

	return Matrix();
}

Matrix Isomap::NearestNeighbourNG(const Matrix& dissMatrix, uint k)
{
	Matrix minDist;
	for(int i = 0; i < dissMatrix.size(); ++i)
		minDist.append(QVector<double>(k, INFINITE_DIST));

	// find smallest k distances for each point
	for(int i = 0; i < dissMatrix.size(); ++i)
	{
		for(int j = 0; j < dissMatrix.size(); ++j)
		{
			if(i == j) 
				continue;

			for(uint n = 0; n < k; ++n)
			{
				if(dissMatrix[i][j] < minDist[i][n])
				{
					for(uint m = k-1; m > n; --m)
					{
						minDist[i][m] = minDist[i][m-1];
					}				

					minDist[i][n] = dissMatrix[i][j];

					break;
				}
			}
		}
	}

	// set all distances greater than the kth smallest distance to infinite
	Matrix neighbourhoodGraph = dissMatrix;
	for(int i = 0; i < neighbourhoodGraph.size(); ++i)
	{
		for(int j = 0; j < neighbourhoodGraph.size(); ++j)
		{
			if(neighbourhoodGraph[i][j]-1e-8 > minDist[i][k-1])
				neighbourhoodGraph[i][j] = INFINITE_DIST;
		}
	}

	return neighbourhoodGraph;
}

Matrix Isomap::SampleDissimilarityNG(const Matrix& dissMatrix, double radius)
{
	// set all distances outside the epislon radius to infinite
	Matrix neighbourhoodGraph = dissMatrix;
	for(int i = 0; i < neighbourhoodGraph.size(); ++i)
	{
		for(int j = 0; j < i; ++j)
		{
			if(neighbourhoodGraph[i][j] > radius)
			{
				neighbourhoodGraph[i][j] = INFINITE_DIST;
				neighbourhoodGraph[j][i] = INFINITE_DIST;
			}
		}
	}

	return neighbourhoodGraph;
}

Matrix Isomap::QuantitativeFactorNG(const Matrix& dissMatrix, const QString& field, double radius)
{
	// calculate quantitative factor dissimilarity matrix
	QVector<QString> values = m_metadata->GetValues(field);
	Matrix envDissMatrix;
	for(int i = 0; i < values.size(); ++i)
	{
		QVector<double> row;
		for(int j = 0; j < i; ++j)
			row.push_back(fabs(values.at(i).toDouble() - values.at(j).toDouble()));
		
		envDissMatrix.push_back(row);
	}

	// set all distances outside the epislon radius to infinite
	Matrix neighbourhoodGraph = dissMatrix;
	for(int i = 0; i < neighbourhoodGraph.size(); ++i)
	{
		for(int j = 0; j < i; ++j)
		{
			if(envDissMatrix[i][j] > radius)
			{
				neighbourhoodGraph[i][j] = INFINITE_DIST;
				neighbourhoodGraph[j][i] = INFINITE_DIST;
			}
		}
	}

	return neighbourhoodGraph;
}

Matrix Isomap::ShortestConnectedGraph(const Matrix& dissMatrix, const QString& neighbourhoodMethod, const QString& neighbourhoodField, double value)
{
	m_neighbourhoodGraph = NeighbourhoodGraph(dissMatrix, neighbourhoodMethod, neighbourhoodField, value);
	Matrix shortestPath = ShortestPathDijkstra(m_neighbourhoodGraph);
	
	// --- Find the connected components in the original graph ---
	QVector<int> component;
	QVector<int> label;
	m_numManifolds = ConnectedComponents(shortestPath, component, label);
	if(label.size() == 1)
		return shortestPath;

	// --- Find the shortest distance between connected components ---
	for(int c = 0; c < label.size() - 1; ++c)
	{
		int indexI;
		int indexJ;
		int minLabel;
		double minDist = INFINITE_DIST;

		for(int i = 0; i < dissMatrix.size(); ++i)
		{
			// find shortest distance b/w unconnected components
			if(component[i] == label[0])
			{
				for(int j = 0; j < dissMatrix.size(); ++j)
				{
					if(component[i] != component[j])
					{
						if(dissMatrix[i][j] < minDist)
						{
							minDist = dissMatrix[i][j];
							indexI = i;
							indexJ= j;
							minLabel = component[j];
						}
					}
				}
			}
		}

		// add shortest distance to another component to neighbourhood graph
		m_neighbourhoodGraph[indexI][indexJ] = minDist;
		m_neighbourhoodGraph[indexJ][indexI] = minDist;

		// add all elements of this component to the first component
		for(int i = 0; i < component.size(); ++i)
		{
			if(component[i] == minLabel)
			{
				component[i] = label[0];
			}
		}
	}

	// --- Calculate shortest paths on modified neighbourhood graph ---
	shortestPath = ShortestPathDijkstra(m_neighbourhoodGraph);
	
	// --- Error check that we now have only one component ---
	ConnectedComponents(shortestPath, component, label);
	if(label.size() != 1)
		assert(false);

	return shortestPath;
}

uint Isomap::ConnectedComponents(const Matrix& dissMatrix, QVector<int>& component, QVector<int>& label)
{
	// --- Find first connected point for each row ---
	component.resize(dissMatrix.size());
	for(int i = 0; i < dissMatrix.size(); ++i)
	{
		for(int j = 0; j < dissMatrix.size(); ++j)
		{
			if(dissMatrix[i][j] != INFINITE_DIST)
			{
				component[i] = j;
				break;
			}
		}
	}

	// --- Count number of connected components ---
	label.clear();
	for(int i = 0; i < component.size(); ++i)
	{
		bool newIndex = true;
		for(int j = 0; j < label.size(); ++j)
		{
			if(component[i] == label.at(j))
			{
				newIndex = false;
			}
		}

		if(newIndex)
		{
			label.append(component[i]);
		}
	}

	return label.size();
}

Matrix Isomap::ShortestPathDijkstra(const Matrix& dissMatrix)
{
	const double SCALE_FACTOR = 1e6;

	// --- Create neighbourhood graph ---
  DGraph *g = new DGraph(dissMatrix.size());
	for(int i = 0; i < dissMatrix.size(); ++i)
	{
		for(int j = i+1; j < dissMatrix.size(); ++j)
		{
			if(dissMatrix[i][j] != INFINITE_DIST)
			{
				g->addNewEdge(i, j, int(dissMatrix[i][j] * SCALE_FACTOR));
				g->addNewEdge(j, i, int(dissMatrix[j][i] * SCALE_FACTOR));
			}
		}
	}

	// --- Run Dijkstra for each node ---
	HeapD<FHeap> heapD;
	Dijkstra *dijkstra = new Dijkstra(dissMatrix.size(),&heapD);
	dijkstra->init(g);

	Matrix shortestPath;
	for(int i = 0; i < dissMatrix.size(); ++i)
		shortestPath.append(QVector<double>(dissMatrix.size()));

	long* d = new long[dissMatrix.size()];
	for(int i = 0; i < dissMatrix.size(); ++i)
	{
    dijkstra->run(d, i);

		// copy shortest path to matrix
		for(int j = 0; j < dissMatrix.size(); ++j)
		{
			if(d[j] != INFINITE_DIST)
				shortestPath[i][j] = double(d[j]) / 1e6;
			else
				shortestPath[i][j] = INFINITE_DIST;
		}
	}

	delete[] d;
	delete dijkstra;
	delete g;

	return shortestPath;
}
