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

#ifndef PROJECTED_COORD_DLG_HPP
#define PROJECTED_COORD_DLG_HPP

#include "ui_ProjectedCoordDialog.h"

#include "stdafx.h"

class ProjectedCoordDlg : public QDockWidget
{
	Q_OBJECT

public:
	ProjectedCoordDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ProjectedCoordDlg() {}

	/** Populate table with projection data. */
	void PopulateTable(const Matrix& matrix, const QStringList& rowHeaders);

private slots:
	/** Save table to file. */
	void Save();

private:
	Ui::ProjectedCoordDlg ui;
};

#endif 
