#include <float.h>

#include "Matrix2.h"
#include "Matrix3.h"

#include "BoxVolume.h"
#include "Transform.h"

BoxVolume::BoxVolume(Transform* transform, const Vector2& halfSizes) : CollisionVolume(transform)
{
	this -> type = VolumeType::BOX;
	
	this -> boxHull.addVertex(Vector2(-halfSizes.x, halfSizes.y));
	this -> boxHull.addVertex(Vector2(halfSizes.x, halfSizes.y));
	this -> boxHull.addVertex(Vector2(halfSizes.x, -halfSizes.y));
	this -> boxHull.addVertex(Vector2(-halfSizes.x, -halfSizes.y));
	
	this -> boxHull.addSide(Vector2(0.0f, 1.0f), 0, 1);
	this -> boxHull.addSide(Vector2(1.0f, 0.0f), 1, 2);
	this -> boxHull.addSide(Vector2(0.0f, -1.0f), 2, 3);
	this -> boxHull.addSide(Vector2(-1.0f, 0.0f), 3, 0);
}

BoxVolume::~BoxVolume()
{
}

void BoxVolume::getClippingInfo(const Vector2& axis, Side& side, Vector2& sideNormal, std::vector<Line>& cuttingLines) const
{
	Matrix3 transform = this -> transform -> getWorldTransform();
	
	Matrix2 normalTransform = transform.getMatrix2();
	Matrix2 inverseNormalTransform = normalTransform.getInverse();
	
	Vector2 localAxis = inverseNormalTransform * axis;
	
	int maxVertex;
	
	this -> boxHull.getMinMaxVerticesOnAxis(localAxis, nullptr, &maxVertex);
	
	float currProjection;
	float bestProjection = -FLT_MAX;
	
	const HullSide* bestSide = nullptr;
	const HullSide* currSide = nullptr;
	
	const HullVertex& vertex = this -> boxHull.getVertex(maxVertex);
	
	for(int sideId : vertex.enclosingSides)
	{
		currSide = &this -> boxHull.getSide(sideId);
		
		currProjection = Vector2::dotProduct(localAxis, currSide -> normal);
		
		if(currProjection > bestProjection)
		{
			bestSide = currSide;
			
			bestProjection = currProjection;
		}
	}
	
	sideNormal = (normalTransform * bestSide -> normal).getNormalised();
	
	const HullVertex& firstVertex = this -> boxHull.getVertex(bestSide -> firstVertexId);
	const HullVertex& finalVertex = this -> boxHull.getVertex(bestSide -> finalVertexId);
	
	side = Side(sideNormal, transform * firstVertex.position, transform * finalVertex.position);
	
	Vector2 linePoint;
	Vector2 lineNormal;
	
	std::vector<int> sides(bestSide -> adjacentSides);
	
	sides.push_back(bestSide -> id);
	
	for(int sideId : sides)
	{
		currSide = &this -> boxHull.getSide(sideId);
		
		linePoint = transform * this -> boxHull.getVertex(currSide -> firstVertexId).position;
		lineNormal = (normalTransform * currSide -> normal).getNormalised();
		
		cuttingLines.push_back(Line(lineNormal, Vector2::dotProduct(lineNormal, linePoint)));
	}
}

void BoxVolume::getVerticesOnAxis(const Vector2& axis, Vector2& min, Vector2& max) const
{
	int minVertex;
	int maxVertex;
	
	Matrix3 transform = this -> transform -> getWorldTransform();
	
	Matrix2 normalTransform = transform.getMatrix2();
	Matrix2 inverseNormalTransform = normalTransform.getInverse();
	
	Vector2 localAxis = (inverseNormalTransform * axis).getNormalised();
	
	this -> boxHull.getMinMaxVerticesOnAxis(localAxis, &minVertex, &maxVertex);
	
	min = transform * this -> boxHull.getVertex(minVertex).position;
	max = transform * this -> boxHull.getVertex(maxVertex).position;
}

void BoxVolume::getPossibleCollisionAxes(const CollisionVolume* volumeB, std::vector<Vector2>& possibleCollisionAxes) const
{
	Matrix2 boxOrientation = Matrix2::rotationMatrix(this -> transform -> getWorldOrientation());
	
	possibleCollisionAxes.push_back(boxOrientation * Vector2(1.0f, 0.0f));
	possibleCollisionAxes.push_back(boxOrientation * Vector2(0.0f, 1.0f));
}

Vector2 BoxVolume::getClosestPoint(const Vector2& point) const
{
	Matrix3 transform = this -> transform -> getWorldTransform();
	Matrix3 inverseTransform = transform.getInverse();
	
	Vector2 localPoint = inverseTransform * point;
	
	float currDistance;
	float bestDistance = FLT_MAX;
	
	Vector2 firstVertex;
	Vector2 finalVertex;
	
	Vector2 currClosestPoint;
	Vector2 bestClosestPoint;
	
	for(const HullSide& side : this -> boxHull.sides)
	{
		firstVertex = this -> boxHull.getVertex(side.firstVertexId).position;
		finalVertex = this -> boxHull.getVertex(side.finalVertexId).position;
		
		currClosestPoint = GeometryUtil::getClosestPointOnSide(localPoint, Side(side.normal, firstVertex, finalVertex));
		
		currDistance = Vector2::dotProduct(currClosestPoint - localPoint, currClosestPoint - localPoint);
		
		if(currDistance < bestDistance)
		{
			bestDistance = currDistance;
			
			bestClosestPoint = currClosestPoint;
		}
	}
	
	return transform * bestClosestPoint;
}