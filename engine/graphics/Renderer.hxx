#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
	friend class Window;
	
	public:
		void clear();
		void present();
		
		void render(const std::string& texture, const Frame& frame, const Matrix3& transform);
	
	private:
		Int_16 w;
		Int_16 h;
		
		SDL_Renderer* renderer;
		
		std::map<std::string, SDL_Texture*> textures;
	
	private:
		Renderer(SDL_Renderer* renderer);
		~Renderer();
		
		void update();
		
		SDL_Texture* getTexture(const std::string& path);
};

#endif