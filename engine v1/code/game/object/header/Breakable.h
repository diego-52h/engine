#ifndef BREAKABLE_H
#define BREAKABLE_H

#include <string>

#include "Object.h"

class World;

class Breakable : public Object
{
	public:
		Breakable(World* world, const std::string& path);
		~Breakable();
		
		virtual void update(float dt) override;
		virtual void onAnimationFinished(const std::string& animation) override;
		
		virtual bool onCollision(GameObject* objectB) override;
	
	protected:
		float maxHealth;
		float currentHealth;
};

#endif