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

#ifndef PROPERTIES_DLG_HPP
#define PROPERTIES_DLG_HPP

#include "ui_PropertiesDialog.h"

#include "stdafx.h"

#include "UniSplit.hpp"

class PropertiesDlg : public QDockWidget
{
	Q_OBJECT

public:
	PropertiesDlg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~PropertiesDlg() {}

signals:
	void BackgroundColorChanged(const QColor& color);

private slots:
	void Execute();
	void SetDefaultValues();

private:
	void SetValues();

private:
	Ui::PropertiesDlg ui;

};

#endif 
