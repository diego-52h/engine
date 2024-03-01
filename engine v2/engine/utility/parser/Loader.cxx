#include "Loader.hxx"

#include <json.h>

GameSection Loader::createGameSection(const std::string& path)
{
	Json::Value JsonSection;
	
	ifstream(path) >> JsonSection;
	
	Float w = JsonSection["w"].asFloat();
	Float h = JsonSection["h"].asFloat();
	
	GameSection section = GameSection(w, h);
	
	for(Json::Value& JsonNode : JsonSection["nodes"])
	{
		std::string type = JsonNode["type"].asString();
		
		std::string name = JsonNode["name"].asString();
		std::string path = JsonNode["path"].asString();
		
		Node& parent = (JsonNode["parent"].asString() == "none") ? section.getRoot() : section.getNode(JsonNode["parent"].asString());
		
		Transform transform = Transform(
			JsonNode["transform"]["orientation"].asFloat(),
			
			{JsonNode["transform"]["scale"][0].asFloat(), JsonNode["transform"]["scale"][1].asFloat()},
			{JsonNode["transform"]["position"][0].asFloat(), JsonNode["transform"]["position"][1].asFloat()}
		);
		
		if(type == "static")
			section.appendNode(Loader::createStaticNode(path, name, transform, parent));
		
		if(type == "active")
			section.appendNode(Loader::createActiveNode(path, name, transform, parent));
	}
	
	return section;
}

std::unique_ptr<StaticNode> Loader::createStaticNode(const std::string& path, const Transform& transform, Node& parent, const std::string& name)
{
	std::unique_ptr<StaticNode> node = new StaticNode(transform, parent, name);
	
	Loader::createGameNode(path, node);
	
	return node;
}

std::unique_ptr<ActiveNode> Loader::createActiveNode(const std::string& path, const Transform& transform, Node& parent, const std::string& name)
{
	std::unique_ptr<ActiveNode> node = new ActiveNode(transform, parent, name);
	
	Loader::createGameNode(path, node);
	
	return node;
}

Sprite Loader::createSprite(const std::string& path)
{
}

void Loader::createGameNode(const std::string& path, GameNode* node)
{
	Json::Value JsonNode;
	
	ifstream(path) >> JsonNode;
	
	std::unique_ptr<GraphicsComponent> graphicsComponent;
	{
		Json::Value JsonGraphicsComponent = JsonNode["graphicsComponent"];
		
		if(JsonGraphicsComponent.empty())
			break;
		
		std::string sprite = JsonGraphicsComponent["sprite"].asString();
		std::string animation = JsonGraphicsComponent["animation"].asString();
		
		graphicsComponent = new GraphicsObject(sprite, animation);
	}
	
	std::unique_ptr<DynamicsComponent> dynamicsComponent;
	{
		Json::Value JsonDynamicsComponent = JsonNode["dynamicsComponent"];
		
		if(JsonDynamicsComponent.empty())
			break;
		
		Properties properties;
		{
			Json::Value JsonProperties = JsonDynamicsComponent["properties"];
			
			properties.inverseMass = JsonProperties["mass"].asFloat();
			properties.inverseInertia = JsonProperties["inertia"].asFloat();
		}
		
		dynamicsComponent = new DynamicsComponent(properties);
	}
	
	node -> setGraphicsComponent(graphicsComponent);
	node -> setDynamicsComponent(dynamicsComponent);
}