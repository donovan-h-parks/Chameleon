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

#include "MatrixSystem.hpp"

#include "Log.hpp"
#include "Samples.hpp"
#include "Metadata.hpp"

#include "StatsUtils.hpp"

bool MatrixSystem::LoadData(const QString& matrixFile, const QString& metadataFile)
{
	// parse matrix file
	QFile file(matrixFile);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		Log::Inst().Warning("Unable to open matrix file: " + matrixFile);
		return false;
	}

	QTextStream textStream(&file);	

	QStringList sampleIds;
	bool bHeader = true;
	bool bPhylipFormat = true;
	Matrix matrix;
	while(!textStream.atEnd())
	{
		QString dataRow = textStream.readLine();
		if(dataRow.isEmpty())
			break;

		QStringList dataItems;
		if(dataRow.count(' ') > dataRow.count('\t'))
			dataItems = dataRow.split(' ', QString::SkipEmptyParts);
		else
			dataItems = dataRow.split('\t', QString::SkipEmptyParts);
		if(bHeader)
		{
			bHeader = false;

			// check if this is a Phylip format distance matrix
			if(dataItems.size() == 1)
			{
				bool bNumber;
				int entries = dataItems.at(0).toInt(&bNumber);
				if(bNumber)
				{
					bPhylipFormat = true;
					continue;
				}
			}
		}

		sampleIds.push_back(dataItems.at(0));

		QVector<double> row;
		for(int i = 1; i < dataItems.size(); ++i)
			row.push_back(dataItems.at(i).toDouble());

		matrix.push_back(row);
	}

	// fill in upper triangular data since only the bottom triangular data may have been specified
	m_matrix.clear();
	m_matrix.resize(matrix.size());
	for(int r = 0; r < matrix.size(); ++r)
	{
		m_matrix[r].resize(matrix.size());
		m_matrix[r][r] = 0;

		for(int c = 0; c < r; ++c)
			m_matrix[r][c] = m_matrix[c][r] = matrix[r][c];
	}

	file.close();

	// create samples for matrix file
	GetSamples()->SetSampleByName(sampleIds);

	// parse metadata file
	if(!GetSamples()->GetMetadata()->Load(metadataFile))
	{
		Log::Inst().Error("Unable to parse metadata file.");
		return false;
	}

	return true;
}

void MatrixSystem::ReadFromFile(const QString& filename, Matrix& matrix)
{
	QFile file(filename);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		Log::Inst().Warning("Unable to open matrix file: " + filename);
		return;
	}

	QTextStream textStream(&file);	
	uint size = textStream.readLine().toInt();

	while(!textStream.atEnd())
	{
		QString dataRow = textStream.readLine();
		if(dataRow.isEmpty())
			break;

		// split up row header from actual dissimilarity data values
		QStringList dataItems = dataRow.split(' ', QString::SkipEmptyParts);
		if(dataItems.size() != 2)
		{
			Log::Inst().Warning("Format error in matrix file: " + filename);
			return;
		}

		dataItems = dataItems[1].split('\t', QString::SkipEmptyParts);

		QVector<double> row;
		for(int i = 0; i < dataItems.size(); ++i)
			row.push_back(dataItems.at(i).toDouble());

		matrix.push_back(row);
	}

	file.close();
}