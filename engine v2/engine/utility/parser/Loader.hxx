#ifndef LOADER_H
#define LOADER_H

class Loader
{
	public:
		static GameSection createGameSection(const std::string& path);
		
		static std::unique_ptr<StaticNode> createStaticNode(const std::string& path, const Transform& transform, Node& parent, const std::string& name);
		static std::unique_ptr<ActiveNode> createActiveNode(const std::string& path, const Transform& transform, Node& parent, const std::string& name);
	
	private:
		static Sprite createSprite(const std::string& path);
		
		static void createGameNode(const std::string& path, GameNode* node);
};

#endif