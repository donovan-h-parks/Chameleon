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

#ifndef _MATRIX_SYSTEM_HPP_
#define _MATRIX_SYSTEM_HPP_

#include "stdafx.h"

#include "System.hpp"

/**
 * @class Matrix system.
 * @brief Holds a matrix along with associate sample metadata information.
 */
class MatrixSystem: public System
{
public:
	/** Constructor. */
	MatrixSystem() {}

	/** Destructor. */
	~MatrixSystem() {}

	/** 
	 * @brief Populate matrix system.
	 * @param matrixFile File containing matrix data.
	 * @param metadataFile File containing sample metadata.
	 * @return True if data loaded successfully, otherwise false.
	 */
	bool LoadData(const QString& matrixFile, const QString& metadataFile);

	/** Get matrix data. */
	Matrix GetMatrix() const { return m_matrix; }

	bool CreateFromTree(VisualNode* root) { return false; }	// can't build a tree from a Matrix system

	static void ReadFromFile(const QString& filename, Matrix& matrix);

private:
	/** Data matrix. */
	Matrix m_matrix;
};

#endif

