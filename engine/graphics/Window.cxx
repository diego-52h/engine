#include "Window.hxx"

Window::Window(const Int_16 x, const Int_16 y, const Int_16 w, const Int_16 h) : renderer(Renderer(nullptr))
{
	this -> window = SDL_CreateWindow(title, x, y, w, h, flags);
	
	assert(window != nullptr);
	
	SDL_Renderer* renderer = SDL_CreateRenderer(this -> window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if(renderer == nullptr)
	{
		SDL_DestroyWindow(this -> window);
		
		assert(false);
	}
	
	this -> ID = SDL_GetWindowID(this -> window);
	this -> renderer = Renderer(renderer);
}

Window::~Window()
{
	SDL_DestroyWindow(this -> window);
}

void Window::update(const SDL_Event& event)
{
	if((event != SDL_WINDOW_EVENT) || (event.window.windowID != this -> ID))
		return;
	
	switch(event.window.event)
	{
		case SDL_WINDOWEVENT_SIZE_CHANGED:
		{
			this -> renderer.update();
			this -> renderer.present();
		} break;
		
		case SDL_WINDOWEVENT_EXPOSED:
		{
			this -> renderer.present();
		} break;
		
		case SDL_WINDOWEVENT_CLOSE:
		{
			// Windows is closed
		} break;
	}
}

void Window::setFullScreen(Bool fullScreen)
{
	if(fullScreen)
		SDL_SetWindowFullScreen(this -> window, SDL_TRUE);
	
	else
		SDL_SetWindowFullScreen(this -> window, SDL_FALSE);
}

SDL_Renderer* Window::getRenderer() { return this -> renderer; }