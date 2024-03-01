//Created by DIBYZE

#include "GameEngine.h"
#include "Level.h"

#include "Window.h"

Window window("-", 1080, 720);

int main(int argc, char* args[])
{
	GameEngine engine(&window);
	
	Level level("C:/Users/diego/Desktop/Game (tmp)/content/levels/level.xml");
	
	engine.startWorld(&level);
	
	return 0;
}