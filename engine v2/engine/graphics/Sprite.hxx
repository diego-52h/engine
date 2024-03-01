#ifndef SPRITE_H
#define SPRITE_H

struct Frame
{
	Int_16 x;
	Int_16 y;
	
	Int_16 w;
	Int_16 h;
};

struct Animation
{
	Int_16 frameSpan;
	
	Vector<Frame> frames;
};

class Sprite
{
	public:
		Sprite(const std::string& path);
		
		const std::string& getTexture() const;
		
		const Animation& getAnimation(const std::string& name) const;
	
	private:
		std::string texture;
		
		std::map<std::string, Animation> animations;
};

#endif