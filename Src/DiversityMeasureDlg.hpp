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

#ifndef DIVERISYT_MEASURE_DLG_HPP
#define DIVERISYT_MEASURE_DLG_HPP

#include "ui_DiversityMeasureDialog.h"

#include "stdafx.h"

#include "UniSplit.hpp"

class DiversityMeasureDlg : public QDockWidget
{
	Q_OBJECT

public:
	DiversityMeasureDlg(SplitSystemPtr splitSystem, QWidget *parent = 0, Qt::WFlags flags = 0);
	~DiversityMeasureDlg();

	/** Type of UniSplit measure to perform. */
	UniSplit::MEASURE_TYPE GetMeasureType() const;

	/** Splits to consider in UniSplit analysis. */
	UniSplit::SPLITS_TO_CONSIDER GetSplitsToConsider() const;

	/** Flag indicating if a normalized analysis is to be performed. */
	bool GetNormalized() const;

	/** Flag indicating if a weighted analysis is to be performed. */
	bool GetWeighted() const;

	/** Indicate underlying spilt system has changed. */
	void SplitSystemChanged() { MeasureTypeChanged(0); }

signals:
	void Run();

private slots:
	/** Type of measure being perform has changed. */
	void MeasureTypeChanged(int index);

	void Execute();

private:
	/** Determine type of UniSplit measure to perform. */
	UniSplit::MEASURE_TYPE MeasureType(const QString& measureType) const;

	/** Determine splits to consider in UniSplit analysis. */
	UniSplit::SPLITS_TO_CONSIDER SplitsToConsider(const QString& splitsToConsider) const;

private:
	Ui::DiversityMeasureDlg ui;

	SplitSystemPtr m_splitSystem;
};

#endif 
