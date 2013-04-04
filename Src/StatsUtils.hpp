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

#ifndef _STATS_UTILS_
#define _STATS_UTILS_

#include "stdafx.h"

class StatsUtils
{
public:
	enum TEST_TYPE { GreaterTest, LessTest };
	enum SORT { RowSort, RowAndColumnSort };

public:
	/**
	 * @brief Calculate significance value for Monte Carlo simulation.
	 * @param vec Vector to permute.
	 */
	static double MonteCarloSign(double origValue, const QList<double>& nullDist, TEST_TYPE testType)
	{
		uint tailCount = 0;
		for(int i = 0; i < nullDist.size(); ++i)
		{
			if(testType == GreaterTest && nullDist.at(i) >= origValue)
				tailCount++;
			else if(testType == LessTest && nullDist.at(i) <= origValue)
				tailCount++;
		}
		
		return ((double)tailCount) / nullDist.size(); 
	}

	static Matrix AlphabeticallyOrderMatrix(const Matrix& matrix, QStringList& labels, SORT sortType = RowAndColumnSort)
	{
		Matrix sortedMatrix(matrix.size());
		for(int i = 0; i < matrix.size(); ++i)
			sortedMatrix[i].resize(matrix.at(0).size());

		// sort labels alphabetically
		QMap<QString, uint> labelToIndexMap;
		for(int i = 0; i < labels.size(); ++i)
		{
			labelToIndexMap[labels.at(i)] = i;
		}

		qSort(labels);

		// set rows
		if(sortType == RowAndColumnSort || sortType == RowSort)
		{
			for(int i = 0; i < labels.size(); ++i)
			{
				uint index = labelToIndexMap.value(labels.at(i));
				sortedMatrix[i] = matrix.value(index);
			}
		}

		// set columns
		if(sortType == RowAndColumnSort)
		{
			for(int r = 0; r < sortedMatrix.size(); ++r)
			{
				for(int c = 0; c < sortedMatrix.at(r).size(); ++c)
				{
					uint indexR = labelToIndexMap.value(labels.at(r));
					uint indexC = labelToIndexMap.value(labels.at(c));
					sortedMatrix[r][c] = matrix.at(indexR).at(indexC);
				}
			}
		}

		return sortedMatrix;
	}

	static Matrix OrderMatrix(const Matrix& matrix, QStringList& curLabels, QStringList& targetLabels, SORT sortType = RowAndColumnSort)
	{
		Matrix sortedMatrix(matrix.size());
		for(int i = 0; i < sortedMatrix.size(); ++i)
			sortedMatrix.resize(matrix.at(0).size());

		// create map of current label positions
		QMap<QString, uint> labelToIndexMap;
		for(int i = 0; i < curLabels.size(); ++i)
		{
			labelToIndexMap[curLabels.at(i)] = i;
		}

		// set rows
		if(sortType == RowAndColumnSort || sortType == RowSort)
		{
			for(int i = 0; i < targetLabels.size(); ++i)
			{
				uint index = labelToIndexMap.value(targetLabels.at(i));
				sortedMatrix[i] = matrix.value(index);
			}
		}

		// set columns
		if(sortType == RowAndColumnSort)
		{
			for(int r = 0; r < targetLabels.size(); ++r)
			{
				for(int c = 0; c < targetLabels.size(); ++c)
				{
					uint indexR = labelToIndexMap.value(targetLabels.at(r));
					uint indexC = labelToIndexMap.value(targetLabels.at(c));
					sortedMatrix[r][c] = matrix.at(indexR).at(indexC);
				}
			}
		}

		return sortedMatrix;
	}
};

#endif