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

#ifndef _NEXUS_IO_
#define _NEXUS_IO_

#include "stdafx.h"

/**
 * @brief Populate a split system from a Nexus file containing a TAXA and either a TREES or SPLITS blocks.
 */
class NexusIO
{
public:
	/** Constructor. */
	NexusIO() {}

	/** Destructor. */
	~NexusIO() {}

	/**
	* @brief Read a split network from a file.
	*
	* @param splitSystem Split system to populate from file.
	* @param filename The file path.
	* @param bImplicitlyRooted Flag indicating if the tree should be treated as implicitly rooted.
	* @return True if file parsed successfully, otherwise false.
	*/
	bool Read(SplitSystem *const splitSystem, const QString& filename, bool bImplicitlyRooted);

private:
	/**
	* @brief Read TAXA block.
	*
	* @param textStream Stream for reading Nexus input file.
	* @return True if block parsed successfully, otherwise false.
	*/
	bool ReadTaxaBlock(QTextStream& textStream);

	/**
	* @brief Read TREES block.
	*
	* @param splitSystem Split system to populate from file.
	* @param textStream Stream for reading Nexus input file.
	* @return True if block parsed successfully, otherwise false.
	*/
	bool ReadTreesBlock(SplitSystem *const splitSystem, QTextStream& textStream, bool bImplicitlyRooted);

	/**
	* @brief Read SPLITS block.
	*
	* @param splitSystem Split system to populate from file.
	* @param textStream Stream for reading Nexus input file.
	* @return True if block parsed successfully, otherwise false.
	*/
	bool ReadSplitsBlock(SplitSystem *const splitSystem, QTextStream& textStream);

private:
	/** Map sequence ids in Nexus file to sequence names. */
	QHash<uint, QString> m_seqIdToName;	
};


#endif


