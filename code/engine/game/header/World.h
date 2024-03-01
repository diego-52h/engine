#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Mouse.h"
#include "Keyboard.h"

class GameObject;

class Camera;

class World
{
	public:
		World();
		~World();
		
		void appendObject(GameObject* object);
		void removeObject(GameObject* object);
		
		std::vector<GameObject*> getObjects();
		
		Camera* getCamera();
		
		virtual void update(float dt);
		
		virtual void handleInput(const Mouse& mouse) = 0;
		virtual void handleInput(const Keyboard& keyboard) = 0;
	
	protected:
		Camera* currentCamera;
		
		std::vector<Camera*> cameras;
		std::vector<GameObject*> objects;
};

#endif