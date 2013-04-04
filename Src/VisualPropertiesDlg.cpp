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

#include "VisualPropertiesDlg.hpp"

#include "Metadata.hpp"
#include "Legends.hpp"
#include "ColorMaps.hpp"

#include "Log.hpp"

VisualPropertiesDlg::VisualPropertiesDlg(MetadataPtr metadata, LegendsPtr legend, ColorMapsPtr colorMaps, QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags), m_colorMaps(colorMaps)
{
	ui.setupUi(this);

	QObject::connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(SetProperties()));
	QObject::connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
	QObject::connect(ui.chkFixedShape, SIGNAL(stateChanged(int)), this, SLOT(ChangedFixedShapeState(int)));

	// initialize field comboboxes 
	QStringList fields = metadata->GetFields();
	foreach(const QString& field, fields)
	{
		ui.cboColorField->addItem(field);
		ui.cboShapeField->addItem(field);
		ui.cboSizeField->addItem(field);
	}

	// initialize color map combobox
	m_colorMaps->PopulateComboBox(ui.cboColorMap);
	if(legend->GetColorMapName() == "<custom>")
		ui.cboColorMap->addItem("<custom>");

	// set current values
	ui.cboColorField->setCurrentIndex(ui.cboColorField->findText(legend->GetColorField()));
	ui.cboColorMap->setCurrentIndex(ui.cboColorMap->findText(legend->GetColorMapName()));

	ui.cboShapeField->setCurrentIndex(ui.cboShapeField->findText(legend->GetShapeField()));
	ui.chkFixedShape->setChecked(legend->IsFixedShape());
	ChangedFixedShapeState(legend->IsFixedShape());

	if(legend->GetFixedShape() == "<custom>")
		ui.cboShape->addItem("<custom>");
	else
		ui.cboShape->removeItem(ui.cboShape->findText("<custom>"));
	ui.cboShape->setCurrentIndex(ui.cboShape->findText(legend->GetFixedShape()));

	ui.cboSizeField->setCurrentIndex(ui.cboSizeField->findText(legend->GetSizeField()));
	ui.spinSizeMin->setValue(legend->GetMinSize());
	ui.spinSizeMax->setValue(legend->GetMaxSize());
	ui.chkLogScale->setChecked(legend->IsLogScale());
}

VisualPropertiesDlg::~VisualPropertiesDlg()
{

}

void VisualPropertiesDlg::SetProperties()
{
	m_colorField = ui.cboColorField->currentText();
	m_colorMap = ui.cboColorMap->currentText();

	m_shapeField = ui.cboShapeField->currentText();
	m_bFixedShape = ui.chkFixedShape->isChecked();
	m_fixedShape = ui.cboShape->currentText();

	m_sizeField = ui.cboSizeField->currentText();
	m_minSize = ui.spinSizeMin->value();
	m_maxSize = ui.spinSizeMax->value();
	m_bLogScale = ui.chkLogScale->isChecked();

	accept();
}

void VisualPropertiesDlg::ChangedFixedShapeState(int state)
{
	ui.cboShape->setEnabled(state);
	ui.cboShapeField->setEnabled(!state);
}

