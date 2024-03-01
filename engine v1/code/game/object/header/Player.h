#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Character.h"

class Player : public Character
{
	public:
		Player(const std::string& path);
		~Player();
		
		virtual bool onCollision(GameObject* objectB) override;
	
	protected:
		std::string team;
};

#endif