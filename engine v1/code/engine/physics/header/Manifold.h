#ifndef COLLISION_MANIFOLD_H
#define COLLISION_MANIFOLD_H

#include <vector>

#include "Vector2.h"

struct CollisionData;

struct ContactPoint
{
	float restitution;
	float penetration;
	
	Vector2 normal;
	Vector2 localPositionA;
	Vector2 localPositionB;
};

class Manifold
{
	public:
		std::vector<ContactPoint> contactPoints;
	
	public:
		Manifold();
		Manifold(const CollisionData& collisionData);
		~Manifold();
		
		void update(float dt);
		
		void applyImpulse();
		void addContactPoint(const Vector2& worldPositionA, const Vector2& worldPositionB, const Vector2& normal, float penetration);
	
	protected:
		PhysicsObject* physicsObjectA;
		PhysicsObject* physicsObjectB;
	
	protected:
		void updateContactPoint(ContactPoint& contactPoint, float dt);
		void solveContactPoint(ContactPoint& contactPoint);
};

#endif