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

#ifndef _QTABLE_WIDGET_NUMERIC_ITEM_HPP_
#define _QTABLE_WIDGET_NUMERIC_ITEM_HPP_

#include "stdafx.h"

/**
 * @brief Provides numerical sorting of a table column.
 */
class QTableWidgetNumericItem: public QTableWidgetItem
{
public:
	QTableWidgetNumericItem(const QString & text): QTableWidgetItem(text) {}

	bool operator<(const QTableWidgetItem &other) const
	{
		return this->text().toDouble() < other.text().toDouble();
  }

};

#endif