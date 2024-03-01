#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <map>
#include <string>

#include <SDL2/SDL.h>

struct Animation;

class World;
class Camera;
class Matrix3;

class GraphicsEngine
{
	public:
		GraphicsEngine();
		~GraphicsEngine();
		
		void setWorld(World* world);
		void setRenderer(SDL_Renderer* renderer);
		
		void update(float dt);
	
	protected:
		std::map<std::string, SDL_Texture*> textures;
		
		World* world;
		Camera* camera;
		
		SDL_Renderer* renderer;
	
	protected:
		void render();
		
		SDL_Rect getSourceRect(Animation* animation);
		SDL_Rect getTargetRect(const Matrix3& transform, int frameW, int frameH, int rendererW, int rendererH);
		
		SDL_Texture* getTexture(const std::string& spriteSheet);
};

#endif