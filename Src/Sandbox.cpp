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

#include "SplitSystem.hpp"
#include "UniSplit.hpp"
#include "Log.hpp"
#include "NewickIO.hpp"
#include "StringUtils.hpp"

#include "Tree.hpp"
#include "VisualNode.hpp"

#include <iostream>

void ExecuteSandbox()
{
	QList<double> timingFileIO;
	QList<double> timingUniSplit;
	Matrix lowerBound, upperBound;
	for(uint i = 0; i < 1; ++i)	
	{

		std::clock_t start = std::clock();

		SplitSystemPtr splitSystem(new SplitSystem());
		splitSystem->LoadData("RandomTree.tre", "RandomTree.env", "", true);

		Log::Inst().Write(QString("Number splits: %1").arg(splitSystem->GetNumSplits()));
		Log::Inst().Write(QString("Number sequences: %1").arg(splitSystem->GetSplits().at(0).GetSplitArray().size()));

		std::clock_t end = std::clock();
		timingFileIO.append(( end - start ) / (double)CLOCKS_PER_SEC);		

		start = std::clock();
		UniSplitPtr uniSplit(new UniSplit(splitSystem));

		uniSplit->SetMeasureType(UniSplit::WEIGHTED_NORMALIZED);
		uniSplit->SetSplitsToConsider(UniSplit::COMMON_SPLIT_SET);
		uniSplit->Run();
		end = std::clock();

		timingUniSplit.append(( end - start ) / (double)CLOCKS_PER_SEC);
	}

	QFile file("UniSplitTiming.txt");
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		Log::Inst().Warning("Unable to create file: UniSplitTiming.txt");
		return;
	}

	qSort(timingFileIO.begin(), timingFileIO.end());
	Log::Inst().Write(QString("Timing File IO: %1").arg(timingFileIO.at(0)));

	qSort(timingUniSplit.begin(), timingUniSplit.end());
	Log::Inst().Write(QString("Timing UniSplit: %1").arg(timingUniSplit.at(0)));

	QTextStream textStream(&file);
	textStream.setRealNumberPrecision(12);
	textStream << timingFileIO.at(0) << '\t' << timingUniSplit.at(0) << '\t' << timingFileIO.at(0) + timingUniSplit.at(0);

	file.close();
}