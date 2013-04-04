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

#include "Sequences.hpp"

#include "Samples.hpp"
#include "Log.hpp"

Sequences::Sequences(Samples* samples): m_samples(samples)
{

}

bool Sequences::GetSequenceId(const QString& sequenceName, uint& sequenceId) const
{ 
	sequenceId = m_seqNameToId.value(sequenceName, UINT_MAX);

	return (sequenceId != UINT_MAX);
}

bool Sequences::GetSequenceName(uint sequenceId, QString& sequenceName) const
{
	sequenceName = m_seqNameToId.key(sequenceId, "");

	return (!sequenceName.isEmpty());
}

QList<uint> Sequences::GetSampleIdsFromSeqId(uint seqId) const
{
	return m_seqIdToSampleIds.values(seqId);
}

bool Sequences::GetSequenceAbundanceInSamples(uint sequenceId, QVector<uint>& sampleData) const
{ 
	if(m_activeSeqs.testBit(sequenceId))
	{
		sampleData = m_abundancyMatrix[sequenceId];
		return true;
	}

	return false;
}

uint Sequences::GetNumActiveSequences(bool bWeighted) const 
{ 
	if(bWeighted)
	{
		QSet<uint> activeSampleIds = m_samples->GetActiveSampleIds();

		uint seqs = 0;
		foreach(uint sampleId, activeSampleIds)
				seqs += m_samples->GetSample(sampleId).GetNumSequences();

		return seqs;
	}

	return m_activeSeqs.count(true);
}

float Sequences::GetRelativeProportionOfSeqs(uint sequenceId, uint sampleId) const
{
	if(m_samples->GetActiveSampleIds().contains(sampleId))
	{
		if(m_activeSeqs.testBit(sequenceId))
			return float(m_abundancyMatrix[sequenceId][sampleId]) / m_samples->GetSample(sampleId).GetNumSequences();
	}

	return 0;
}

uint Sequences::GetNumSequences(uint sequenceId, uint sampleId) const
{
	if(m_samples->GetActiveSampleIds().contains(sampleId))
	{
		if(m_activeSeqs.testBit(sequenceId))
			return m_abundancyMatrix[sequenceId][sampleId];
	}

	return 0;
}

uint Sequences::GetNumSequencesInSample(uint sampleId, bool bWeighted) const
{ 
	if(m_samples->GetActiveSampleIds().contains(sampleId))
	{
		if(bWeighted)
			return m_samples->GetSample(sampleId).GetNumSequences(); 

		uint uniqueSeqInSample = 0;
		for(int seqId = 0; seqId < m_abundancyMatrix.size(); ++seqId)
		{
			if(m_activeSeqs.testBit(seqId) && m_abundancyMatrix.at(seqId).at(sampleId) > 0)
				uniqueSeqInSample++;
		}

		return uniqueSeqInSample;
	}

	return 0;
}

QHash<QString, uint> Sequences::GetSequenceCounts(bool bWeighted) const
{
	QHash<QString, uint> countMap;

	for(uint sampleId = 0; sampleId < m_samples->GetNumSamples(); ++sampleId)
		countMap.insert(m_samples->GetSample(sampleId).GetName(), GetNumSequencesInSample(sampleId, bWeighted));
	
	return countMap;
}

void Sequences::SetActiveStateOfSeqs(bool state) 
{ 
	uint numSeqs = GetNumSequences() + GetNumberOutgroupSeq();
	m_activeSeqs = QBitArray(numSeqs, state); 
}