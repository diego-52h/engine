#include "GraphicsObject.h"

#include "Vector2.h"

#include "BoxVolume.h"
#include "CircleVolume.h"
#include "CollisionVolume.h"
#include "PhysicsObject.h"

#include "Object.h"

#include "TinyXML2.h"

Object::Object(World* world, const std::string& path) : GameObject(world)
{
	tinyxml2::XMLDocument document;
	
	document.LoadFile(path.c_str());
	
	tinyxml2::XMLElement* XML_Object = document.FirstChildElement("Object");
	
	if(XML_Object != nullptr)
	{
		tinyxml2::XMLElement* XML_PhysicsObject = XML_Object -> FirstChildElement("PhysicsObject");
		tinyxml2::XMLElement* XML_GraphicsObject = XML_Object -> FirstChildElement("GraphicsObject");
		
		if(XML_PhysicsObject != nullptr)
		{
			float XML_friction = XML_PhysicsObject -> FloatAttribute("friction");
			float XML_elasticity = XML_PhysicsObject -> FloatAttribute("elasticity");
			
			std::string XML_mass = XML_PhysicsObject -> Attribute("mass");
			std::string XML_inertia = XML_PhysicsObject -> Attribute("inertia");
			
			float inverseMass = 0;
			float inverseInertia = 0;
			
			if(XML_mass != "INF")
				inverseMass = 1 / std::stof(XML_mass);
			
			if(XML_inertia != "INF")
				inverseInertia = 1 / std::stof(XML_inertia);
			
			tinyxml2::XMLElement* XML_CollisionVolume = XML_PhysicsObject -> FirstChildElement("CollisionVolume");
			
			CollisionVolume* collisionVolume = nullptr;
			
			if(XML_CollisionVolume != nullptr)
			{
				std::string XML_type = XML_CollisionVolume -> Attribute("type");
				
				if(XML_type == "BOX")
				{
					float XML_width = XML_CollisionVolume -> FloatAttribute("width");
					float XML_height = XML_CollisionVolume -> FloatAttribute("height");
					
					collisionVolume = new BoxVolume(&this -> transform, Vector2(XML_width / 2.0f, XML_height / 2.0f));
				}
				
				else if(XML_type == "CIRCLE")
				{
					float XML_radius = XML_CollisionVolume -> FloatAttribute("radius");
					
					collisionVolume = new CircleVolume(&this -> transform, XML_radius);
				}
			}
			
			this -> physicsObject = new PhysicsObject(&this -> transform, collisionVolume, XML_friction, XML_elasticity, inverseMass, inverseInertia);
		}
		
		if(XML_GraphicsObject != nullptr)
		{
			std::string XML_spriteSheet = XML_GraphicsObject -> Attribute("spriteSheet");
			
			this -> graphicsObject = new GraphicsObject(&this -> transform, XML_spriteSheet);
			
			tinyxml2::XMLElement* XML_Animation = XML_GraphicsObject -> FirstChildElement("Animation");
			
			while(XML_Animation != nullptr)
			{
				std::string XML_name = XML_Animation -> Attribute("name");
				
				float XML_frameDuration = XML_Animation -> FloatAttribute("frameDuration");
				
				float XML_frameW = XML_Animation -> FloatAttribute("frameW");
				float XML_frameH = XML_Animation -> FloatAttribute("frameH");
				
				Animation animation = Animation(XML_name, XML_frameDuration, Vector2(XML_frameW, XML_frameH));
				
				tinyxml2::XMLElement* XML_Frame = XML_Animation -> FirstChildElement("Frame");
				
				while(XML_Frame != nullptr)
				{
					float XML_frameX = XML_Frame -> FloatAttribute("frameX");
					float XML_frameY = XML_Frame -> FloatAttribute("frameY");
					
					animation.frames.push_back(Vector2(XML_frameX, XML_frameY));
					
					XML_Frame = XML_Frame -> NextSiblingElement("Frame");
				}
				
				this -> graphicsObject -> addAnimation(animation.name, animation);
				
				XML_Animation = XML_Animation -> NextSiblingElement("Animation");
			}
			
			this -> graphicsObject -> setAnimation("none");
		}
	}
}

Object::~Object()
{
}

void Object::update(float dt)
{
	GameObject::update(dt);
}

bool Object::onCollision(GameObject* objectB)
{
	return true;
}