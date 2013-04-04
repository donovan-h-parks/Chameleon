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

#include "Samples.hpp"

#include "Metadata.hpp"
#include "Sequences.hpp"
#include "Sample.hpp"

#include "Log.hpp"

Samples::Samples(): m_metadata(new Metadata(this)), m_sequences(new Sequences(this)), m_bActiveSetChanged(false)
{

}

bool Samples::LoadFromSampleFile(const QString& filename)
{
	Log::Inst().Debug("Samples::LoadFromSample(const QString& filename)");

	// Open sample file.
	QFile file(filename);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		Log::Inst().Warning("Unable to open sample file: " + filename);
		return false;
	}

	// Determine number of unique sequences and samples
	QList<QString> seqs;
	QList<QString> samples;
	QList<uint> count;
	QTextStream textStream(&file);
	uint lineCount = 0;
	while(!textStream.atEnd()) 
	{
		lineCount++;

		QString data = textStream.readLine();

		QStringList rowData = data.split('\t');
		if(rowData.size() < 2)
		{
			Log::Inst().Error("Missing sequence or sample id on line " + QString(lineCount));
			return false;
		}

		seqs.append(rowData[0]);
		samples.append(rowData[1]);

		if(rowData.size() >= 3)
			count.append(rowData.at(2).toUInt());
		else
			count.append(1);
	}

	int numSamples = samples.toSet().size();
	int numUniqueSeqs = seqs.toSet().size();
	
	// Parse sample file.
	QHash<QString, uint> seqNameToId;
	seqNameToId.reserve(numUniqueSeqs);

	m_sampleNameToSample.reserve(numSamples);

	QMultiHash< uint, uint > seqIdToSampleIds;
	seqIdToSampleIds.reserve(numUniqueSeqs);

	QStringList outgroupSeqNames;
	QList<uint> outgroupSeqIds;

	QVector< QVector<uint> > abundancyMatrix;
	abundancyMatrix.resize(numUniqueSeqs);
	for(int i = 0; i < abundancyMatrix.size(); ++i)
		abundancyMatrix[i].resize(numSamples);
		
	uint sampleId = 0;
	uint sequenceId = 0;
	for(int i = 0; i < seqs.count(); ++i)
	{ 
		QString sequenceName = seqs.at(i);
		QString sampleName = samples.at(i);
		uint numSequences = count.at(i);

		// check if sequence is an outgroup
		if(QString::compare(sampleName, "outgroup", Qt::CaseInsensitive) == 0)
		{
			outgroupSeqNames.push_back(sequenceName);
			continue;
		}

		// add sequence to split system
		uint curSequenceId;
		QHash<QString, uint>::const_iterator seqNameIt = seqNameToId.find(sequenceName);
		if(seqNameIt != seqNameToId.end())
		{
			curSequenceId = seqNameIt.value();
		}
		else
		{
			curSequenceId = sequenceId;
			seqNameToId.insert(sequenceName, sequenceId);
			sequenceId++;
		}
		
		// add sample to split system
		uint curSampleId;
		QHash<QString, Sample>::iterator sampleNameIt = m_sampleNameToSample.find(sampleName);
		if(sampleNameIt != m_sampleNameToSample.end())
		{
			curSampleId = sampleNameIt.value().GetId();
			sampleNameIt.value().SetNumSequences(sampleNameIt.value().GetNumSequences() + numSequences);
		}
		else
		{
			curSampleId = sampleId;

			Sample sample(sampleName, sampleId);
			sample.SetNumSequences(numSequences);

			m_samples.append(sample);		
			m_sampleNameToSample.insert(sampleName, sample);

			sampleId++;
		}

		seqIdToSampleIds.insert(curSequenceId, curSampleId);

		// add data to abundance matrix	
		if(abundancyMatrix.at(curSequenceId).at(curSampleId) == 0)
		{
			abundancyMatrix[curSequenceId][curSampleId] = numSequences;
		}
		else
		{
			Log::Inst().Error("Sample file contains multiple lines with sequence '" +  sequenceName + "' assigned to sample '" + sampleName + "'.");
			return false;
		}
	}			
	
	m_sequences->SetSequenceNameToIdMapping(seqNameToId);
	m_sequences->SetSeqIdToSampleIdsMapping(seqIdToSampleIds);
	m_sequences->SetOutgroupSequences(outgroupSeqNames);
	m_sequences->SetAbundancyMatrix(abundancyMatrix);
	m_sequences->SetActiveStateOfSeqs(true);

	Log::Inst().Write("Sample file contains " + QString("%1").arg(m_sequences->GetNumSequences()) + " unique sequences from " + QString("%1").arg(GetNumSamples()) + " samples.");

	file.close();

	// set all samples as active
	for(uint i = 0; i < GetNumSamples(); ++i)
		m_activeSampleIds.insert(i);

	return true;
}

void Samples::SetSampleByName(const QStringList& sampleNames)
{
	Log::Inst().Debug("Samples::SetSampleByName(const QStringList& sampleNames)");

	for(int i = 0; i < sampleNames.size(); ++i)
	{
		Sample sample(sampleNames.at(i), i);
		sample.SetNumSequences(0);

		m_samples.append(sample);		
		m_sampleNameToSample.insert(sampleNames.at(i), sample);
	}

	// set all samples as active
	for(uint i = 0; i < GetNumSamples(); ++i)
		m_activeSampleIds.insert(i);
}

