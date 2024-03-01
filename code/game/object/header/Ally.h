#ifndef ALLY_H
#define ALLY_H

#include "NPC.h"

class Ally : public NPC
{
	public:
		Ally(const std::string& name, const std::string& path);
		~Ally();
		
		virtual void update(float dt) override;
		virtual void onCollision(GameObject* objectB) override;
	
	protected:
};

#endif