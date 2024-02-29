#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H

class GraphicsComponent
{
	public:
		GraphicsComponent(const std::string& sprite, const std::string& animation);
		
		void setFrame(const Int_16 frame);
		void setFrameTime(const Int_16 frameTime);
		
		void setAnimation(const std::string& animation);
		
		Int_16 getFrame() const;
		Int_16 getFrameTime() const;
		
		const std::string& getSprite() const;
		const std::string& getAnimation() const;
	
	private:
		Int_16 frame;
		Int_16 frameTime;
		
		std::string sprite;
		std::string animation;
};

#endif