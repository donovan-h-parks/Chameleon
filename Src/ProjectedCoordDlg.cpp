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

#include "ProjectedCoordDlg.hpp"

#include "Log.hpp"


ProjectedCoordDlg::ProjectedCoordDlg(QWidget *parent, Qt::WFlags flags)
	: QDockWidget(parent, flags)
{
	ui.setupUi(this);

	QObject::connect(ui.btnSave,  SIGNAL(clicked()), this, SLOT(Save()));

	ui.tableEmbeddedDimensions->verticalHeader()->show();
	ui.tableEmbeddedDimensions->horizontalHeader()->show();

	updateGeometry();
}

void ProjectedCoordDlg::Save()
{
	QString filename = QFileDialog::getSaveFileName(this, "Save table", "", "Tab seperated values file (*.tsv);;Comma seperated values file (*.csv)");
	if(filename.isEmpty())
		return;

	// determine seperator type
	QString extension = filename.mid(filename.lastIndexOf(".")+1);
	extension = extension.toLower();
	QChar seperator = '\t';
	if(extension == "csv")
		seperator = ',';

	// write data to file
	QFile file(filename);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		Log::Inst().Warning("Unable to create file: " + filename);
		return;
	}

	QTextStream textStream(&file);
	textStream.setRealNumberPrecision(6);
	
	// write out row labels
	QTableWidget* table = ui.tableEmbeddedDimensions;
	textStream << seperator;
	for(int i = 0; i < table->rowCount(); ++i)
			textStream << table->verticalHeaderItem(i)->text() << seperator;
	textStream << endl;

	for(int i = 0; i < table->rowCount(); ++i)
	{	
		textStream << table->horizontalHeaderItem(i)->text() << seperator;
		for(int j = 0; j < table->columnCount(); ++j)
		{
			QTableWidgetItem* item = table->item(i, j);
			textStream << item->text() << seperator;
		}

		textStream << endl;
	}	

	file.close();
}

void ProjectedCoordDlg::PopulateTable(const Matrix& matrix, const QStringList& rowHeaders)
{
	QTableWidget* table = ui.tableEmbeddedDimensions;

	if(matrix.size() == 0)
	{
		table->clear();
		return;
	}

	table->setRowCount(matrix.size());
	table->setColumnCount(matrix.at(0).size());
	
	// set row headers
	table->setVerticalHeaderLabels(rowHeaders);

	// set column headers
	QStringList numbers;
	for(int i = 0; i < matrix.size(); ++i)
		numbers << QString("%1").arg(i);
	table->setHorizontalHeaderLabels(numbers);

	// set value of each cell
	for(int i = 0; i < matrix.size(); ++i)
	{	
		for(int j = 0; j < matrix.at(i).size(); ++j)
		{
			QTableWidgetItem* item = new QTableWidgetItem(tr("%1").arg(matrix.at(i).at(j)));
			item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			table->setItem(i, j, item);
		}
	}	

	table->resizeColumnsToContents();
}