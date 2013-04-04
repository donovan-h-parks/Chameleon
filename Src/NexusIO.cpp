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

#include "Log.hpp"
#include "NexusIO.hpp"
#include "NewickIO.hpp"
#include "SplitSystem.hpp"

#include "Tree.hpp"
#include "VisualNode.hpp"

bool NexusIO::Read(SplitSystem *const splitSystem, const QString& filename, bool bImplicitlyRooted)
{
	QString nexusFile = filename;
	nexusFile.replace('\\', '/');

	QFile file(nexusFile);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		Log::Inst().Warning("Unable to open file: " + filename);
		return false;
	}

	// Read entire input stream
	// Note: Assumes TAXA block comes before the SPLITS block
	QTextStream textStream(&file);
	bool bReadTaxaBlock = false;
	while(!textStream.atEnd())
  {
		QString line = textStream.readLine();
		if(line[0] != 'B')
			continue;

		if(line.contains("BEGIN Taxa", Qt::CaseInsensitive))
		{
			ReadTaxaBlock(textStream);
			bReadTaxaBlock = true;
		}
		else if(line.contains("BEGIN Trees", Qt::CaseInsensitive))
		{
			if(!ReadTreesBlock(splitSystem, textStream, bImplicitlyRooted))
				return false;

			break;
		}
		else if(line.contains("BEGIN Splits", Qt::CaseInsensitive))
		{
			if(!bReadTaxaBlock)
			{
				Log::Inst().Warning("Unable to parse file. TAXA block is expected before SPLITS block.");
				return false;
			}

			if(!ReadSplitsBlock(splitSystem, textStream))
				return false;

			break;
		}
	}

	file.close();

	return true;
}

bool NexusIO::ReadTaxaBlock(QTextStream& textStream)
{
	uint seqId = 1;
	QString line = "";
	while(!line.contains("END; [Taxa]", Qt::CaseInsensitive))
	{
		line = textStream.readLine();

		if(line[0] == '[')
		{			
			int openingQuote = line.indexOf('\'');
			int closingQuote = line.lastIndexOf('\'');
			QString seqName = line.mid(openingQuote + 1, closingQuote - openingQuote - 1);

			// map sequence names to ids
			m_seqIdToName[seqId] = seqName;

			seqId++;
		}
	}

	return true;
}

bool NexusIO::ReadTreesBlock(SplitSystem *const splitSystem, QTextStream& textStream, bool bImplicitlyRooted)
{
	// get line containing Newick tree
	QString line = "";
	while(!line.contains("[1] tree"))
	{
		line = textStream.readLine();
	}

	QString newickTree = line.mid(line.indexOf('('));

	Tree<VisualNode> tree;
	NewickIO newickIO;
	return newickIO.ParseNewickString(tree, splitSystem, newickTree, bImplicitlyRooted);
}

bool NexusIO::ReadSplitsBlock(SplitSystem *const splitSystem, QTextStream& textStream)
{	
	// determine number of splits
	QString line = "";
	while(!line.contains("nsplits="))
	{
		line = textStream.readLine();
	}

	uint indexOfSplitsCount = line.lastIndexOf('=');
	uint numSplits = line.mid(indexOfSplitsCount+1, line.indexOf(';') - indexOfSplitsCount -1).toInt();

	// get to start of splits
	while(!line.contains("MATRIX"))
	{
		line = textStream.readLine();
	}

	// Sum of all sequences ids. Sequences ids go from 0 to one minus the number of sequences.
	uint numSeqs = splitSystem->GetSamples()->GetSequences()->GetNumSequences();
	uint sumSeqsIds = numSeqs*(numSeqs-1)*0.5;

	// determine all splits
	QList<Split> tempSplits;
	bool bError = false;
	#pragma omp parallel private(tempSplits)
	{
		#pragma omp for schedule(static) nowait
		for(int splitId = 0; splitId < (int)numSplits; ++splitId)
		{
			QString splitLine;
			#pragma omp critical
			{
				splitLine = textStream.readLine();
			}

			QStringList rowData = splitLine.split('\t');
			double weight = rowData[1].toDouble();

			// bit array indicates the id of sequences on the left (1) and right (0) of the split
			QString idStr = "";
			QBitArray split(splitSystem->GetSamples()->GetSequences()->GetNumSequences()); 
			QString bipartitionStr = rowData[2].mid(2, rowData[2].size()-3);	// grab just the section contains the sequence ids
			QStringList ids = bipartitionStr.split(' ');

			uint outgroupSeqOnLeft = 0;
			uint numSeqOnLeft = 0;
			uint uniqueSeqId = 0;
			for(int i = 0; i < ids.size(); ++i)
			{
				uint seqId;
				QString seqName = m_seqIdToName.value(ids.at(i).toInt());
				splitSystem->GetSamples()->GetSequences()->GetSequenceId(seqName, seqId);
				if(seqId != UINT_MAX)
				{
					split.setBit(seqId);
					numSeqOnLeft++;
					uniqueSeqId += seqId;
				}
				else
				{
					if(splitSystem->GetSamples()->GetSequences()->IsOutgroupSequence(seqName))
					{
						outgroupSeqOnLeft++;
					}
					else
					{
						Log::Inst().Error("Sequence '" + seqName + "' is contained in the phylogeny file, but not the sample file.");
						bError = true;
					}
				}			
			}

			// If the split is trivial (i.e., one of the bipartitions contains only a single leaf) it is critical
			// that its id be equal to the  id of the leaf sequence. This is use to reduce the time to process
			// trivial splits. If there was only a single sequence processed for this split than uniqueSeqId is
			// already set to the correct value, otherwise uniqueSeqId is set to the sum of all sequence ids minus
			// the leaf sequence
			if(numSeqOnLeft == splitSystem->GetSamples()->GetSequences()->GetNumSequences() - 1)
			{				
				uniqueSeqId = sumSeqsIds - uniqueSeqId;
			}

			bool bOutgroupSeqOnLeft = (outgroupSeqOnLeft > 0);
			bool bOutgroupSeqOnRight = (splitSystem->GetSamples()->GetSequences()->GetNumberOutgroupSeq() != outgroupSeqOnLeft);
			tempSplits.push_back(Split(uniqueSeqId, weight, split, bOutgroupSeqOnLeft, bOutgroupSeqOnRight, numSeqOnLeft, split.size()-numSeqOnLeft));
		}

		// tabulate results from all threads.
		#pragma omp critical
		{
			splitSystem->AddSplits(tempSplits);
		}
	}

	return !bError;
}
