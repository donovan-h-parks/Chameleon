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

#include "Sample.hpp"
#include "Log.hpp"

SampleData::SampleData(): m_id(0), m_bVisible(true), m_shape(QwtSymbol::Ellipse), m_bGuaranteedVisible(false), m_size(10)
{

}

SampleData::SampleData(const QString& name, uint id): m_name(name), m_id(id), m_bVisible(true), m_bGuaranteedVisible(false), m_shape(QwtSymbol::Ellipse), m_size(10)
{

}


Sample::Sample(): d(new SampleData)
{
	
}

Sample::Sample(const QString& name, uint id): d(new SampleData)
{
	SetName(name);
	SetId(id);
}
