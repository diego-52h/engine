#include <SDL2/SDL.h>

#include "Timer.h"

Timer::Timer()
{
	this -> initialTime = SDL_GetTicks();
}

Timer::~Timer()
{
}

int Timer::getTimeDelta() const
{
	return this -> elapsedTime;
}

void Timer::update()
{
	int currentTime = SDL_GetTicks();
	
	this -> elapsedTime = currentTime - this -> initialTime;
	this -> initialTime = currentTime;
}