bool Samples::GetSample(const QString& name, Sample& sample) const 
{ 
	if(m_sampleNameToSample.contains(name))
	{
		sample = m_sampleNameToSample.value(name);
		return true;
	}

	return false;
}

void Samples::GetDeepCopyOfSamples(QList<Sample>& samples)
{
	for(int i = 0; i < m_samples.size(); ++i)
	{
		samples.push_back(m_samples.at(i));
		samples[i].DeepCopy();
	}
}

void Samples::ToggleSelectedSamples(const QSet<uint>& sampleIds)
{
	foreach(uint sampleId, sampleIds)
	{
		QSet<uint>::iterator it = m_selectedSampleIds.find(sampleId);
		if(it != m_selectedSampleIds.end())
			m_selectedSampleIds.erase(it);
		else
			m_selectedSampleIds.insert(sampleId);
	}
}

void Samples::SetSampleToInactive(uint id) 
{ 
	m_activeSampleIds.remove(id); 
	
	m_bActiveSetChanged = true;
	emit ActiveSamplesChanged(); 

	m_metadata->MarkActiveSamplesInTable();
}

void Samples::SetSamplesToInactive(const QSet<uint>& ids) 
{ 
	m_activeSampleIds.subtract(ids); 
	
	m_bActiveSetChanged = true;
	emit ActiveSamplesChanged(); 

	m_metadata->MarkActiveSamplesInTable();
}

void Samples::SetSampleToActive(uint id) 
{
	m_activeSampleIds.insert(id); 
	
	m_bActiveSetChanged = true;
	emit ActiveSamplesChanged(); 

	m_metadata->MarkActiveSamplesInTable();
}

void Samples::SetAllSamplesToActive()
{	
	for(uint i = 0; i < GetNumSamples(); ++i)
		m_activeSampleIds.insert(i);

	m_bActiveSetChanged = true;
	emit ActiveSamplesChanged(); 

	m_metadata->MarkActiveSamplesInTable();
}

void Samples::SetAllSamplesToInactive()
{
	m_activeSampleIds.clear();

	m_bActiveSetChanged = true;
	emit ActiveSamplesChanged(); 

	m_metadata->MarkActiveSamplesInTable();
}

void Samples::SetSelectedSamplesToActive()
{
	m_activeSampleIds.clear();

	foreach(uint sampleId, m_selectedSampleIds)
		m_activeSampleIds.insert(sampleId);

	emit ActiveSamplesChanged();

	m_metadata->MarkActiveSamplesInTable();
}

void Samples::FilterActiveSamples(const QString& addRemove, const QString& field, const QString& relation, const QString& value)
{
	// get sample ids satisfying filtering constraints
	Metadata::DATA_TYPE dataType = m_metadata->GetDatatype(field);

	QList<uint> filteredSamples;
	for(uint sampleId = 0; sampleId < GetNumSamples(); sampleId++)
	{
		const QString& sampleValue = m_metadata->GetValue(field, sampleId);

		if(dataType == Metadata::NUMERICAL_DATA)
		{
			if(relation == ">")
			{
				if(sampleValue.toDouble() > value.toDouble())
					filteredSamples.append(sampleId);
			}
			else if(relation == "=")
			{
				if(sampleValue.toDouble() == value.toDouble())
					filteredSamples.append(sampleId);
			}
			else if(relation == "<")
			{
				if(sampleValue.toDouble() < value.toDouble())
					filteredSamples.append(sampleId);
			}
		}
		else
		{
			uint relationship = QString::compare(sampleValue, value, Qt::CaseInsensitive);
			if(relation == ">")
			{
				if(relationship > 0)
					filteredSamples.append(sampleId);
			}
			else if(relation == "=")
			{
				if(relationship == 0)
					filteredSamples.append(sampleId);
			}
			else if(relation == "<")
			{
				if(relationship < 0)
					filteredSamples.append(sampleId);
			}
		}
	}

	foreach(uint sampleId, filteredSamples)
	{
		if(addRemove == "Add")
			m_activeSampleIds.insert(sampleId);
		else
			m_activeSampleIds.remove(sampleId);
	}

	m_bActiveSetChanged = true;
	emit ActiveSamplesChanged();

	m_metadata->MarkActiveSamplesInTable();
}

QStringList Samples::GetSampleMetadataFromSeq(const QString& field, const QString& seqName)
{
	QStringList values;

	uint seqId;
	bool bFoundSeqId = m_sequences->GetSequenceId(seqName, seqId);
	if(!bFoundSeqId)
		values.append("<missing data>");
	else
	{
		QList<uint> sampleIds = m_sequences->GetSampleIdsFromSeqId(seqId);
		foreach(uint sampleId, sampleIds)
			values.append(m_metadata->GetValue(field, sampleId));
	}

	return values;
}

QStringList Samples::GetActiveSampleNames() const
{
	QStringList names;
	foreach(uint id, m_activeSampleIds)
		names.append(m_samples.at(id).GetName());

	return names;
}
