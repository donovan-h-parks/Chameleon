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

#include "OpenPhylogenyDlg.hpp"

OpenPhylogenyDlg::OpenPhylogenyDlg(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	// event handlers
	QObject::connect(ui.btnOpenPhylogeny, SIGNAL(clicked()), this, SLOT(OpenPhylogenyFile()));
	QObject::connect(ui.btnOpenSampleFile, SIGNAL(clicked()), this, SLOT(OpenSampleFile()));
	QObject::connect(ui.btnOpenMetadataFile, SIGNAL(clicked()), this, SLOT(OpenMetadataFile()));
}

OpenPhylogenyDlg::~OpenPhylogenyDlg()
{

}

void OpenPhylogenyDlg::OpenPhylogenyFile()
{
	m_phylogenyFile = QFileDialog::getOpenFileName(this, "Open tree or network", "", 
																										"Phylogeny files (*.new *.nex *.nexus *.nxs *.tre *.tree);;"
																										"Newick tree (*.tre *.tree *.new);;"
																										"Nexus split network (*.nex *.nxs *.nexus)");

	QString extension = m_phylogenyFile.mid(m_phylogenyFile.lastIndexOf(".")+1);
	extension = extension.toLower();
	if(extension == "new" || extension == "tre" || extension == "tree")
	{
		ui.chkRooted->setEnabled(true);
	}
	else if(extension == "nxs" || extension == "nex" || extension == "nexus")
	{
		ui.chkRooted->setEnabled(false);
	}

	ui.txtPhylogenyFile->setText(m_phylogenyFile);
}

void OpenPhylogenyDlg::OpenSampleFile()
{
	m_sampleFile = QFileDialog::getOpenFileName(this, "Open sample file", "", "Sample file (*.tsv *.env *.txt);;All files (*.*)");
	ui.txtSampleFile->setText(m_sampleFile);
}

void OpenPhylogenyDlg::OpenMetadataFile()
{
	m_metadataFile = QFileDialog::getOpenFileName(this, "Open metadata file", "", "Metadata file (*.tsv *.dat *.txt);;All files (*.*)");
	ui.txtMetadataFile->setText(m_metadataFile);
}

