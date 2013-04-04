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

#ifndef _SAMPLES_HPP_
#define _SAMPLES_HPP_

#include "stdafx.h"

#include "Sample.hpp"
#include "Metadata.hpp"
#include "Sequences.hpp"

/**
 * @class Samples.
 * @brief Provides access to a set of samples.
 */
class Samples: public QObject
{
	Q_OBJECT

public:
	/** Constructor. */
	Samples();

	/** Destructor. */
	~Samples() {}

	/** Load samples from an explicit sample file. */
	bool LoadFromSampleFile(const QString& filename);

	/** Create samples with the specified names. */
	void SetSampleByName(const QStringList& sampleNames);

	/** Get number of samples. */
	uint GetNumSamples() const { return m_samples.size(); }

	/** Get sample by id. */
	Sample GetSample(uint id) const { return m_samples.at(id); }

	/** Get sample by name. */
	bool GetSample(const QString& name, Sample& sample) const;

	/** Set samples. */
	void SetSamples(QList<Sample> samples) { m_samples = samples; }

	/** Get a deep-copy of all samples.*/
	void GetDeepCopyOfSamples(QList<Sample>& samples);

	/** Get list of selected sample ids. */
	QSet<uint> GetSelectedSampleIds() const { return m_selectedSampleIds; }

	/** Set all samples as unselected. */
	void ClearSelectedSamples() { m_selectedSampleIds.clear(); }

	/** Add sample to the selection set. */
	void SetSampleToSelected(uint sampleId) { m_selectedSampleIds.insert(sampleId); }

	/** Add samples to the selection set. */
	void SetSamplesToSelected(const QSet<uint>& sampleIds) { m_selectedSampleIds.unite(sampleIds); }

	/** Toggle selection state of specified samples. */
	void ToggleSelectedSamples(const QSet<uint>& sampleIds);	

	/** Get number of active samples. */
	uint GetNumActiveSamples() const { return m_activeSampleIds.size(); }

	/** Flag indicating if the active set has changed. */
	bool IsActiveSetChanged() const { return m_bActiveSetChanged; }

	/** Save current state of active set. */
	void SaveActiveSet() { m_bActiveSetChanged = false; }
	
	/** Get list of active sample ids. */
	QSet<uint> GetActiveSampleIds() const { return m_activeSampleIds; }

	/** Get list of all active samples. */
	QStringList GetActiveSampleNames() const;

	/** Add all samples to the active set. */
	void SetAllSamplesToActive();

	/** Remove all samples from the active set. */
	void SetAllSamplesToInactive();

	/** Add sample to active set. */
	void SetSampleToActive(uint id);

	/** Remove sample from active set. */
	void SetSampleToInactive(uint id);

	/** Remove samples from active set. */
	void SetSamplesToInactive(const QSet<uint>& ids) ;

	/** Set active set to the selected sample set. */
	void SetSelectedSamplesToActive();

	/** Filter the set of active samples. */
	void FilterActiveSamples(const QString& addRemove, const QString& field, const QString& relation, const QString& value);

	/** Get metadata for samples. */
	MetadataPtr GetMetadata() const { return m_metadata; }

	/** Get sequences within samples. */
	SequencesPtr GetSequences() const { return m_sequences; }

	/** Get metadata associated with the sample containing the specified sequence. */
	QStringList GetSampleMetadataFromSeq(const QString& field, const QString& seqName);

signals:
	void ActiveSamplesChanged();

private:
	QList<Sample> m_samples;

	QHash<QString, Sample> m_sampleNameToSample;

	QSet<uint> m_activeSampleIds;
	QSet<uint> m_selectedSampleIds;

	MetadataPtr m_metadata;
	SequencesPtr m_sequences;

	bool m_bActiveSetChanged;
};

#endif

