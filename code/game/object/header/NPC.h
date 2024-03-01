#ifndef NPC_H
#define NPC_H

#include "Character.h"

class NPC : public Character
{
	public:
		NPC(const std::string& name, const std::string& path);
		~NPC();
		
		virtual void update(float dt) override;
		virtual void onCollision(GameObject* objectB) override;
	
	protected:
};

#endif