#include "CollisionVolume.h"
#include "PhysicsObject.h"
#include "Transform.h"

PhysicsObject::PhysicsObject(Transform* transform, CollisionVolume* collisionVolume, float friction, float elasticity, float inverseMass, float inverseInertia)
{
	this -> friction = friction;
	this -> elasticity = elasticity;
	
	this -> inverseMass = inverseMass;
	this -> inverseInertia = inverseInertia;
	
	this -> torque = 0;
	this -> angularVelocity = 0;
	
	this -> transform = transform;
	
	this -> collisionVolume = collisionVolume;
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::clearForces()
{
	this -> torque = 0;
	
	this -> force.toZero();
}

void PhysicsObject::addTorque(float torque)
{
	this -> torque += torque;
}

void PhysicsObject::addAngularImpulse(float impulse)
{
	this -> angularVelocity += impulse * this -> inverseInertia;
}

void PhysicsObject::setAngularVelocity(float angularVelocity)
{
	this -> angularVelocity = angularVelocity;
}

void PhysicsObject::addForce(const Vector2& force)
{
	this -> force += force;
}

void PhysicsObject::addLinearImpulse(const Vector2& impulse)
{
	this -> linearVelocity += impulse * this -> inverseMass;
}

void PhysicsObject::setLinearVelocity(const Vector2& linearVelocity)
{
	this -> linearVelocity = linearVelocity;
}

float PhysicsObject::getFriction() const
{
	return this -> friction;
}

float PhysicsObject::getElasticity() const
{
	return this -> elasticity;
}

float PhysicsObject::getInverseMass() const
{
	return this -> inverseMass;
}

float PhysicsObject::getInverseInertia() const
{
	return this -> inverseInertia;
}

float PhysicsObject::getTorque() const
{
	return this -> torque;
}

float PhysicsObject::getAngularVelocity() const
{
	return this -> angularVelocity;
}

Vector2 PhysicsObject::getForce() const
{
	return this -> force;
}

Vector2 PhysicsObject::getLinearVelocity() const
{
	return this -> linearVelocity;
}

Transform* PhysicsObject::getTransform()
{
	return this -> transform;
}

const Transform* PhysicsObject::getTransform() const
{
	return this -> transform;
}

const CollisionVolume* PhysicsObject::getCollisionVolume() const
{
	return this -> collisionVolume;
}