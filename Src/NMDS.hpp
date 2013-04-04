//=======================================================================
// Author: Donovan Parks
//
// Copyright 2011 Donovan Parks
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
//
// This is a wrapper around NMDS.cpp which was written by 
// Peter Kleiweg 2000 - 2005, and released under GPL v2.0.
//
//=======================================================================

#ifndef NMDS_HPP
#define NMDS_HPP

#include "stdafx.h"

class NMDS
{
public:
	NMDS() {}
	~NMDS() {}

	void Project(const Matrix& dissMatrix, int maxIter);

	const Matrix& GetProjectedData() const { return m_projectedData; }
	float GetCorrelation() const { return m_correlation; }

private:


private:
	Matrix m_projectedData;

	float m_correlation;
};

#endif