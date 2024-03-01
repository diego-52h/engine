#include "Level.h"
#include "GameEngine.h"

#include "Window.h"

Window window("-", 1080, 720);

int main(int argc, char* args[])
{
	GameEngine engine(&window);
	
	Level level("/home/x/me/projects/engine/data/game v1/content/levels/level.xml");
	
	engine.startWorld(&level);
	
	return 0;
}