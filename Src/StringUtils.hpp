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

#ifndef _STRING_UTILS_
#define _STRING_UTILS_

#include "stdafx.h"

class StringUtils
{
public:
	StringUtils() {}
	~StringUtils() {}

	/**
	 * @brief Write map to file. 
	 * @param outputFile File to write map to.
	 * @param map Map to write to file.
	 */
	static void WriteMap(const QString& filename, const QHash<QString, uint>& map)
	{
		QFile file(filename);
		if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			Log::Inst().Warning("Unable to create file: " + filename);
			return;
		}

		QTextStream textStream(&file);
		textStream.setRealNumberPrecision(6);

		QHashIterator<QString, uint> iter(map);
		while(iter.hasNext())
		{
			iter.next();
			textStream << iter.key() << ": " << iter.value() << endl;
		}

		file.close();
	}

	/**
	 * @brief Write matrix to file. 
	 * @param outputFile File to write matrix to.
	 * @param matrix Matrix to write to file.
	 * @param entryNames Name of rows/columns.
	 */
	static void WriteMatrix(const QString& filename, const Matrix& matrix, const QStringList& entryNames)
	{
		QFile file(filename);
		if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			Log::Inst().Warning("Unable to create file: " + filename);
			return;
		}

		QTextStream textStream(&file);
		textStream.setRealNumberPrecision(6);

		// write out distance matrix between all communities (taking care to ignore the "outgroup" community)
		textStream << matrix.size() << endl;

		for(int i = 0; i < matrix.size(); ++i)
		{
			QString entryName = entryNames.at(i);
			entryName = entryName.leftJustified(10, ' ', true);
			textStream << entryName << " ";
			for(int j = 0; j < matrix.at(i).size(); ++j)
			{
				textStream << matrix.at(i).at(j) << '\t';
			}

			textStream << endl;
		}

		file.close();
	}
};

#endif