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

#ifndef ORDINATION_ANALYSIS_DLG_HPP
#define ORDINATION_ANALYSIS_DLG_HPP

#include "ui_OrdinationAnalysisDialog.h"

#include "stdafx.h"

class OrdinationAnalysisDlg : public QDockWidget
{
	Q_OBJECT

public:
	OrdinationAnalysisDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~OrdinationAnalysisDlg();

	void SetMetadata(MetadataPtr metadata);

	QString GetEmbeddingMethod() const { return ui.cboClusteringMethod->currentText(); }
	QString GetNeighbourhoodMethod() const { return ui.cboNeighbourhoodMethod->currentText(); }
	QString GetNeighbourhoodField() const { return ui.cboNeighbourhoodField->currentText(); }
	double GetNeighbourhoodValue() const { return ui.spinNeighborhoodValue->value(); }
	int GetNumberOfIter() const { return ui.spinMaxIter->value(); }

signals:
	void Run();

private slots:
	void Execute();

	void MethodChanged();
	void NeighbourhoodMethodChanged();

private:
	Ui::OrdinationAnalysisDlg ui;
};

#endif 
