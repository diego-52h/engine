#include "GameObject.h"
#include "World.h"

#include "GraphicsObject.h"

#include "PhysicsObject.h"

GameObject::GameObject(World* world)
{
	this -> world = world;
	
	this -> physicsObject = nullptr;
	this -> graphicsObject = nullptr;
}

GameObject::~GameObject()
{
}

Transform& GameObject::getTransform()
{
	return this -> transform;
}

PhysicsObject* GameObject::getPhysicsObject() const
{
	return this -> physicsObject;
}

GraphicsObject* GameObject::getGraphicsObject() const
{
	return this -> graphicsObject;
}

const Transform& GameObject::getTransform() const
{
	return this -> transform;
}

void GameObject::update(float dt)
{
	this -> transform.updateMatrices();
}