#include "World.h"

#include "GraphicsObject.h"

#include "Weapon.h"

#include "TinyXML2.h"

Weapon::Weapon(World* world, const std::string& path) : Object(world, path)
{
	tinyxml2::XMLDocument document;
	
	document.LoadFile(path.c_str());
	
	tinyxml2::XMLElement* XML_Weapon = document.FirstChildElement("Weapon");
	
	if(XML_Weapon != nullptr)
	{
	}
}

Weapon::~Weapon()
{
}

void Weapon::shoot()
{
	if(this -> graphicsObject != nullptr)
		this -> graphicsObject -> setAnimation("shoot");
}

void Weapon::onAnimationFinished(const std::string& animation)
{
	if(animation == "shoot")
		this -> graphicsObject -> setAnimation("none");
}

bool Weapon::onCollision(GameObject* objectB)
{
	return false;
}