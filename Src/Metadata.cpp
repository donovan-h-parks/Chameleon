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

#include "Metadata.hpp"

#include "Log.hpp"
#include "Samples.hpp"
#include "QTableWidgetNumericItem.hpp"

Metadata::Metadata(Samples* samples): m_samples(samples), m_table(NULL)
{

}

bool Metadata::Load(const QString& filename)
{
	Log::Inst().Debug("Metadata::Load()");

	if(filename.isEmpty())
	{
		SetDefaultMetadata();
	}
	else
	{
		// Open sample file.
		QFile file(filename);
		if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			Log::Inst().Warning("Unable to open metadata file: " + filename);
			return false;
		}

		// Parse sample file.
		QTextStream textStream(&file);	

		// Read header line
		QString headerLine = textStream.readLine();
		if(headerLine[0] == '#')
			headerLine = headerLine.mid(1);

		QStringList headers = headerLine.split('\t');

		// Set primary key to 'SampleID'
		int sampleIdIndex = headers.indexOf("SampleID");
		if(sampleIdIndex == -1)
			sampleIdIndex = headers.indexOf("Sample ID");
		if(sampleIdIndex == -1)
				sampleIdIndex = headers.indexOf("SampleId");
		if(sampleIdIndex == -1)
				sampleIdIndex = headers.indexOf("Sample Id");
		if(sampleIdIndex == -1)
				sampleIdIndex = headers.indexOf("Sample id");
		if(sampleIdIndex == -1)
		{
				Log::Inst().Error("Metadata file requires a column labelled 'Sample Id'.");
				return false;
		}
		headers[sampleIdIndex] = "SampleID";

		// Reserve memory for each field
		for(int i = 0; i < headers.size(); ++i)
			m_metadata[headers.at(i)].resize(m_samples->GetNumSamples());

		// Parse each row
		uint processedDataRows = 0;
		QVector<QString> missingSamples;
		while(!textStream.atEnd())
		{
			QString row = textStream.readLine();
			if(row[0] == '#' || row.isEmpty())
				continue;	// skip comments

			row = row.trimmed();	// remove trailing whitespaces

			QStringList rowData = row.split('\t');
			if(rowData.size() != headers.size())
			{
				Log::Inst().Error("Metadata file contains " + QString("%1").arg(headers.size()) + " column headers, but there is a row with " + QString("%1").arg(rowData.size()) + " values.");
				return false;
			}

			QString sampleName = rowData.at(0);
			Sample sample;
			bool bSampleInTree = m_samples->GetSample(sampleName, sample);
			if(!bSampleInTree)
			{
				missingSamples.append(sampleName);
				continue;
			}

			uint sampleId = sample.GetId();
			for(int i = 0; i < rowData.size(); ++i)
				m_metadata[headers.at(i)][sampleId] = rowData.at(i);

			processedDataRows++;
		}

		if(processedDataRows != m_samples->GetNumSamples())
			Log::Inst().Warning("Metadata file contains " + QString("%1").arg(processedDataRows) + " data rows, but there are " + QString("%1").arg(m_samples->GetNumSamples()) + " specified samples.");

		if(missingSamples.size() != 0)
		{						
			QString missingSampleStr;
			foreach(const QString& sampleName, missingSamples)
				missingSampleStr += sampleName + ",";
			missingSampleStr = missingSampleStr.left(missingSampleStr.size()-1);	// remove last comma

			Log::Inst().Warning("The following samples are present in the metadata file, but not your sample or matrix file: " + missingSampleStr);
		}

		// determine datatype for each field
		QStringList fields = m_metadata.keys();
		for(int i = 0; i < fields.size(); ++i)
		{
			QVector<QString> values = m_metadata[fields.at(i)];
			
			bool isDecimalNumber = true;
			for(int j = 0; j < values.size(); ++j)
			{
				if(values.at(j) == "X" || values.at(j) == "")
					continue;	// skip missing data

				bool temp;
				values.at(j).toDouble(&temp);
				isDecimalNumber = (isDecimalNumber && temp); 
			}

			if(isDecimalNumber)
				m_dataType[fields.at(i)] = NUMERICAL_DATA;
			else
				m_dataType[fields.at(i)] = CATEGORICAL_DATA;
		}

		file.close();
	}

	return true;
}

