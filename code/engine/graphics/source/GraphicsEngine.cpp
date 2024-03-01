#include <vector>

#include <SDL2/SDL_image.h>

#include "GameObject.h"
#include "World.h"

#include "Camera.h"
#include "GraphicsEngine.h"
#include "GraphicsObject.h"

#include "Math.h"

#include "Transform.h"

GraphicsEngine::GraphicsEngine()
{
	this -> world = nullptr;
	this -> renderer = nullptr;
}

GraphicsEngine::~GraphicsEngine()
{
}

void GraphicsEngine::setWorld(World* world)
{
	this -> world = world;
}

void GraphicsEngine::setRenderer(SDL_Renderer* renderer)
{
	this -> renderer = renderer;
}

void GraphicsEngine::update(float dt)
{
	this -> camera = this -> world -> getCamera();
	
	for(GameObject* object : this -> world -> getObjects())
	{
		GraphicsObject* graphicsObject = object -> getGraphicsObject();
		
		if(graphicsObject == nullptr)
			continue;
		
		graphicsObject -> advanceAnimation(dt);
		
		if(graphicsObject -> animationAdvanced)
			object -> onAnimationAdvanced(graphicsObject -> getAnimation() -> name);
		
		if(graphicsObject -> animationFinished)
			object -> onAnimationFinished(graphicsObject -> getAnimation() -> name);
	}
	
	this -> render();
}

void GraphicsEngine::render()
{
	SDL_RenderClear(this -> renderer);
	
	int rendererW;
	int rendererH;
	
	SDL_GetRendererOutputSize(this -> renderer, &rendererW, &rendererH);
	
	Matrix3 cameraInverseTransform = this -> camera -> getTransform().getWorldTransform().getInverse();
	
	for(GameObject* object : this -> world -> getObjects())
	{
		GraphicsObject* graphicsObject = object -> getGraphicsObject();
		
		if(graphicsObject == nullptr)
			continue;
		
		Animation* animation = graphicsObject -> getAnimation();
		
		if(animation == nullptr)
			continue;
		
		Matrix3 transform = cameraInverseTransform * graphicsObject -> getTransform() -> getWorldTransform();
		
		SDL_Rect sourceRect = this -> getSourceRect(animation);
		SDL_Rect targetRect = this -> getTargetRect(transform, sourceRect.w, sourceRect.h, rendererW, rendererH);
		
		SDL_Texture* texture = this -> getTexture(graphicsObject -> getSpriteSheet());
		
		SDL_RenderCopyEx(this -> renderer, texture, &sourceRect, &targetRect, Math::radiansToDegrees(Transform::getOrientation(transform)), NULL, SDL_FLIP_NONE);
	}
	
	SDL_RenderPresent(this -> renderer);
}

SDL_Rect GraphicsEngine::getSourceRect(Animation* animation)
{
	SDL_Rect sourceRect;
	
	sourceRect.w = animation -> frameDimensions.x;
	sourceRect.h = animation -> frameDimensions.y;
	sourceRect.x = animation -> frames[animation -> framePosition].x * sourceRect.w;
	sourceRect.y = animation -> frames[animation -> framePosition].y * sourceRect.h;
	
	return sourceRect;
}

SDL_Rect GraphicsEngine::getTargetRect(const Matrix3& transform, int frameW, int frameH, int rendererW, int rendererH)
{
	SDL_Rect targetRect;
	
	float orientation = Transform::getOrientation(transform);
	
	Vector2 scale = Transform::getScale(transform);
	Vector2 position = Transform::getPosition(transform);
	
	targetRect.w = scale.x * frameW;
	targetRect.h = scale.y * frameH;
	targetRect.x = +(position.x - (targetRect.w / 2.0f)) + (rendererW / 2.0f);
	targetRect.y = -(position.y + (targetRect.h / 2.0f)) + (rendererH / 2.0f);
	
	return targetRect;
}

SDL_Texture* GraphicsEngine::getTexture(const std::string& spriteSheet)
{
	std::string path = spriteSheet;
	
	if(this -> textures.count(path) > 0)
		return this -> textures[path];
	
	else
	{
		SDL_Surface* surface = IMG_Load(path.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(this -> renderer, surface);
		
		this -> textures[path] = texture;
		
		return texture;
	}
}