#include "GraphicsObject.h"

#include "Transform.h"

GraphicsObject::GraphicsObject(Transform* transform, const std::string& spriteSheet)
{
	this -> spriteSheet = spriteSheet;
	
	this -> animation = nullptr;
	this -> transform = transform;
}

GraphicsObject::~GraphicsObject()
{
}

void GraphicsObject::setAnimation(const std::string& name)
{
	auto it = this -> animations.find(name);
	
	if(it != this -> animations.end())
	{
		if(this -> animation == &(*it).second)
			return;
		
		this -> animation = &(*it).second;
		
		this -> animation -> framePosition = 0;
	}
}

void GraphicsObject::addAnimation(const std::string& name, const Animation& animation)
{
	this -> animations[name] = animation;
}

void GraphicsObject::advanceAnimation(float dt)
{
	this -> animationAdvanced = false;
	this -> animationFinished = false;
	
	if(this -> animation == nullptr)
		return;
	
	this -> timeOffset += dt;
	
	if(this -> timeOffset > this -> animation -> frameDuration)
	{
		this -> timeOffset -= this -> animation -> frameDuration;
		
		if(this -> animation -> framePosition < (this -> animation -> frames.size() - 1))
		{
			this -> animation -> framePosition++;
			
			this -> animationAdvanced = true;
		}
		
		else
		{
			this -> animation -> framePosition = 0;
			
			this -> animationFinished = true;
		}
	}
}

std::string& GraphicsObject::getSpriteSheet()
{
	return this -> spriteSheet;
}

Animation* GraphicsObject::getAnimation()
{
	return this -> animation;
}

Transform* GraphicsObject::getTransform()
{
	return this -> transform;
}

const Animation* GraphicsObject::getAnimation() const
{
	return this -> animation;
}

const Transform* GraphicsObject::getTransform() const
{
	return this -> transform;
}