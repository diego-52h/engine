#include <SDL2/SDL.h>

#include "Window.h"

Window::Window(const std::string& title, int width, int height)
{
	this -> window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
	this -> renderer = SDL_CreateRenderer(this -> window, -1, 0);
}

Window::~Window()
{
	SDL_DestroyWindow(this -> window);
	SDL_DestroyRenderer(this -> renderer);
}

bool Window::update()
{
	this -> timer.update();
	
	SDL_Event event;
	
	SDL_PollEvent(&event);
	
	if(event.type == SDL_QUIT)
		return false;
	
	this -> mouse.update(event);
	this -> keyboard.update(event);
	
	return true;
}

const Timer& Window::getTimer() const
{
	return this -> timer;
}

const Mouse& Window::getMouse() const
{
	return this -> mouse;
}

const Keyboard& Window::getKeyboard() const
{
	return this -> keyboard;
}

SDL_Renderer* Window::getRenderer()
{
	return this -> renderer;
}