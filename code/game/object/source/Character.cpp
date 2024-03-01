#include "World.h"

#include "GraphicsObject.h"

#include "PhysicsObject.h"

#include "Character.h"
#include "Weapon.h"

#include "TinyXML2.h"

Character::Character(World* world, const std::string& path) : Breakable(world, path)
{
	tinyxml2::XMLDocument document;
	
	document.LoadFile(path.c_str());
	
	tinyxml2::XMLElement* XML_Character = document.FirstChildElement("Character");
	
	if(XML_Character != nullptr)
	{
		this -> movementX = 0;
		this -> movementY = 0;
		
		this -> currentWeapon = 0;
		
		this -> speed = XML_Character -> FloatAttribute("speed");
		
		tinyxml2::XMLElement* XML_Weapon = XML_Character -> FirstChildElement("Weapon");
		
		for(int i = 0; (i < 3) && (XML_Weapon != nullptr); i++)
		{
			std::string path = XML_Weapon -> Attribute("path");
			
			Weapon* weapon = new Weapon(world, path);
			
			this -> weapons[i] = weapon;
			this -> weapons[i] -> getTransform().setParentTransform(Vector2(20, 0), &this -> transform);
			
			// this -> world -> appendObject(weapon);
			
			XML_Weapon = XML_Weapon -> NextSiblingElement();
		}
	}
}

Character::~Character()
{
}

void Character::moveL()
{
	this -> movementX += -this -> speed;
}

void Character::moveR()
{
	this -> movementX += this -> speed;
}

void Character::moveU()
{
	this -> movementY += this -> speed;
}

void Character::moveD()
{
	this -> movementY += -this -> speed;
}

void Character::punch()
{
	this -> weapons[0] -> shoot();
}

void Character::shoot()
{
	this -> weapons[currentWeapon] -> shoot();
}

void Character::prevWeapon()
{
	if(this -> currentWeapon == 1)
		this -> currentWeapon = 2;
	
	else
		this -> currentWeapon--;
}

void Character::nextWeapon()
{
	if(this -> currentWeapon == 2)
		this -> currentWeapon = 1;
	
	else
		this -> currentWeapon++;
}

void Character::update(float dt)
{
	if(this -> physicsObject != nullptr)
		this -> physicsObject -> setLinearVelocity(Vector2(this -> movementX, this -> movementY));
	
	if(this -> graphicsObject != nullptr)
	{
		if((this -> movementX == 0) && (this -> movementY == 0))
			this -> graphicsObject -> setAnimation("none");
		
		else
			this -> graphicsObject -> setAnimation("move");
	}
	
	this -> movementX = 0;
	this -> movementY = 0;
	
	Breakable::update(dt);
}

bool Character::onCollision(GameObject* objectB)
{
	// Breakable::onCollision(objectB);
	
	return true;
}