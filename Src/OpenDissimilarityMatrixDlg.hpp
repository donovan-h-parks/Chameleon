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

#ifndef OPEN_DISSIMILARITY_MATRIX_HPP
#define OPEN_DISSIMILARITY_MATRIX_HPP

#include "ui_OpenDissimilarityMatrixDialog.h"

#include "stdafx.h"

class OpenDissimilarityMatrixDlg : public QDialog
{
	Q_OBJECT

public:
	OpenDissimilarityMatrixDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~OpenDissimilarityMatrixDlg();

	QString GetDissimilarityMatrixFile() { return m_dissimilarityMatrixFile; }
	QString GetMetadataFile() { return m_metadataFile; }

private slots:
	void OpenDissimilarityMatrix();
	void OpenMetadataFile();

private:
	Ui::OpenDissimilarityMatrixDlg ui;

	QString m_dissimilarityMatrixFile;
	QString m_metadataFile;
};

#endif 
