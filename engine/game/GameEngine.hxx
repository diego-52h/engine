#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

class GameEngine
{
	public:
		GameEngine();
		
		void loop();
	
	private:
		Window window;
		
		GameSection section;
		
		GraphicsEngine graphicsEngine;
		DynamicsEngine dynamicsEngine;
};

#endif