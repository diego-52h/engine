#ifndef ENEMY_H
#define ENEMY_H

#include "NPC.h"

class Enemy : public NPC
{
	public:
		Enemy(const std::string& name, const std::string& path);
		~Enemy();
		
		virtual void update(float dt) override;
		virtual void onCollision(GameObject* objectB) override;
	
	protected:
};

#endif