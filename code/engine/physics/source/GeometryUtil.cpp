#include <float.h>

#include "GeometryUtil.h"

void GeometryUtil::cutSide(Side& side, std::vector<Line>& cuttingLines)
{
	Line sideLine = Line(side.normal, Vector2::dotProduct(side.normal, side.firstPoint));
	
	for(const Line& cuttingLine : cuttingLines)
	{
		Vector2 intersectionPoint = GeometryUtil::getLineIntersection(sideLine, cuttingLine);
		
		if((intersectionPoint.x == FLT_MAX) && (intersectionPoint.y == FLT_MAX))
			continue;
		
		if(((side.firstPoint.x - intersectionPoint.x) * (side.finalPoint.x - intersectionPoint.x) <= 0) && ((side.firstPoint.y - intersectionPoint.y) * (side.finalPoint.y - intersectionPoint.y) <= 0))
		{
			if(((cuttingLine.normal.x * side.firstPoint.x) + (cuttingLine.normal.y * side.firstPoint.y) - cuttingLine.distance) > 0)
				side.firstPoint = intersectionPoint;
			
			else
				side.finalPoint = intersectionPoint;
		}
	}
}

Vector2 GeometryUtil::getLineIntersection(const Line& lineA, const Line& lineB)
{
	float a1 = lineA.normal.x;
	float b1 = lineA.normal.y;
	float c1 = lineA.distance;
	
	float a2 = lineB.normal.x;
	float b2 = lineB.normal.y;
	float c2 = lineB.distance;
	
	float determinant = (a1 * b2) - (a2 * b1);
	
	if(determinant = 0.0f)
		return Vector2(FLT_MAX, FLT_MAX);
	
	float x = ((b2 * c1) - (b1 * c2)) / determinant;
	float y = ((a1 * c2) - (a2 * c1)) / determinant;
	
	return Vector2(x, y);
}

Vector2 GeometryUtil::getClosestPointOnSide(const Vector2& pointC, const Side& side)
{
	Vector2 pointA = side.firstPoint;
	Vector2 pointB = side.finalPoint;
	
	Vector2 AtoB = pointB - pointA;
	Vector2 AtoC = pointC - pointA;
	
	float sideLength = Vector2::dotProduct(AtoB, AtoB);
	float pointProjection = Vector2::dotProduct(AtoC, AtoB);
	
	float proportion = pointProjection / sideLength;
	float distance = std::max(std::min(proportion, 1.0f), 0.0f);
	
	return pointA + (AtoB * distance);
}