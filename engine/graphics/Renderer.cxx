#include "Renderer.hxx"

Renderer::Renderer(SDL_Renderer* renderer) : renderer(renderer)
{
	this -> update();
}

Renderer::~Renderer()
{
	for(const auto& [path, texture] : this -> textures)
		SDL_DestroyTexture(texture);
	
	SDL_DestroyRenderer(this -> renderer);
}

void Renderer::clear() { SDL_RenderClear(this -> renderer); }
void Renderer::present() { SDL_RenderPresent(this -> renderer); }

void Renderer::render(const std::string& texturePath, const Frame& frame, const Matrix3& transform)
{
	Float orientation = transform.getOrientation();
	
	Vector2 scale = transform.getScale();
	Vector2 position = transform.getPosition();
	
	SDL_Rect sourceRect;
	SDL_Rect screenRect;
	
	sourceRect.w = frame.w;
	sourceRect.h = frame.h;
	sourceRect.x = frame.x;
	sourceRect.y = frame.y;
	
	screenRect.w = frame.w * scale.x;
	screenRect.h = frame.h * scale.y;
	screenRect.x = +(position.x - (screenRect.w / 2.0f)) + (this -> w / 2.0f);
	screenRect.y = -(position.y - (screenRect.h / 2.0f)) + (this -> h / 2.0f);
	
	SDL_RenderCopyEx(this -> renderer, this -> getTexture(texture), &sourceRect, &screenRect, orientation, NULL, SDL_FLIP_NONE);
}

void Renderer::update() { SDL_GetRendererOutputSize(this -> renderer, &this -> w, &this -> h); }

SDL_Texture* Renderer::getTexture(const std::string& path)
{
	if(!this -> textures.contains(path))
		this -> textures[path] = IMG_LoadTexture(this -> renderer, path);
	
	return this -> textures[path];
}