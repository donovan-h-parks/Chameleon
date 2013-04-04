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

#include "DiversityMeasureDlg.hpp"

#include "Log.hpp"

#include "SplitSystem.hpp"
#include "GUI.h"

DiversityMeasureDlg::DiversityMeasureDlg(SplitSystemPtr splitSystem, QWidget *parent, Qt::WFlags flags)
	: QDockWidget(parent, flags), m_splitSystem(splitSystem)
{
	ui.setupUi(this);

	QObject::connect(ui.btnRun,  SIGNAL(clicked()), this, SLOT(Execute()));
	QObject::connect(ui.cboMeasureType, SIGNAL(currentIndexChanged(int)), this, SLOT(MeasureTypeChanged(int)));

	MeasureTypeChanged(0);

	updateGeometry();
}

DiversityMeasureDlg::~DiversityMeasureDlg()
{

}

void DiversityMeasureDlg::Execute()
{
	emit Run();

	if(isFloating())
		setVisible(false);
}

void DiversityMeasureDlg::MeasureTypeChanged(int index)
{
	QStringList splitsToConsider;
	if(m_splitSystem->GetSamples()->GetSequences()->IsOutgroup())	
	{
		if(index== UniSplit::UNWEIGHTED)
		{
			splitsToConsider.append("Common split set");
			splitsToConsider.append("Complete lineage"); 
			splitsToConsider.append("All splits");
		}
		else if(index == UniSplit::WEIGHTED)
		{
			splitsToConsider.append("All splits"); 
		}
		else if(index == UniSplit::WEIGHTED_NORMALIZED)
		{
			splitsToConsider.append("Common split set");
			splitsToConsider.append("Complete lineage"); 
			splitsToConsider.append("All splits");
			splitsToConsider.append("UniFrac semimetric");
		}
	}
	else
	{
		if(index == UniSplit::UNWEIGHTED)
		{
			splitsToConsider.append("<no suitable measures>");
		}
		else if(index == UniSplit::WEIGHTED)
		{
			splitsToConsider.append("All splits"); 
		}
		else if(index == UniSplit::WEIGHTED_NORMALIZED)
		{
			splitsToConsider.append("Common split set");
			splitsToConsider.append("All splits");
		}
	}

	ui.cboMeasure->clear();
	ui.cboMeasure->addItems(splitsToConsider);
}

UniSplit::MEASURE_TYPE DiversityMeasureDlg::GetMeasureType() const
{
	return MeasureType(ui.cboMeasureType->currentText());
}

UniSplit::SPLITS_TO_CONSIDER DiversityMeasureDlg::GetSplitsToConsider() const
{
	return SplitsToConsider(ui.cboMeasure->currentText());
}

UniSplit::MEASURE_TYPE DiversityMeasureDlg::MeasureType(const QString& measureType) const
{
	if(measureType == "Unweighted")
		return UniSplit::UNWEIGHTED;
	else if(measureType == "Weighted, unnormalized")
		return UniSplit::WEIGHTED;
	else if(measureType == "Weighted, normalized")
		return UniSplit::WEIGHTED_NORMALIZED;

	Log::Inst().Error("Unrecognized measure type string.");
	return UniSplit::UNWEIGHTED;
}

UniSplit::SPLITS_TO_CONSIDER DiversityMeasureDlg::SplitsToConsider(const QString& measureType) const
{
	if(measureType == "Common split set")
		return UniSplit::COMMON_SPLIT_SET;
	else if(measureType == "Complete lineage")
		return UniSplit::COMPLETE_LINEAGE;
	else if(measureType == "All splits")
		return UniSplit::ALL_SPLITS;
	else if(measureType == "UniFrac semimetric")
		return UniSplit::NORMALIZED_WEIGHTED_UNIFRAC;
	else if(measureType == "<no suitable measures>")
		return UniSplit::NO_SPLITS;

	Log::Inst().Error("Unrecognized split set string.");
	return UniSplit::NO_SPLITS;
}


bool DiversityMeasureDlg::GetNormalized() const
{
	if(GetMeasureType() == UniSplit::WEIGHTED_NORMALIZED)
		return true;

	return false;
}

bool DiversityMeasureDlg::GetWeighted() const
{
	if(GetMeasureType() == UniSplit::UNWEIGHTED)
		return false;

	return true;
}
