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
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "LinearRegression.hpp"

bool LinearRegression::LeastSquaresEstimate(QList<double>& x, QList<double>& y, RESULTS& results)
{
	int numPts = x.size();
	if(numPts < 2)
		return false;

	double sumX = 0;
	double sumY = 0;
	double sumXY = 0;
	double sumX2 = 0;
	double sumY2 = 0;
	for(int i=0; i < numPts; ++i) 
	{
		sumX += x.at(i);
		sumY += y.at(i);
		sumXY	+= x.at(i) * y.at(i);
		sumX2	+= x.at(i) * x.at(i);
		sumY2	+= y.at(i) * y.at(i);
	}

	double SSxy = sumXY - (sumX*sumY) / numPts;
	double SSxx = sumX2 - (sumX*sumX) / numPts;
	double SSyy = sumY2 - (sumY*sumY) / numPts;

	results.slope = SSxy / SSxx;
	results.offset = (sumY - results.slope*sumX) / numPts;

	results.cod = (SSxy*SSxy) / (SSxx*SSyy);

	results.dof = numPts-2;

	double SSE = SSyy-results.slope*SSxy;
	results.sd = sqrt(SSE / results.dof);
	results.seos = results.sd / sqrt(SSxx);
	results.seoi = results.sd*sqrt((1/numPts) + ((sumX/numPts)*(sumX/numPts))/SSxx);
	
	results.tStat = results.slope / results.seos;

	results.nPts = numPts;

	return true;
}

/**
 * Calculate the error of a given best fit line.
 */
double LinearRegression::Error(int numPts, double sumX, double sumY, double sumXY, 
											double sumX2, double sumY2)
{
	double SSxx = sumX2 - (sumX*sumX) / numPts;
	double SSyy = sumY2 - (sumY*sumY) / numPts;
	double SSxy = sumXY - (sumX*sumY) / numPts;

	double slope = SSxy / SSxx;
	double offset = (sumY - slope*sumX) / numPts;

	return SSyy - slope*SSxy;
}
