#include <float.h>

#include <cmath>

#include "CollisionDetection.h"
#include "CollisionVolume.h"
#include "PhysicsObject.h"

CollisionDetection::CollisionDetection()
{
}

CollisionDetection::~CollisionDetection()
{
}

bool CollisionDetection::areColliding(PhysicsObject* physicsObjectA, PhysicsObject* physicsObjectB, CollisionData* collisionData)
{
	const CollisionVolume* collisionVolumeA = physicsObjectA -> getCollisionVolume();
	const CollisionVolume* collisionVolumeB = physicsObjectB -> getCollisionVolume();
	
	if((collisionVolumeA == nullptr) || (collisionVolumeB == nullptr))
		return false;
	
	std::vector<Vector2> possibleCollisionAxesA;
	std::vector<Vector2> possibleCollisionAxesB;
	
	collisionVolumeA -> getPossibleCollisionAxes(collisionVolumeB, possibleCollisionAxesA);
	collisionVolumeB -> getPossibleCollisionAxes(collisionVolumeA, possibleCollisionAxesB);
	
	this -> possibleCollisionAxes.clear();
	
	for(const Vector2& possibleCollisionAxis : possibleCollisionAxesA)
		this -> addPossibleCollisionAxis(possibleCollisionAxis);
	
	for(const Vector2& possibleCollisionAxis : possibleCollisionAxesB)
		this -> addPossibleCollisionAxis(possibleCollisionAxis);
	
	CollisionData currCollisionData;
	CollisionData bestCollisionData;
	
	bestCollisionData.penetration = -FLT_MAX;
	
	for(const Vector2& possibleCollisionAxis : this -> possibleCollisionAxes)
	{
		if(!collisionOnAxis(possibleCollisionAxis, *collisionVolumeA, *collisionVolumeB, currCollisionData))
			return false;
		
		if(currCollisionData.penetration >= bestCollisionData.penetration)
			bestCollisionData = currCollisionData;
	}
	
	if(collisionData != nullptr)
	{
		bestCollisionData.physicsObjectA = physicsObjectA;
		bestCollisionData.physicsObjectB = physicsObjectB;
		
		*collisionData = bestCollisionData;
	}
	
	return true;
}

bool CollisionDetection::collisionOnAxis(const Vector2& axis, const CollisionVolume& volumeA, const CollisionVolume& volumeB, CollisionData& collisionData)
{
	Vector2 minA;
	Vector2 maxA;
	Vector2 minB;
	Vector2 maxB;
	
	volumeA.getVerticesOnAxis(axis, minA, maxA);
	volumeB.getVerticesOnAxis(axis, minB, maxB);
	
	float pointA = Vector2::dotProduct(axis, minA);
	float pointB = Vector2::dotProduct(axis, maxA);
	float pointC = Vector2::dotProduct(axis, minB);
	float pointD = Vector2::dotProduct(axis, maxB);
	
	if((pointA <= pointC) && (pointC < pointB))
	{
		collisionData.normal = axis;
		collisionData.penetration = pointC - pointB;
		
		return true;
	}
	
	if((pointC <= pointA) && (pointA < pointD))
	{
		collisionData.normal = -axis;
		collisionData.penetration = pointA - pointD;
		
		return true;
	}
	
	return false;
}

bool CollisionDetection::addPossibleCollisionAxis(Vector2 axis)
{
	const float epsilon = 1e-6f;
	
	if(Vector2::dotProduct(axis, axis) < epsilon)
		return false;
	
	axis.normalise();
	
	for(const Vector2& possibleCollisionAxis : this -> possibleCollisionAxes)
	{
		if(Vector2::dotProduct(axis, possibleCollisionAxis) >= (1.0f - epsilon))
			return false;
	}
	
	this -> possibleCollisionAxes.push_back(axis);
	
	return true;
}