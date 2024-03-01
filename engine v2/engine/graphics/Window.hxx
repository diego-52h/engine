#ifndef WINDOW_H
#define WINDOW_H

class Window
{
	public:
		Window(const std::string& path);
		~Window();
		
		void update(const SDL_Event& event);
		void setFullScreen(Bool fullScreen);
		
		Renderer& getRenderer();
	
	private:
		Int_16 ID;
		
		Renderer renderer;
		
		SDL_Window* window;
};

#endif