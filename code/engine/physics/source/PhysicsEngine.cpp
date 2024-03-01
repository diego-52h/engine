#include "GameObject.h"
#include "World.h"

#include "Vector2.h"

#include "CollisionDetection.h"
#include "Manifold.h"
#include "PhysicsEngine.h"
#include "PhysicsObject.h"

#define MAX_UPDATES 5
#define TIME_PER_ITERATION ((1.0f / 120.f) * 1000.0f)

PhysicsEngine::PhysicsEngine()
{
	this -> timeOffset = 0.0f;
	
	this -> world = nullptr;
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::setWorld(World* world)
{
	this -> world = world;
}

void PhysicsEngine::update(float dt)
{
	this -> timeOffset += dt;
	
	for(int i = 0; (i < MAX_UPDATES) && (this -> timeOffset >= TIME_PER_ITERATION); i++)
	{
		for(Manifold* manifold : this -> manifolds)
			delete manifold;
		
		this -> manifolds.clear();
		
		this -> broadPhase();
		this -> narrowPhase();
		
		for(Manifold* manifold : this -> manifolds)
			manifold -> update(TIME_PER_ITERATION);
		
		this -> integrateForVelocity(TIME_PER_ITERATION);
		
		for(Manifold* manifold : this -> manifolds)
			manifold -> applyImpulse();
		
		this -> integrateForPosition(TIME_PER_ITERATION);
		
		this -> timeOffset -= TIME_PER_ITERATION;
	}
	
	this -> clearForces();
}

void PhysicsEngine::broadPhase()
{
	this -> broadPhaseCollisions.clear();
	
	GameObject* objectA = nullptr;
	GameObject* objectB = nullptr;
	
	std::vector<GameObject*> objects = this -> world -> getObjects();
	
	for(int indexA = 0; indexA < objects.size(); indexA++)
	{
		objectA = objects[indexA];
		
		if(objectA -> getPhysicsObject() == nullptr)
			continue;
		
		for(int indexB = indexA + 1; indexB < objects.size(); indexB++)
		{
			objectB = objects[indexB];
			
			if(objectB -> getPhysicsObject() == nullptr)
				continue;
			
			CollisionPair collisionPair;
			
			collisionPair.objectA = objectA;
			collisionPair.objectB = objectB;
			
			this -> broadPhaseCollisions.push_back(collisionPair);
		}
	}
}

void PhysicsEngine::narrowPhase()
{
	CollisionDetection collisionDetection;
	
	CollisionData collisionData;
	
	for(const CollisionPair& collisionPair : this -> broadPhaseCollisions)
	{
		if(collisionDetection.areColliding(collisionPair.objectA -> getPhysicsObject(), collisionPair.objectB -> getPhysicsObject(), &collisionData))
		{
			bool handleCollisionA = collisionPair.objectA -> onCollision(collisionPair.objectB);
			bool handleCollisionB = collisionPair.objectB -> onCollision(collisionPair.objectA);
			
			if(handleCollisionA && handleCollisionB)
			{
				Manifold* manifold = new Manifold(collisionData);
				
				if(manifold -> contactPoints.size() > 0)
					this -> manifolds.push_back(manifold);
				
				else
					delete manifold;
			}
		}
	}
}

void PhysicsEngine::clearForces()
{
	for(GameObject* object : this -> world -> getObjects())
	{
		PhysicsObject* physicsObject = object -> getPhysicsObject();
		
		if(physicsObject == nullptr)
			continue;
		
		physicsObject -> clearForces();
	}
}

void PhysicsEngine::integrateForPosition(float dt)
{
	for(GameObject* object : this -> world -> getObjects())
	{
		PhysicsObject* physicsObject = object -> getPhysicsObject();
		
		if(physicsObject == nullptr)
			continue;
		
		Transform* transform = physicsObject -> getTransform();
		
		Vector2 position = transform -> getLocalPosition();
		Vector2 linearVelocity = physicsObject -> getLinearVelocity();
		
		position = position + (linearVelocity * dt);
		
		transform -> setLocalPosition(position);
		
		float orientation = transform -> getLocalOrientation();
		float angularVelocity = physicsObject -> getAngularVelocity();
		
		orientation = orientation + (angularVelocity * dt);
		
		transform -> setLocalOrientation(orientation);
	}
}

void PhysicsEngine::integrateForVelocity(float dt)
{
	for(GameObject* object : this -> world -> getObjects())
	{
		PhysicsObject* physicsObject = object -> getPhysicsObject();
		
		if(physicsObject == nullptr)
			continue;
		
		Vector2 linearVelocity = physicsObject -> getLinearVelocity();
		Vector2 linearAcceleration = physicsObject -> getForce() * physicsObject -> getInverseMass();
		
		linearVelocity = linearVelocity + (linearAcceleration * dt);
		
		physicsObject -> setLinearVelocity(linearVelocity);
		
		float angularVelocity = physicsObject -> getAngularVelocity();
		float angularAcceleration = physicsObject -> getTorque() * physicsObject -> getInverseInertia();
		
		angularVelocity = angularVelocity + (angularAcceleration * dt);
		
		physicsObject -> setAngularVelocity(angularVelocity);
	}
}