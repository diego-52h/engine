#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include <vector>

#include "Vector2.h"

class CollisionVolume;
class PhysicsObject;

struct CollisionData
{
	float penetration;
	
	Vector2 normal;
	
	PhysicsObject* physicsObjectA;
	PhysicsObject* physicsObjectB;
};

class CollisionDetection
{
	public:
		CollisionDetection();
		~CollisionDetection();
		
		bool areColliding(PhysicsObject* physicsObjectA, PhysicsObject* physicsObjectB, CollisionData* collisionData);
	
	protected:
		bool collisionOnAxis(const Vector2& axis, const CollisionVolume& volumeA, const CollisionVolume& volumeB, CollisionData& collisionData);
		bool addPossibleCollisionAxis(Vector2 axis);
	
	private:
		std::vector<Vector2> possibleCollisionAxes;
};

#endif