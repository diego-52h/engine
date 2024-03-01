#include "Mouse.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::update(SDL_Event& event)
{
	this -> scrollUp = false;
	this -> scrollDown = false;
	
	switch(event.type)
	{
		case SDL_MOUSEMOTION:
		{
			this -> positionX = event.motion.x;
			this -> positionY = event.motion.y;
		} break;
		
		case SDL_MOUSEWHEEL:
		{
			if(event.wheel.y > 0)
				this -> scrollUp = true;
			
			if(event.wheel.y < 0)
				this -> scrollDown = true;
		} break;
		
		case SDL_MOUSEBUTTONUP:
		{
		} break;
		
		case SDL_MOUSEBUTTONDOWN:
		{
		} break;
	}
}