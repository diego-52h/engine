#include "Window.h"

#include "GameEngine.h"
#include "World.h"

GameEngine::GameEngine(Window* window)
{
	this -> window = window;
	
	this -> graphicsEngine.setRenderer(window -> getRenderer());
}

GameEngine::~GameEngine()
{
}

void GameEngine::startWorld(World* world)
{
	float dt;
	
	this -> physicsEngine.setWorld(world);
	this -> graphicsEngine.setWorld(world);
	
	while(this -> window -> update())
	{
		dt = this -> window -> getTimer().getTimeDelta();
		
		world -> update(dt);
		
		world -> handleInput(this -> window -> getMouse());
		world -> handleInput(this -> window -> getKeyboard());
		
		physicsEngine.update(dt);
		graphicsEngine.update(dt);
	}
}