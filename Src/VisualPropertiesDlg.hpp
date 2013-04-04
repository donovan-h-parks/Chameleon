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

#ifndef VISUAL_PROPERTIES_DLG_HPP
#define VISUAL_PROPERTIES_DLG_HPP

#include "ui_VisualPropertiesDialog.h"

#include "stdafx.h"

class Legend;

class VisualPropertiesDlg : public QDialog
{
	Q_OBJECT

public:
	VisualPropertiesDlg(MetadataPtr metadata, LegendsPtr legend, ColorMapsPtr colorMaps, QWidget *parent = 0, Qt::WFlags flags = 0);
	~VisualPropertiesDlg();

	QString GetColorField() const { return m_colorField; }
	QString GetColorMap() const { return m_colorMap; }

	QString GetShapeField() const { return m_shapeField; }
	bool IsFixedShape() const { return m_bFixedShape; }
	QString GetFixedShape() const { return m_fixedShape; }

	QString GetSizeField() const { return m_sizeField; }
	uint GetMinSize() const { return m_minSize; }
	uint GetMaxSize() const { return m_maxSize; }
	bool IsLogScale() const { return m_bLogScale; }

private slots:
	void SetProperties();
	void ChangedFixedShapeState(int state);

private:
	Ui::VisualPropertiesDlg ui;

	MetadataPtr m_metadata;
	ColorMapsPtr m_colorMaps;

	QString m_colorField;
	QString m_colorMap;

	QString m_shapeField;
	bool m_bFixedShape;
	QString m_fixedShape;

	QString m_sizeField;
	uint m_minSize;
	uint m_maxSize;
	bool m_bLogScale;
};

#endif 
