#include "World.h"

#include "GraphicsObject.h"

#include "Breakable.h"

#include "TinyXML2.h"

Breakable::Breakable(World* world, const std::string& path) : Object(world, path)
{
	tinyxml2::XMLDocument document;
	
	document.LoadFile(path.c_str());
	
	tinyxml2::XMLElement* XML_Breakable = document.FirstChildElement("Breakable");
	
	if(XML_Breakable != nullptr)
	{
		this -> maxHealth = XML_Breakable -> FloatAttribute("maxHealth");
		
		this -> currentHealth = maxHealth;
	}
}

Breakable::~Breakable()
{
}

void Breakable::update(float dt)
{
	if(this -> currentHealth <= 0)
	{
		if(this -> graphicsObject != nullptr)
			this -> graphicsObject -> setAnimation("break");
		
		else
			this -> world -> removeObject(this);
	}
	
	GameObject::update(dt);
}

void Breakable::onAnimationFinished(const std::string& animation)
{
	if(animation == "break")
		this -> world -> removeObject(this);
}

bool Breakable::onCollision(GameObject* objectB)
{
	this -> currentHealth--;
	
	return true;
}