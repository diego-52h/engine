#include <fstream>

#include "PhysicsObject.h"

#include "Camera.h"

#include "Level.h"

#include "Object.h"
#include "Breakable.h"
#include "Character.h"
#include "Weapon.h"

#include "TinyXML2.h"

std::map<std::string, Key> Level::keys = {
	{"W", Key::KEY_W},
	{"S", Key::KEY_S},
	{"A", Key::KEY_A},
	{"D", Key::KEY_D},
	
	{"F", Key::KEY_F},
	{"X", Key::KEY_X},
};

std::map<Key, Handler> Level::handlePressedKey;
std::map<Key, Handler> Level::handleDroppedKey;

Level::Level(const std::string& path) : World()
{
	tinyxml2::XMLDocument document;
	
	document.LoadFile(path.c_str());
	
	tinyxml2::XMLElement* XML_World = document.FirstChildElement("World");
	
	if(XML_World != nullptr)
	{
		this -> name = XML_World -> Attribute("name");
		
		tinyxml2::XMLElement* XML_Objects = XML_World -> FirstChildElement("Objects");
		
		if(XML_Objects != nullptr)
		{
			tinyxml2::XMLElement* XML_Object = XML_Objects -> FirstChildElement("Object");
			
			while(XML_Object != nullptr)
			{
				std::string XML_type = XML_Object -> Attribute("type");
				std::string XML_path = XML_Object -> Attribute("path");
				
				float XML_orientation = XML_Object -> FloatAttribute("orientation");
				
				float XML_scaleX = XML_Object -> FloatAttribute("scaleX");
				float XML_scaleY = XML_Object -> FloatAttribute("scaleY");
				
				float XML_positionX = XML_Object -> FloatAttribute("positionX");
				float XML_positionY = XML_Object -> FloatAttribute("positionY");
				
				GameObject* object;
				
				if(XML_type == "Object")
					object = new Object(this, XML_path);
				
				else if(XML_type == "Breakable")
					object = new Breakable(this, XML_path);
				
				else if(XML_type == "Character")
				{
					object = new Character(this, XML_path);
					
					this -> player = dynamic_cast<Character*>(object);
				}
				
				else if(XML_type == "Weapon")
					object = new Weapon(this, XML_path);
				
				object -> getTransform().setWorldOrientation(XML_orientation);
				
				object -> getTransform().setWorldScale(Vector2(XML_scaleX, XML_scaleY));
				object -> getTransform().setWorldPosition(Vector2(XML_positionX, XML_positionY));
				
				this -> appendObject(object);
				
				// Temporary
				if(XML_type == "Character")
					this -> appendObject(this -> player -> weapons[0]);
				
				XML_Object = XML_Object -> NextSiblingElement("Object");
			}
		}
	}
	
	this -> currentCamera = new Camera();
	
	this -> currentCamera -> getTransform().setWorldOrientation(0);
	
	this -> currentCamera -> getTransform().setWorldScale(Vector2(1, 1));
	this -> currentCamera -> getTransform().setWorldPosition(Vector2(0, 0));
	
	this -> currentCamera -> update(0);
	
	this -> loadInput("C:/Users/diego/Desktop/Game (tmp)/content/levels/keys.txt");
}

Level::~Level()
{
}

void Level::loadInput(const std::string& path)
{
	std::string key;
	
	std::string pressedHandler;
	std::string droppedHandler;
	
	std::ifstream file;
	
	file.open(path.c_str());
	
	if(file.is_open())
	{
		while(file >> key)
		{
			file >> pressedHandler;
			file >> droppedHandler;
			
			if(pressedHandler != "NONE")
				this -> handlePressedKey[this -> keys[key]] = this -> handlers[pressedHandler];
			
			if(droppedHandler != "NONE")
				this -> handleDroppedKey[this -> keys[key]] = this -> handlers[droppedHandler];
		}
	}
}

void Level::handleInput(const Mouse& mouse)
{
}

void Level::handleInput(const Keyboard& keyboard)
{
	for(Key key : keyboard.getPressedKeys())
	{
		Handler handler = Level::handlePressedKey[key];
		
		if(handler != nullptr)
			handler();
	}
	
	for(Key key : keyboard.getDroppedKeys())
	{
		Handler handler = Level::handleDroppedKey[key];
		
		if(handler != nullptr)
			handler();
	}
}

void Level::update(float dt)
{
	this -> currentCamera -> update(dt);
	
	World::update(dt);
}