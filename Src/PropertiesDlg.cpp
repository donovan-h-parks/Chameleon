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

#include "PropertiesDlg.hpp"

#include "Log.hpp"

#include "Properties.hpp"


PropertiesDlg::PropertiesDlg(QWidget *parent, Qt::WFlags flags)
	: QDockWidget(parent, flags)
{
	ui.setupUi(this);

	ui.btnBackgroundColor->setStandardColors();

	SetValues();

	QObject::connect(ui.btnOK,  SIGNAL(clicked()), this, SLOT(Execute()));

	QObject::connect(ui.btnDefaultValues, SIGNAL(clicked()), this, SLOT(SetDefaultValues()));

	updateGeometry();
}

void PropertiesDlg::Execute()
{
	Properties::Inst().SetSelectionTransparency(ui.spinSelectionTransparency->value());
	Properties::Inst().SetBackgroundColor(ui.btnBackgroundColor->currentColor());

	emit BackgroundColorChanged(ui.btnBackgroundColor->currentColor());

	if(isFloating())
		setVisible(false);
}

void PropertiesDlg::SetDefaultValues()
{
	Properties::Inst().RestoreDefaultValues();

	SetValues();
}

void PropertiesDlg::SetValues()
{
	ui.spinSelectionTransparency->setValue((1.0 - Properties::Inst().GetSelectionOpacity() / 255.0) * 100);
	ui.btnBackgroundColor->setCurrentColor(Properties::Inst().GetBackgroundColor());
}
