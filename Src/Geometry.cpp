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
// along with Chameleon.  If not, see <http://www.gnu.org/licenses/>.
//=======================================================================

#include "stdafx.h"

#include "Geometry.hpp"

const double eps = 1e-6;

bool Geometry::CrossedQuadrantBoundaries(double quadrantAngle, double angle1, double angle2) 
{
	double dAngle1 = SignedAngularDifference(quadrantAngle, angle1);
	double dAngle2 = SignedAngularDifference(quadrantAngle, angle2);
	if(dAngle1*dAngle2 < 0 && abs(dAngle1) + abs(dAngle2) < PI)
		return true;

	return false;
}

double Geometry::SignedAngularDifference(double angle1, double angle2) 
{
	double dA = angle2 - angle1;
	if(dA > PI)
		dA -= TWO_PI;
	if(dA < -PI)
		dA += TWO_PI;

	return dA;
}

QPoint Geometry::VerticalIntersect(const QLine& line, const double x)
{
	assert((line.p2().x()-line.p1().x()) != 0);

	double slope = (line.p2().y() - line.p1().y()) / (line.p2().x()-line.p1().x());
	double run = x - line.p1().x();

	double yInter = line.p1().y()+slope*run;

	return QPoint((float)x, (float)yInter);
}

QPoint Geometry::HorizontalIntersect(const QLine& line, const double y)
{
	assert((line.p2().y() - line.p1().y()) != 0);

	double vertSlope = (line.p2().x()-line.p1().x()) / (line.p2().y() - line.p1().y());
	double vertRun = y - line.p1().y();

	double xInter = line.p1().x()+vertSlope*vertRun;

	return QPoint((float)xInter, (float)y);
}

QPoint Geometry::Intersect(const QLine& line1, const QLine& line2)
{
	// express line 1 in form: Ax+By=C
	double A1 = line1.p2().y() - line1.p1().y();
	double B1 = line1.p1().x() - line1.p2().x();
	double C1 = A1*line1.p1().x() + B1*line1.p1().y();

	// express line 2 in form: Ax+By=C
	double A2 = line2.p2().y() - line2.p1().y();
	double B2 = line2.p1().x() - line2.p2().x();
	double C2 = A2*line2.p1().x() + B2*line2.p1().y();

	double det = A1*B2 - A2*B1;
	if(det != 0)
	{
		double x = (B2*C1 - B1*C2)/det;
		double y = (A1*C2 - A2*C1)/det;

		return QPoint((float)x, (float)y);
	}

	return QPoint(0, 0);
}

bool Geometry::ClosestPointToLine(const QLineF& line, const QPointF& point, QPointF& closestPoint)
{
	/*
	[ Source unknown ]

	Subject 1.02: How do I find the distance from a point to a line?


			Let the point be C (Cx,Cy) and the line be AB (Ax,Ay) to (Bx,By).
			Let P be the point of perpendicular projection of C on AB.  The parameter
			r, which indicates P's position along AB, is computed by the dot product 
			of AC and AB divided by the square of the length of AB:
	    
			(1)     AC dot AB
					r = ---------  
							||AB||^2
	    
			r has the following meaning:
	    
					r=0      P = A
					r=1      P = B
					r<0      P is on the backward extension of AB
					r>1      P is on the forward extension of AB
					0<r<1    P is interior to AB
	*/

	float dx = line.p2().x()-line.p1().x();
	float dy = line.p2().y()-line.p1().y();

	float r_numerator = (point.x()-line.p1().x())*dx + (point.y()-line.p1().y())*dy;
	float r_denomenator = dx*dx + dy*dy;
	float r = r_numerator / r_denomenator;

	closestPoint.setX(line.p1().x() + r*dx);
	closestPoint.setY(line.p1().y() + r*dy);

	return (r >= 0 && r <= 1);
}

void Geometry::ClosestPointToLineSegment(const QLineF& line, const QPointF& point, QPointF& closestPoint)
{
	/*
	[ Source unknown ]

	Subject 1.02: How do I find the distance from a point to a line?


			Let the point be C (Cx,Cy) and the line be AB (Ax,Ay) to (Bx,By).
			Let P be the point of perpendicular projection of C on AB.  The parameter
			r, which indicates P's position along AB, is computed by the dot product 
			of AC and AB divided by the square of the length of AB:
	    
			(1)     AC dot AB
					r = ---------  
							||AB||^2
	    
			r has the following meaning:
	    
					r=0      P = A
					r=1      P = B
					r<0      P is on the backward extension of AB
					r>1      P is on the forward extension of AB
					0<r<1    P is interior to AB
	*/

	float dx = line.p2().x()-line.p1().x();
	float dy = line.p2().y()-line.p1().y();

	float r_numerator = (point.x()-line.p1().x())*dx + (point.y()-line.p1().y())*dy;
	float r_denomenator = dx*dx + dy*dy;
	float r = r_numerator / r_denomenator;

	closestPoint.setX(line.p1().x() + r*dx);
	closestPoint.setY(line.p1().y() + r*dy);

	if(r < 0)
		closestPoint = line.p1();
	else if(r > 1)
		closestPoint = line.p2();
}

double Geometry::Distance(const QPoint& pt1, const QPoint& pt2)
{
	double dx = pt1.x() - pt2.x();
	double dy = pt1.y() - pt2.y();

	return sqrt(dx*dx + dy*dy);
}

QPoint Geometry::MidPoint(const QLine& line)
{	
	double dx = line.p2().x() - line.p1().x();
	double dy = line.p2().y() - line.p1().y();
	return QPoint(line.p1().x() + 0.5*dx, line.p1().y() + 0.5*dy);
}


bool Geometry::PointInPolygon(const QPoint& pt, const QVector<QPoint>& polygon)
{
	// Taken from: http://local.wasp.uwa.edu.au/~pbourke/geometry/insidepoly/
	// Uses the crossing number (even-odd rule) algorithm
	bool bInPolygon = false;
  for(int i = 0, j = polygon.size()-1; i < polygon.size(); j = i++) 
	{
    if ((((polygon.at(i).y() <= pt.y()) && (pt.y() < polygon.at(j).y())) ||
         ((polygon.at(j).y() <= pt.y()) && (pt.y() < polygon.at(i).y()))) &&
        (pt.x() < (polygon.at(j).x() - polygon.at(i).x()) * (pt.y() - polygon.at(i).y()) / (polygon.at(j).y() - polygon.at(i).y()) + polygon.at(i).x()))
		{
      bInPolygon = !bInPolygon;
		}
  }

  return bInPolygon;
}

double Geometry::AngleBisector(double angle1, double angle2)
{
	if(angle1 < 0) 
		angle1 = TWO_PI + angle1;
	
	if(angle2 < 0) 
		angle2 = TWO_PI + angle2;
	
	double midAngle;
	if(angle1 > angle2)
	{
		double deltaAngle = angle1 - angle2;
		if(deltaAngle > PI) 
			deltaAngle = deltaAngle - TWO_PI;
		midAngle = angle2 + deltaAngle * 0.5;
	}
	else
	{
		double deltaAngle = angle2 - angle1;
		if(deltaAngle > PI) 
			deltaAngle = deltaAngle - TWO_PI;
		midAngle = angle1 + deltaAngle * 0.5;
	}

	return midAngle;
}

int Geometry::SmallestAngleDir(double start, double end)
{
	int dir = 1;
	double dAngle = start - end;
	if(dAngle > 0 && dAngle < PI)
			dir = -1;
	else if(dAngle > 0 && dAngle < -PI)
			dir = -1;

	return dir;
}