void Metadata::SetDefaultMetadata()
{
	QVector<QString> sampleNames(m_samples->GetNumSamples());
	for(uint i = 0; i < m_samples->GetNumSamples(); ++i)
		sampleNames[i] = m_samples->GetSample(i).GetName();

	m_metadata["SampleID"] = sampleNames;
	m_dataType["SampleID"] = CATEGORICAL_DATA;
}

void Metadata::PopulateTable(QTableWidget* table)
{
	m_table = table;
	m_table->clear();

	QObject::connect(m_table,  SIGNAL(clicked(const QModelIndex&)), this, SLOT(CellClicked(const QModelIndex&)));

	// display all fields in alphabetical order, except make sure the SampleID field is first 
	QList<QString> keys = m_metadata.keys();
	int sampleIdIndex = keys.indexOf("SampleID");
	keys[sampleIdIndex] = keys.at(0);
	keys[0] = "SampleID";

	table->setColumnCount(keys.size());
	table->setHorizontalHeaderLabels(keys);

	table->setRowCount(m_samples->GetNumSamples());
	table->verticalHeader()->hide();

	// populate table
	for(int i = 0; i < keys.size(); ++i)
	{	
		DATA_TYPE dataType = GetDatatype(keys.at(i));
		QVector<QString> values = m_metadata.value(keys.at(i));

		for(int j = 0; j < values.size(); ++j)
		{
			// for numerical columns, this ensures sorting is done numerically as opposed to lexically
			QTableWidgetItem* item;
			if(dataType == NUMERICAL_DATA)
				item = new QTableWidgetNumericItem(values.at(j));
			else
				item = new QTableWidgetItem(values.at(j));

			// save the sample id for each row
			item->setData(Qt::UserRole, j);

			// set checkboxes for SampleID field
			if(i == 0)
			{
				item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
				item->setCheckState(Qt::Checked);
			}
			else
				item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

			table->setItem(j, i, item);
		}
	}	
}

void Metadata::CellClicked(const QModelIndex& index)
{
	int row = index.row();
	int col = index.column();

	bool bChecked = m_table->item(row,0)->checkState();
	QVariant d = m_table->item(row,0)->data(Qt::UserRole);
	uint sampleId = d.toInt();

	QSet<uint> sampleIds;
	sampleIds.insert(sampleId);
	m_samples->ToggleSelectedSamples(sampleIds);

	// add/remove sample from active set
	if(col == 0)
	{		
		if(bChecked)
			m_samples->SetSampleToActive(sampleId);
		else
			m_samples->SetSampleToInactive(sampleId);
	}
}

void Metadata::MarkActiveSamplesInTable()
{
	for(uint r = 0; r < m_samples->GetNumSamples(); ++r)
	{
		QVariant d = m_table->item(r,0)->data(Qt::UserRole);
		uint sampleId = d.toInt();

		if(m_samples->GetActiveSampleIds().contains(sampleId))
			m_table->item(r,0)->setCheckState(Qt::Checked);
		else
			m_table->item(r,0)->setCheckState(Qt::Unchecked);
	}
}


void Metadata::SetSelectedRows()
{
	m_table->clearSelection();
	for(uint r = 0; r < m_samples->GetNumSamples(); ++r)
	{
		QVariant d = m_table->item(r,0)->data(Qt::UserRole);
		uint sampleId = d.toInt();

		if(m_samples->GetSelectedSampleIds().contains(sampleId))
			m_table->selectRow(r);
	}	

	m_table->setFocus();
}

QStringList Metadata::GetQuantitativeFields() const
{
	QStringList quanFields;
	foreach(const QString& field, GetFields())
	{
		if(GetDatatype(field) == NUMERICAL_DATA)
			quanFields.append(field);
	}

	return quanFields;
}