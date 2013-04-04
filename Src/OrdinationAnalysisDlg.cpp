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

#include "OrdinationAnalysisDlg.hpp"

#include "Metadata.hpp"

#include "Log.hpp"

OrdinationAnalysisDlg::OrdinationAnalysisDlg(QWidget *parent, Qt::WFlags flags)
	: QDockWidget(parent, flags)
{
	ui.setupUi(this);

	QObject::connect(ui.btnRun,  SIGNAL(clicked()), this, SLOT(Execute()));
	QObject::connect(ui.cboClusteringMethod, SIGNAL(currentIndexChanged(int)), this, SLOT(MethodChanged()));
	QObject::connect(ui.cboNeighbourhoodMethod, SIGNAL(currentIndexChanged(int)), this, SLOT(NeighbourhoodMethodChanged()));

	// set initial state of widgets
	MethodChanged();
	NeighbourhoodMethodChanged();

	// update layout of dialog
	updateGeometry();
	update();
}

OrdinationAnalysisDlg::~OrdinationAnalysisDlg()
{

}

void OrdinationAnalysisDlg::SetMetadata(MetadataPtr metadata)
{
	// get quantitative metadata fields
	ui.cboNeighbourhoodField->clear();
	ui.cboNeighbourhoodField->addItems(metadata->GetQuantitativeFields());
	ui.cboNeighbourhoodField->updateGeometry();
}

void OrdinationAnalysisDlg::Execute()
{
	emit Run();

	if(isFloating())
		setVisible(false);
}

void OrdinationAnalysisDlg::MethodChanged()
{
	if(ui.cboClusteringMethod->currentText() == "Principal coordinate analysis")
	{
		ui.lblNeighbourhoodMethod->setEnabled(false);
		ui.cboNeighbourhoodMethod->setEnabled(false);
		ui.lblNeighbourhoodField->setEnabled(false);
		ui.cboNeighbourhoodField->setEnabled(false);
		ui.lblNeighborhoodValue->setEnabled(false);
		ui.spinNeighborhoodValue->setEnabled(false);
		ui.lblIterations->setEnabled(false);
		ui.spinMaxIter->setEnabled(false);
	}
	else if(ui.cboClusteringMethod->currentText() == "Nonmetric MDS")
	{
		ui.lblNeighbourhoodMethod->setEnabled(false);
		ui.cboNeighbourhoodMethod->setEnabled(false);
		ui.lblNeighbourhoodField->setEnabled(false);
		ui.cboNeighbourhoodField->setEnabled(false);
		ui.lblNeighborhoodValue->setEnabled(false);
		ui.spinNeighborhoodValue->setEnabled(false);
		ui.lblIterations->setEnabled(true);
		ui.spinMaxIter->setEnabled(true);
	}
	else if(ui.cboClusteringMethod->currentText() == "Isomap" || ui.cboClusteringMethod->currentText() == "Contiguous isomap")
	{
		ui.lblNeighbourhoodMethod->setEnabled(true);
		ui.cboNeighbourhoodMethod->setEnabled(true);
		ui.lblNeighborhoodValue->setEnabled(true);
		ui.spinNeighborhoodValue->setEnabled(true);
		ui.lblIterations->setEnabled(false);
		ui.spinMaxIter->setEnabled(false);

		NeighbourhoodMethodChanged();
	}

}

void OrdinationAnalysisDlg::NeighbourhoodMethodChanged()
{
	if(ui.cboNeighbourhoodMethod->currentText() == "Fixed number of neighbours")
	{
		ui.lblNeighborhoodValue->setText("Neighbours:");
		ui.spinNeighborhoodValue->setDecimals(0);

		ui.lblNeighbourhoodField->setEnabled(false);
		ui.cboNeighbourhoodField->setEnabled(false);
	}
	else if(ui.cboNeighbourhoodMethod->currentText() == "Sample dissimilarity")
	{
		ui.lblNeighborhoodValue->setText("Neighbourhood radius:");
		ui.spinNeighborhoodValue->setDecimals(3);

		ui.lblNeighbourhoodField->setEnabled(false);
		ui.cboNeighbourhoodField->setEnabled(false);
	}
	else if(ui.cboNeighbourhoodMethod->currentText() == "Quantitative factor")
	{
		ui.lblNeighborhoodValue->setText("Neighbourhood radius:");
		ui.spinNeighborhoodValue->setDecimals(3);

		ui.lblNeighbourhoodField->setEnabled(true);
		ui.cboNeighbourhoodField->setEnabled(true);
	}

	updateGeometry();
}
