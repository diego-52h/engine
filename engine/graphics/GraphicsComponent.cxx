#include "GraphicsComponent.hxx"

GrahpicsComponent::GraphicsComponent(const std::string& sprite, const std::string& animation) : frame(0), frameTime(0), sprite(sprite), animation(animation) { }

void GraphicsComponent::setFrame(const Int_16 frame) { this -> frame = frame; }
void GraphicsComponent::setFrameTime(const Int_16 frameTime) { this -> frameTime = frameTime; }

void GraphicsComponent::setAnimation(const std::string& animation)
{
	this -> frame = 0;
	this -> frameTime = 0;
	
	this -> animation = animation;
}

Int_16 GraphicsComponent::getFrame() const { return this -> frame; }
Int_16 GraphicsComponent::getFrameTime() const { return this -> frameTime; }

std::string GraphicsComponent::getSprite() const { return this -> sprite; }
std::string GraphicsComponent::getAnimation() const { return this -> animation; }