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

#ifndef _SEQUENCES_HPP_
#define _SEQUENCES_HPP_

#include "stdafx.h"

/**
 * @class Sequences.
 * @brief Information about sequences.
 */
class Sequences
{
public:
	/** Constructor. */
	Sequences(Samples* samples);

	/** Destructor. */
	virtual ~Sequences() {}

	/** Get number of sequences in original split system. */
	uint GetNumSequences() const { return m_seqNameToId.size(); }

	/** Get number of active sequences. */
	uint GetNumActiveSequences(bool bWeighted) const;

	/** Get sequence id associated with a given sequence name. */
	bool GetSequenceId(const QString& sequenceName, uint& sequenceId) const;

	/** Get sequence name associated with a given sequence id. */
	bool GetSequenceName(uint sequenceId, QString& sequenceName) const;
	
	/** Set association between sequence names and ids. */
	void SetSequenceNameToIdMapping(QHash< QString, uint > seqNameToId) { m_seqNameToId = seqNameToId; }

	/** Get abundance of sequence in each sample. */
	bool GetSequenceAbundanceInSamples(uint sequenceId, QVector<uint>& sampleData) const;
	
	/** Get relative proportion of sequences in specified sample. */
	float GetRelativeProportionOfSeqs(uint sequenceId, uint sampleId) const;

	/** Get number of sequences of a given type in the specified sample. */
	uint GetNumSequences(uint sequenceId, uint sampleId) const;

	/** Set number of sequences in a given sample. */
	void SetNumSequencesInSample(uint sampleId, uint numSequences);

	/** Get number of sequences in a given sample. */
	uint GetNumSequencesInSample(uint sampleId, bool bWeighted = true) const;

	/** Get active adundancy matrix which indicates number of reads assigned to each unique sequence for each environment. */
	QVector< QVector<uint> > GetAbundancyMatrix() {	return m_abundancyMatrix; }

	/** Set adundancy matrix which indicates number of reads assigned to each unique sequence for each environment. */
	void SetAbundancyMatrix(const QVector< QVector<uint> >& abundancyMatrix) { m_abundancyMatrix = abundancyMatrix; }

	/** Set association between sequence ids and sample ids. */
	void SetSeqIdToSampleIdsMapping(QMultiHash< uint, uint > seqIdToSampleIds) { m_seqIdToSampleIds = seqIdToSampleIds; }

	/** Get sample id(s) associated with a given sequence id. */
	QList<uint> GetSampleIdsFromSeqId(uint seqId) const;

	/** 
	 * @brief Get number of sequences from each sample. 
	 * @param bWeighted Indicates if abundance weights should be used.
	 * @return Hash table indicating number of reads (bWeighted = true) or unique sequences (bWeighted = false).
	 */
	QHash<QString, uint> GetSequenceCounts(bool bWeighted) const;

	/** Check if there are outgroup sequences. */
	bool IsOutgroup() const { return m_outgroupSeqNames.size() > 0; }

	/** Get number of outgroup sequences. */
	uint GetNumberOutgroupSeq() const {  return m_outgroupSeqNames.size(); } 

	/** Set outgroup sequences. */
	void SetOutgroupSequences(const QStringList& outgroupNames) { m_outgroupSeqNames = outgroupNames; }

	/** Add outgroup sequences. */
	void AddOutgroupSequence(const QString& outgroupName) { m_outgroupSeqNames.push_back(outgroupName); }

	/** Check if a sequence is from the outgroup. */
	bool IsOutgroupSequence(const QString& label) { return m_outgroupSeqNames.contains(label); }
	
	/** Get list of outgroup sequencs. */
	QStringList GetOutgroupSequences() { return m_outgroupSeqNames; }

	/** Set active state of all sequences. */
	void SetActiveStateOfSeqs(bool state);

	/** Add sequence to active set. */
	void SetSequenceToActive(uint id) { m_activeSeqs.setBit(id); }

protected:
	Samples* m_samples;

	/** Indicating number of each unique sequence found in each sample. */
	QVector< QVector<uint> > m_abundancyMatrix;

	/** Map sequence name to sequence id. */
	QHash<QString, uint> m_seqNameToId;

	/** Maps a sequence id to sample ids. */
	QMultiHash<uint, uint> m_seqIdToSampleIds;

	/** Stores all sequences within a sample. */
	QHash<uint, QList<uint> > m_seqsInSample;

	/** Outgroup sequences. */
	QStringList m_outgroupSeqNames;

	/** Flags indicating if a sequence is in the active set. */
	QBitArray m_activeSeqs;
};

#endif

