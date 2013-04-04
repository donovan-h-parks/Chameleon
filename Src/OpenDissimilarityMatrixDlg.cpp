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

#include "OpenDissimilarityMatrixDlg.hpp"

OpenDissimilarityMatrixDlg::OpenDissimilarityMatrixDlg(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	// event handlers
	QObject::connect(ui.btnOpenDissimilarityMatrix, SIGNAL(clicked()), this, SLOT(OpenDissimilarityMatrix()));
	QObject::connect(ui.btnOpenMetadataFile, SIGNAL(clicked()), this, SLOT(OpenMetadataFile()));
}

OpenDissimilarityMatrixDlg::~OpenDissimilarityMatrixDlg()
{

}

void OpenDissimilarityMatrixDlg::OpenDissimilarityMatrix()
{
	m_dissimilarityMatrixFile = QFileDialog::getOpenFileName(this, "Open dissimilarity matrix", "", 
																										"Dissimilarity matrix files (*.dst *.dis *.diss *.mat *.phy);;"
																										"All files (*.*);;");

	ui.txtDissimilarityMatrix->setText(m_dissimilarityMatrixFile);
}

void OpenDissimilarityMatrixDlg::OpenMetadataFile()
{
	m_metadataFile = QFileDialog::getOpenFileName(this, "Open metadata file", "", "Metadata file (*.tsv *.txt *.dat);;All files (*.*)");
	ui.txtMetadataFile->setText(m_metadataFile);
}

