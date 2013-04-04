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

#ifndef ISOMAP_HPP_
#define ISOMAP_HPP_

#include "stdafx.h"

#include "PCoA.hpp"

class Isomap
{
public:
	Isomap(): m_numManifolds(0) {}
	~Isomap() {;}

	/** Set metadata associated with samples. */
	void SetMetadata(MetadataPtr metadata) { m_metadata = metadata; }

  /**
	* Perform the standard ISOMAP algorithm.
	*
	* @param data Dissimilarity matrix to be embedded.
	* @param neighbourhoodMethod Method for building neighbourhood graph.
	* @param neighbourhoodField Field to use when building neighbourhood graph.
	* @param value Threshold value for neighbourhood graph.
	*/
	void Project(const Matrix& dissMatrix, const QString& neighbourhoodMethod, const QString& neighbourhoodField, double value);

	/**
	* Perform the C-ISOMAP algorithm.
	*
	* @param data Dissimilarity matrix to be embedded.
	* @param neighbourhoodMethod Method for building neighbourhood graph.
	* @param neighbourhoodField Field to use when building neighbourhood graph.
	* @param value Threshold value for neighbourhood graph.
	*/
	void ProjectSingleManifold(const Matrix& dissMatrix, const QString& neighbourhoodMethod, const QString& neighbourhoodField, double value);

	const Matrix& GetProjectedData() const { return m_pcoa.GetProjectedData(); }
	const QVector<double>& GetEigenvalues() const { return m_pcoa.GetEigenvalues(); }
	const QVector<double>& GetVariance() const { return m_pcoa.GetVariance(); }
	const QVector<double>& GetSumVariance() const { return m_pcoa.GetSumVariance(); }

	/** Number of connected components in neighbourhood graph. */
	uint GetNumConnectedComponents() const { return m_numManifolds; }

	/** Get neighbourhood graph. */
	Matrix GetNeighbourhoodGraph() { return m_neighbourhoodGraph; }

private:
	/**
	* Build the neighbourhood graph.
	*
	* @param dissMatrix Matrix containing dissimilarity between all pairs of points.
	* @param neighbourhoodMethod Method for building neighbourhood graph.
	* @param neighbourhoodField Field to use when building neighbourhood graph.
	* @param value Threshold value for neighbourhood graph.
	*
	* @return Neighbourhood graph.
	*/
	Matrix NeighbourhoodGraph(const Matrix& dissMatrix, const QString& neighbourhoodMethod, const QString& neighbourhoodField, double value);

	/** Calculate neighbourhood graph using a fixed number of nearest neighbours. */
	Matrix NearestNeighbourNG(const Matrix& dissMatrix, uint k);

	/** Calculate neighbourhood graph using a fixed epsilon radius. */
	Matrix SampleDissimilarityNG(const Matrix& dissMatrix, double radius);

	/** Calculate neighbout graph using a fixed epsilon radius applied to associated sample metadata. */
	Matrix QuantitativeFactorNG(const Matrix& dissMatrix, const QString& field, double radius);

	/**
	* Finds the shortest distance between points in a single connected neighbourhood
	* graph.  That is, the neighbourhood graph is explicitly adjusted so that there
	* is only a single connected component and the distance between points is
	* calculated using this graph.
	*
	* @param dissMatrix Matrix containing dissimilarity between all pairs of points.
	* @param neighbourhoodMethod Method for building neighbourhood graph.
	* @param neighbourhoodField Field to use when building neighbourhood graph.
	* @param value Threshold value for neighbourhood graph.
	*
	* @return Neighbourhood graph.
	*/
	Matrix ShortestConnectedGraph(const Matrix& dissMatrix, const QString& neighbourhoodMethod, const QString& neighbourhoodField, double value);

	/**
	* Determine the connected components in the given shortest path distance matrix.
	*
	* @param dissMatrix Matrix giving shortest dissimilarity between points in neighbourhood graph.
	* @param components Vector indicating what component each point belongs to.
	* @param labels Vector indicating the different component labels.
								(i.e. first point of each component)
	*/
	uint ConnectedComponents(const Matrix& graph, QVector<int>& component, QVector<int>& label);

	/**
	* Use Dijkstra's algorithm to calculate the shortest path between all pairs of
	* points.  
	*
	* @param dissMatrix Matrix containing dissimilarity between all pairs of points.
	*
	* @return Shortest distance between all pairs of points.
	*/
	Matrix ShortestPathDijkstra(const Matrix& dissMatrix);

private:
	/** Metadata associated with samples. */
	MetadataPtr m_metadata;

	/** Number of manifolds (i.e. number of parts object is divided into). */
	uint m_numManifolds;

	/** Maximum distance between two points on a manifold is normalize to be unit length. */
	QVector<float> m_normalize;

	/** Results of PCoA analysis on a geodesic dissimilarity matrix. */
	PCoA m_pcoa;

	/** Matrix indicating the neighbourhood graph (connected samples have a value < INF). */
	Matrix m_neighbourhoodGraph;
};

#endif