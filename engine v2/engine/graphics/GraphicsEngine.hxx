#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

class GraphicsEngine
{
	public:
		GraphicsEngine(GameSection& section, Renderer& renderer);
		
		void update(const Int_16 dt);
		void render(const Camera& camera);
	
	private:
		GameSection& section;
		
		Renderer& renderer;
		
		std::map<std::string, Sprite> sprites;
	
	private:
		void draw(const Camera& camera, const GameNode& node);
		
		const Sprite& getSprite(const std::string& path) const;
};

#endif