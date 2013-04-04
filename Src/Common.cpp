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

#include "Common.hpp"

//--- Useful sorting functions ---
bool numericStrLessThan(const QString &s1, const QString &s2)
{
	if(s1 == "X" || s1 == "")
		return false;
	else if(s2 == "X" || s2 == "")
		return true;
	else
   return s1.toDouble() < s2.toDouble();
}

bool caseInsensitiveLessThan(const QString &s1, const QString &s2)
{
   return s1.toLower() < s2.toLower();
}

