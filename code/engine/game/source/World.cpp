#include <algorithm>

#include "GameObject.h"
#include "World.h"

#include "Camera.h"

World::World()
{
}

World::~World()
{
}

void World::appendObject(GameObject* object)
{
	this -> objects.push_back(object);
}

void World::removeObject(GameObject* object)
{
	this -> objects.erase(std::remove(this -> objects.begin(), this -> objects.end(), object));
	
	delete object;
}

std::vector<GameObject*> World::getObjects()
{
	return this -> objects;
}

Camera* World::getCamera()
{
	return this -> currentCamera;
}

void World::update(float dt)
{
	for(GameObject* object : this -> objects)
		object -> update(dt);
}