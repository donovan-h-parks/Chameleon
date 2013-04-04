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

#ifndef _COLOUR_MAPS_HPP_
#define _COLOUR_MAPS_HPP_

#include "stdafx.h"

/**
 * @class ColorMaps.
 * @brief Provides access to colour maps.
 */
class ColorMaps
{
public:
	ColorMaps();

	bool Load();

	void PopulateComboBox(QComboBox* comboBox);

	QwtLinearColorMapPtr GetColorMap(const QString& name) const { return m_colorMaps.value(name); }
	QLinearGradient GetLinearGradient(const QString& name);

private:
	QMap<QString, QwtLinearColorMapPtr> m_colorMaps;

};

#endif