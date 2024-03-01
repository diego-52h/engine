#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "Vector2.h"

class CollisionVolume;
class Transform;

class PhysicsObject
{
	public:
		PhysicsObject(Transform* transform, CollisionVolume* collisionVolume, float friction, float elasticity, float inverseMass, float inverseInertia);
		~PhysicsObject();
		
		void clearForces();
		
		void addTorque(float torque);
		void addAngularImpulse(float impulse);
		void setAngularVelocity(float angularVelocity);
		
		void addForce(const Vector2& force);
		void addLinearImpulse(const Vector2& impulse);
		void setLinearVelocity(const Vector2& linearVelocity);
		
		float getFriction() const;
		float getElasticity() const;
		
		float getInverseMass() const;
		float getInverseInertia() const;
		
		float getTorque() const;
		float getAngularVelocity() const;
		
		Vector2 getForce() const;
		Vector2 getLinearVelocity() const;
		
		Transform* getTransform();
		
		const Transform* getTransform() const;
		const CollisionVolume* getCollisionVolume() const;
	
	protected:
		float friction;
		float elasticity;
		
		float inverseMass;
		float inverseInertia;
		
		float torque;
		float angularVelocity;
		
		Vector2 force;
		Vector2 linearVelocity;
		
		Transform* transform;
		CollisionVolume* collisionVolume;
};

#endif