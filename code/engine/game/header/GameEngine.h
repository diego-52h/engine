#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "GraphicsEngine.h"

#include "PhysicsEngine.h"

class Window;

class GameEngine
{
	public:
		GameEngine(Window* window);
		~GameEngine();
		
		void startWorld(World* world);
	
	protected:
		PhysicsEngine physicsEngine;
		GraphicsEngine graphicsEngine;
		
		Window* window;
};

#endif