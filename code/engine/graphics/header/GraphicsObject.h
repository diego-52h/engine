#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include <map>
#include <string>
#include <vector>

#include "Vector2.h"

class Transform;

struct Animation
{
	int framePosition;
	int frameDuration;
	
	Vector2 frameDimensions;
	
	std::string name;
	
	std::vector<Vector2> frames;
	
	Animation()
	{
	}
	
	Animation(const std::string& name, int frameDuration, const Vector2& frameDimensions)
	{
		this -> framePosition = 0;
		this -> frameDuration = frameDuration;
		
		this -> frameDimensions = frameDimensions;
		
		this -> name = name;
	}
};

struct SpriteSheet
{
	Vector2 frameSize;
	Vector2 totalSize;
	
	std::string path;
	
	SpriteSheet()
	{
	}
	
	SpriteSheet(const std::string& path, const Vector2& frameSize, const Vector2& totalSize)
	{
		this -> frameSize = frameSize;
		this -> totalSize = totalSize;
		
		this -> path = path;
	}
};

class GraphicsObject
{
	public:
		bool animationAdvanced;
		bool animationFinished;
	
	public:
		GraphicsObject(Transform* transform, const std::string& spriteSheet);
		~GraphicsObject();
		
		void setAnimation(const std::string& name);
		void addAnimation(const std::string& name, const Animation& animation);
		
		void advanceAnimation(float dt);
		
		Animation* getAnimation();
		Transform* getTransform();
		
		std::string& getSpriteSheet();
		
		const Animation* getAnimation() const;
		const Transform* getTransform() const;
	
	protected:
		float timeOffset;
		
		std::string spriteSheet;
		
		std::map<std::string, Animation> animations;
		
		Animation* animation;
		Transform* transform;
};

#endif