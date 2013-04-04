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

#ifndef _COMMON_
#define _COMMON_

//--- Common Numeric Values ---------------------------------------------------

#define PI 3.14159265f
#define TWO_PI (2*PI)
#define PI_BY_2 (PI / 2.0f)
#define EPSILON 0.00000001f
#define DEG_TO_RAD (PI/180.0f)
#define RAD_TO_DEG (180.0f/PI)
#define TAN_30	0.5773502692f
#define COS_30	0.8660254038f
#define SIN_30	0.5f

//--- Useful flags ---

#define NOT_SET INT_MAX

//--- Useful sorting functions ---
bool numericStrLessThan(const QString &s1, const QString &s2);
bool caseInsensitiveLessThan(const QString &s1, const QString &s2);

#endif

