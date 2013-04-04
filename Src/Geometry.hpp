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

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "stdafx.h"

/**
 * @brief Functions for calculating basic geometric relationships.
 */
class Geometry
{
public:
	/**
	 * @brief Determine if shortest distance between two angles crosses a given quadrant.
	 * @param quadrantAngle Angle of quadrant (in radians).
	 * @param angle1 First angle of interest (in radians).
	 * @param angle2 Second angle of interest (in radians).
	 * @return True if shortest distance between angles crosses teh provided quadrant angle.
	 */
	static bool CrossedQuadrantBoundaries(double quadrantAngle, double angle1, double angle2);

	/**
	 * @brief Determine shortest distance between two angles while perserving relative direction.
	 * @param angle1 First angle of interest (in radians).
	 * @param angle2 Second angle of interest (in radians).
	 * @return Shortest angle with CCW being positive and CW being negative.
	 */
	static double SignedAngularDifference(double angle1, double angle2);

	/**
	 * @brief Find intersection between a vertical and diagonal line.
	 * @param line Diagonal line.
	 * @param x X-coordinate of vertical line.
	 * @return Point of intersections.
	 */
	static QPoint VerticalIntersect(const QLine& line, const double x);

	/**
	 * @brief Find intersection between a horizontal and diagonal line.
	 * @param line Diagonal line.
	 * @param y Y-coordinate of horizontal line.
	 * @return Point of intersections.
	 */
	static QPoint HorizontalIntersect(const QLine& line, const double y);

	/**
	 * @brief Find intersection between two lines.
	 * @param line Diagonal line 1.
	 * @param line Diagonal line 2.
	 * @return Point of intersections between lines.
	 */
	static QPoint Intersect(const QLine& line1, const QLine& line2);

	/**
	 * @brief Find the closest point on a line, L, to a given point, P.
	 * @param line Line L.
	 * @param point Point P.
	 * @param closestPoint Set to the closest point on L to P.
	 * @return True if closest point on the line is on the line segment specified by L, otherwise false.
	 */
	static bool ClosestPointToLine(const QLineF& line, const QPointF& point, QPointF& closestPoint);

		/**
	 * @brief Find the closest point on a line segment, L, to a given point, P.
	 * @param line Line L.
	 * @param point Point P.
	 * @param closestPoint Set to the closest point on L to P.
	 */
	static void ClosestPointToLineSegment(const QLineF& line, const QPointF& point, QPointF& closestPoint);

	/**
	 * @brief Calculate the distance between two points.
	 * @param pt1 First point.
	 * @param pt2 Second point.
	 * @return Distance between points.
	 */
	static double Distance(const QPoint& pt1, const QPoint& pt2);

	/** 
	 * @brief Find mid-point of a line.
	 * @param line Line of interest.
	 * @return Mid-point of line.
	 */
	static QPoint MidPoint(const QLine& line);

	/**
	 * @brief Determine if a point is within a polygon. Note: the point and polygon.
	 * @param pt Point to test.
	 * @param polygon Vector of points defining polygon. All points should be specified only once.
	 * @return True if the point is contained in the polygon.
	 */
	static bool PointInPolygon(const QPoint& pt, const QVector<QPoint>& polygon);

	/** 
	 * @brief Determine if the smallest angle between a start and stop angle is in the CW or CCW direction.
	 * @param start First angle of interest.
	 * @param end Second angle of interest.
	 * @return -1/1 if the smallest angle going from start to end is in the CW/CCW direction.
	 */
	 static int SmallestAngleDir(double start, double end);

	 	/** 
	 * @brief Find angle bisector of two angles.
	 * @param angle1 First angle.
	 * @param angle2 Second angle.
	 * @return Angle halfway between angle1 and angle2.
	 */
	static double AngleBisector(double angle1, double angle2);
};


#endif
