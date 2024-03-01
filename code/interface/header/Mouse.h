#ifndef MOUSE_H
#define MOUSE_H

#include <SDL2/SDL.h>

class Mouse
{
	public:
		Mouse();
		~Mouse();
		
		void update(SDL_Event& event);
	
	protected:
		bool scrollUp;
		bool scrollDown;
		
		float positionX;
		float positionY;
};

#endif