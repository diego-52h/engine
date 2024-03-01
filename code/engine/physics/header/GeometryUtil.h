#ifndef GEOMETRY_UTIL_H
#define GEOMETRY_UTIL_H

#include <vector>

#include "Vector2.h"

struct Side
{
	int numPoints;
	
	Vector2 normal;
	Vector2 firstPoint;
	Vector2 finalPoint;
	
	Side()
	{
		this -> numPoints = 0;
	}
	
	Side(const Vector2& firstPoint)
	{
		this -> numPoints = 1;
		
		this -> firstPoint = firstPoint;
	}
	
	Side(const Vector2& normal, const Vector2& firstPoint, const Vector2& finalPoint)
	{
		this -> numPoints = 2;
		
		this -> normal = normal;
		this -> firstPoint = firstPoint;
		this -> finalPoint = finalPoint;
	}
};

struct Line
{
	float distance;
	
	Vector2 normal;
	
	Line(const Vector2& normal, float distance)
	{
		this -> distance = distance;
		
		this -> normal = normal;
	}
};

namespace GeometryUtil
{
	void cutSide(Side& side, std::vector<Line>& cuttingLines);
	
	Vector2 getLineIntersection(const Line& lineA, const Line& lineB);
	Vector2 getClosestPointOnSide(const Vector2& point, const Side& side);
}

#endif