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

#ifndef _SPLIT_
#define _SPLIT_

#include "stdafx.h"

/**
 * @class Split
 * @brief Holds data and functions for a single split.
 */
class Split
{
public:
	Split();

	/** Constructor. */
	Split(uint id, double weight, const QBitArray& split, bool bOutgroupSeqOnLeft, bool bOutgroupSeqOnRight, uint numSeqOnLeft, uint numSeqOnRight);

	/** Destructor. */
	~Split() {}

	/** Get unique id of split. */
	uint GetId() const { return m_id; }

	/** Get weight of split. */
	double GetWeight() const { return m_weight; }

	/** Set weight of split. */
	void SetWeight(double weight) { m_weight = weight; }

	/** Get frequency of split. */
	uint GetFrequency() const { return m_frequency; }

	/** Set frequency of split. */
	void SetFrequency(uint freq) { m_frequency = freq; }

	/** Get bit array indicating the IDs of sequences on the left (1) and right (0) of the split. */
	QBitArray GetSplitArray() const { return m_split; }

	/** Get sequences IDs on left of split. */
	QVector<uint> GetLeftSequenceIds() const;

	/** Get sequences IDs on right of split. */
	QVector<uint> GetRightSequenceIds() const;

	/** Get sequences IDs in smallest bipartition. */
	QVector<uint> GetSequencesIdsInSmallestBipartition() const;

	/** Get size of split (i.e., number of sequences in smallest bipartition). */
	int GetSize() const;

	/** Get number of sequences in left bipartition. */
	int GetSizeLeftBipartition() const { return m_leftSeqCount; }

	/** Get number of sequences in right bipartition. */
	int GetSizeRightBipartition() const { return m_rightSeqCount; }

	/** Determine if there are outgroup sequences on the left of the split. */
	bool IsOutgroupSeqOnLeft() const { return m_bOutgroupSeqOnLeft; }

	/** Determine if there are outgroup sequences on the right of the split. */
	bool IsOutgroupSeqOnRight() const { return m_bOutgroupSeqOnRight; }

	/** Check if split is trivial (i.e., has only a leaf node on one side). */
	bool IsTrivial() const;

	/** Print split data to log. */
	void Print();

private:
	/** Unique id of split. */
	uint m_id;

	/** Number of sequences in left bipartition. */
	uint m_leftSeqCount;

	/** Number of sequences in right bipartition. */
	uint m_rightSeqCount;

	/** Weight of split. */
	double m_weight;

	/** Number of times this split occurs in a split system. */
	uint m_frequency;

	/** Specifies the sequence ID of sequences on the left (1) and right (0) of a split. */
	QBitArray m_split;

	/** Flag indicating if there are outgroup sequences on left of split. */
	bool m_bOutgroupSeqOnLeft;
	
	/** Flag indicating if there are outgroup sequences on right of split. */
	bool m_bOutgroupSeqOnRight;
};

#endif

