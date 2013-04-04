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

#ifndef _MATH_UTILS_
#define _MATH_UTILS_

#include "stdafx.h"

class MathUtils
{
public:
	/**
	 * @brief Randomly permute elements in a vector.
	 * @param vec Vector to permute.
	 */
	template <typename T>
	static void RandomShuffle(QVector<T>& vec)
	{
		std::random_shuffle(vec.begin( ), vec.end( ));

		/*
		for(int i = 0; i < vec.size(); ++i)
		{
			int j = rand() % vec.size();
			T temp = vec.at(i);
			vec[i] = vec.at(j);
			vec[j] = temp;
		}
		*/
	}
};

#endif