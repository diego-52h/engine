#include "Player.h"

#include "TinyXML2.h"

Player::Player(const std::string& path) : Character(path)
{
	tinyxml2::XMLDocument document;
	
	document.LoadFile(path.c_str());
	
	tinyxml2::XMLElement* XML_Player = document.FirstChildElement("Player");
	
	if(XML_Player != nullptr)
	{
		this -> team = XML_Player -> Attribute("team");
	}
}

Player::~Player()
{
}

bool Player::onCollision(GameObject* objectB)
{
	Player* playerB = dynamic_cast<Player*>(objectB);
	
	if((playerB != nullptr) && (playerB -> team == this -> team))
		return false;
	
	return true;
}