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

#include "Split.hpp"
#include "Log.hpp"

Split::Split(uint id, double weight, const QBitArray& split, bool bOutgroupSeqOnLeft, bool bOutgroupSeqOnRight, uint numSeqOnLeft, uint numSeqOnRight)
	: m_rightSeqCount(numSeqOnRight), m_leftSeqCount(numSeqOnLeft), m_bOutgroupSeqOnRight(bOutgroupSeqOnRight),
		m_bOutgroupSeqOnLeft(bOutgroupSeqOnLeft), m_split(split), m_frequency(1), m_weight(weight), m_id(id)
{

}

QVector<uint> Split::GetLeftSequenceIds() const
{
	QVector<uint> seqs(m_leftSeqCount);

	if(m_leftSeqCount == 1 && m_bOutgroupSeqOnRight)
	{
		// The id of a split is always set to the sequence id for trivial splits. This has been done
		// to permit trivial splits to be efficently processed using this check.
		seqs[0] = m_id;
		return seqs;
	}

	uint index = 0;
	for(int i = 0; i < m_split.size(); ++i)
	{
		if(m_split.testBit(i))
		{
			seqs[index] = i;
			index++;
		}
	}

	return seqs;
}

QVector<uint> Split::GetRightSequenceIds() const
{
	QVector<uint> seqs(m_rightSeqCount);

	if(m_rightSeqCount == 1 && m_bOutgroupSeqOnLeft)
	{
		// The id of a split is always set to the sequence id for trivial splits. This has been done
		// to permit trivial splits to be efficently processed using this check.
		seqs[0] = m_id;
		return seqs;
	}

	uint index = 0; 
	for(int i = 0; i < m_split.size(); ++i)
	{
		if(!m_split.testBit(i))
		{
			seqs[index] = i;
			index++;
		}
	}

	return seqs;
}

QVector<uint> Split::GetSequencesIdsInSmallestBipartition() const
{
	if(m_leftSeqCount < m_rightSeqCount)
		return GetLeftSequenceIds();

	return GetRightSequenceIds();
}

bool Split::IsTrivial() const
{
	// check if left or right side of split contains a single sequence
	return ((m_leftSeqCount == 1 && m_bOutgroupSeqOnRight)
							|| (m_rightSeqCount == 1 && m_bOutgroupSeqOnLeft));
}

void Split::Print()
{
	QString splitStr;
	splitStr = QString("%1").arg(m_weight, 12, 'g', 4) + ": ";

	for(int i = 0; i < m_split.size(); ++i)
	{
		if(m_split.testBit(i))
			splitStr += QString("%1").arg(i) + ", ";
	}
	splitStr = splitStr.left(splitStr.lastIndexOf(','));

	splitStr += " | ";

	for(int i = 0; i < m_split.size(); ++i)
	{
		if(!m_split.testBit(i))
			splitStr += QString("%1").arg(i) + ", ";
	}
	splitStr = splitStr.left(splitStr.lastIndexOf(','));

	Log::Inst().Write(splitStr);
}

int Split::GetSize() const
{
	return qMin(m_leftSeqCount, m_rightSeqCount);
}
