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

#include "SeqMetadata.hpp"

#include "Log.hpp"
#include "ColorMaps.hpp"

SeqMetadata::SeqMetadata(ColorMapsPtr colorMaps)
	: m_colorMaps(colorMaps), m_colorMapName("Ware (categorical - 9)"), 
		m_otherPercentage(5.0), m_otherColor(Qt::black), m_missingDataColor(Qt::black) 
{

}

bool SeqMetadata::Load(const QString& filename)
{
	Log::Inst().Debug("SeqMetadata::Load()");

	// Open sample file.
	QFile file(filename);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		Log::Inst().Warning("Unable to open sequence metadata file: " + filename);
		return false;
	}

	// Parse sample file.
	QTextStream textStream(&file);	

	// Read header line
	QString headerLine = textStream.readLine();
	QStringList headers = headerLine.split('\t');

	// Parse each row
	uint processedDataRows = 0;
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

		QString seqName = rowData.at(0);
		for(int i = 0; i < rowData.size(); ++i)
		{
			m_metadata[headers.at(i)][seqName] = rowData.at(i);
		}

		processedDataRows++;
	}

	// determine datatype for each field
	QStringList fields = m_metadata.keys();
	for(int i = 0; i < fields.size(); ++i)
	{
		QList<QString> values = m_metadata[fields.at(i)].values();
		
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

	return true;
}

QString SeqMetadata::GetMetadataValue(const QString& seqName) 
{ 
	Log::Inst().Debug("SeqMetadata::GetMetadataValue(const QString& seqName)");

	if(!m_metadata.value(m_field).contains(seqName))
		Log::Inst().Write("No metadata specified for sequence '" + seqName + "'.");

	return m_metadata.value(m_field).value(seqName); 
}

QColor SeqMetadata::GetMetadataColor(const QString& seqName)
{
	Log::Inst().Debug("SeqMetadata::GetMetadataColor(const QString& seqName)");

	QString value = GetMetadataValue(seqName);
	if(m_colorMap.contains(value))
		return m_colorMap[value];

	return Qt::black;
}

void SeqMetadata::SetField(const QString& field)
{
	Log::Inst().Debug("SeqMetadata::SetField(const QString& field)");

	if(m_colorMapName == "<custom>")
	{
		// custom map will not be valid for new field, so set to default map
		m_colorMapName = "Ware (categorical - 9)";
	}

	m_field = field;
	SetColorMap(m_colorMapName);
}

void SeqMetadata::SetOtherPercentage(double percentage)
{
	Log::Inst().Debug("SeqMetadata::SetOtherPercentage(double percentage)");

	m_otherPercentage = percentage;
	SetColorMap(m_colorMapName);
}	

void SeqMetadata::SetColorMap(const QString& colorMapName) 
{
	Log::Inst().Debug("SeqMetadata::SetColorMap(const QString& colorMapName)");

	if(m_field == "")
		return;

	m_colorMapName = colorMapName;

	// find unique sequences for current field
	m_percentages.clear();
	QSet<QString> uniqueKeys;
	uint numSeqs = 0;
	uint missingCategory = 0;
	foreach(const QString& key, m_metadata[m_field])
	{
		if(m_percentages.contains(key))
			m_percentages[key] = m_percentages.value(key) + 1.0;
		else
			m_percentages[key] = 1.0;

		if(key != "" || key != "X")
			uniqueKeys.insert(key);

		numSeqs++;
	}

	// get percentages for each unique key
	foreach(const QString& key, m_percentages.keys())
	{
		m_percentages[key] = m_percentages.value(key)*100.0 / numSeqs;
		if(m_percentages.value(key)*100.0 < m_otherPercentage)
			uniqueKeys.remove(key);
	}

	QwtLinearColorMapPtr colorMap;
	QwtInterval colorMapInterval;
	DATA_TYPE dataType = m_dataType.value(m_field);
	if(m_colorMapName != "<custom>")
	{
		// setup color map
		QList<QString> uniqueKeysList = uniqueKeys.toList();
		colorMap = m_colorMaps->GetColorMap(colorMapName); 
		if(dataType == CATEGORICAL_DATA)
		{
			qSort(uniqueKeysList.begin(), uniqueKeysList.end(), caseInsensitiveLessThan);

			colorMapInterval.setMinValue(0);

			if(colorMap->colorStops().size() > uniqueKeysList.size())
				colorMapInterval.setMaxValue(colorMap->colorStops().size()-1);
			else
				colorMapInterval.setMaxValue(uniqueKeysList.size()-1);
		}
		else
		{
			qSort(uniqueKeysList.begin(), uniqueKeysList.end(), numericStrLessThan);

			double minValue = uniqueKeysList.at(0).toDouble();
			double maxValue = FindMaximumOfSortedValue(uniqueKeysList);

			colorMapInterval.setMinValue(minValue);
			colorMapInterval.setMaxValue(maxValue);
		}

		m_colorMap.clear();
	}

	// create color map
	uint index = 0;
	foreach(const QString& key, m_percentages.keys())
	{
		QColor color;
		if(key == "" || key == "X")	
		{
			color = m_missingDataColor; // missing data
			m_colorMap[key] = color;
		}
		else if(m_percentages[key] < m_otherPercentage)
		{
			color = m_otherColor;
			m_colorMap[key] = color;
		}
		else if(dataType == CATEGORICAL_DATA)
		{
			if(m_colorMapName != "<custom>")
			{
				color = colorMap->color(colorMapInterval, index);
				index++;		
				m_colorMap[key] = color;
			}
			else
			{
				if(!m_colorMap.contains(key))
					m_colorMap[key] = Qt::black;
			}
		}
		else
		{
			if(m_colorMapName != "<custom>")
			{
				color = colorMap->color(colorMapInterval, key.toDouble());
				m_colorMap[key] = color;
			}
			else
			{
				if(!m_colorMap.contains(key))
					m_colorMap[key] = Qt::black;
			}
		}		
	}

	emit ColorMapChanged(m_colorMap, m_percentages, dataType == NUMERICAL_DATA);
}

double SeqMetadata::FindMaximumOfSortedValue(const QList<QString>& values)
{
	// this function assumes the values are already sorted with
	// unknown values placed at the end
	for(int i = values.size()-1; i >= 0; --i)
	{
		if(values.at(i) != "X" && values.at(i) != "")
			return values.at(i).toDouble();
	}

	// all values are unknown
	return 0;
}

void SeqMetadata::SetColorMap(const QMap<QString, QColor>& colorMap) 
{ 
	Log::Inst().Debug("SeqMetadata::SetColorMap(const QMap<QString, QColor>& colorMap)");

	m_colorMapName = "<custom>"; 
	m_colorMap = colorMap; 
}