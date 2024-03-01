#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "Keyboard.h"
#include "Mouse.h"
#include "Timer.h"

class SDL_Window;
class SDL_Renderer;

class Window
{
	public:
		Window(const std::string& title, int width, int height);
		~Window();
		
		bool update();
		
		const Timer& getTimer() const;
		
		const Mouse& getMouse() const;
		const Keyboard& getKeyboard() const;
		
		SDL_Renderer* getRenderer();
	
	protected:
		Timer timer;
		
		Mouse mouse;
		Keyboard keyboard;
		
		SDL_Window* window;
		SDL_Renderer* renderer;
};

#endif