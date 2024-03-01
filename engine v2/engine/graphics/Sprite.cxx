#include "Sprite.hxx"

Sprite::Sprite(const std::string& path)
{
	// Load sprite
}

const std::string& Sprite::getTexture() const { return this -> texture; }

const Animation& Sprite::getAnimation(const std::string& name) const
{
	assert(animations.contains(name));
	
	return this -> animations[animation];
}