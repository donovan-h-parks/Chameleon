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

#ifndef _PCOA_HPP_
#define _PCOA_HPP_

#include "stdafx.h"

class PCoA
{
public:
	PCoA() {}
	~PCoA() {}

	void Project(const Matrix& distMatrix);

	const Matrix& GetProjectedData() const { return m_projectedData; }
	const QVector<double>& GetEigenvalues() const { return m_eigenValues; }
	const QVector<double>& GetVariance() const { return m_variance; }
	const QVector<double>& GetSumVariance() const { return m_sumVariance; }

	double GetVariance(uint principalComponent) const { return m_eigenValues.at(principalComponent) / m_sumEigenvalues; }
	const double GetSumEigenvalues() const { return m_sumEigenvalues; }

	int GetDataPts() const { return m_projectedData.size(); }

	int GetDimensionality() const
	{
		if(m_projectedData.size() == 0)
			return 0;

		return m_projectedData.at(0).size();
	}

	void WriteToFile(const QString& filename);

private:
	Matrix m_projectedData;
	QVector<double> m_eigenValues;
	QVector<double> m_variance;
	QVector<double> m_sumVariance;

	double m_sumEigenvalues;
};


///////////////////////////////////////////////////////////////////////////////
//
//	Computes eigenvalues and eigenvectors of a real, symmetric
//	matrix. 
//
//	A matrix can be decomposed as A = U*D*U', where the eigenvalue matrix D is
//	diagonal and the eigenvector matrix U is orthogonal. That is,
//	the diagonal values of D are the eigenvalues, and
//	U*U' = I, where I is the identity matrix.  The columns of U 
//	represent the eigenvectors in the sense that A*U = V*U.
//   
//	(Adapted from JAMA, a Java Matrix Library, developed by jointly 
//	by the Mathworks and NIST; see  http://math.nist.gov/javanumerics/jama).
//
//  Modified by: Donovan Parks, August 2007 (donovan.parks@gmail.com)
///////////////////////////////////////////////////////////////////////////////
class EigDecomp
{
public:
	// A - input matrix stored in row-major order
	// U - eigenvector matrix stored in row-major order
	// D - real-components of eigenvalues
	// E - imaginary-components of eigenvalues
	// rows - number of rows in matrix
	EigDecomp(double* A, double* U, double* D, double* E, int rows);

private:
	void tred2();
	void tql2();

	int m_rows;	// size of matrix

	// real and imaginary components of the eigenvalues
	double* m_D;  
	double* m_E;

	// eigenvectors (stored as a row-major single dimensional vector)
	double* m_U;
};

#endif
