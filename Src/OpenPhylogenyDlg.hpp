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

#ifndef OPEN_PHYLOGENY_DLG_HPP
#define OPEN_PHYLOGENY_DLG_HPP

#include "ui_OpenPhylogenyDialog.h"

#include "stdafx.h"

class OpenPhylogenyDlg : public QDialog
{
	Q_OBJECT

public:
	OpenPhylogenyDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~OpenPhylogenyDlg();

	QString GetPhylogenyFile() { return m_phylogenyFile; }
	QString GetSampleFile() { return m_sampleFile; }
	QString GetMetadataFile() { return m_metadataFile; }
	bool IsImplicitlyRooted() { return ui.chkRooted->isChecked(); }
	bool IsShowPhylogeny() { return ui.chkShowPhylogeny->isChecked(); }

private slots:
	void OpenPhylogenyFile();
	void OpenSampleFile();
	void OpenMetadataFile();

private:
	Ui::OpenPhylogenyDlg ui;

	QString m_phylogenyFile;
	QString m_sampleFile;
	QString m_metadataFile;
};

#endif 
