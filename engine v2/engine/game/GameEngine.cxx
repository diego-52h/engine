#include "GameEngine.hxx"

const Int_16 MS_PER_UPDATE = 1.0 / 60.0;

GameEngine::GameEngine()
{
	this -> window = Loader::createWindow("");
	
	this -> section = Loader::createGameSection("");
	
	this -> graphicsEngine = GraphicsEngine(section);
	this -> dynamicsEngine = DynamicsEngine(section);
}

void GameEngine::gameLoop()
{
	Int_16 delay = 0;
	
	Int_16 currTime = 0;
	Int_16 prevTime = SDL_GetTicks();
	
	while(true)
	{
		SDL_Event event;
		
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				return;
		}
		
		currTime = SDL_GetTicks();
		
		delay += currTime - prevTime;
		
		prevTime = currTime;
		
		while(delay >= MS_PER_UPDATE)
		{
			graphicsEngine.update(MS_PER_UPDATE);
			dynamicsEngine.update(MS_PER_UPDATE);
			
			delay -= MS_PER_UPDATE;
		}
		
		section.update();
		
		graphicsEngine.render(this -> section.getCamera());
	}
}