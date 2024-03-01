#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include "GameObject.h"

class Object : public GameObject
{
	public:
		Object(World* world, const std::string& path);
		~Object();
		
		virtual void update(float dt) override;
		
		virtual bool onCollision(GameObject* objectB) override;
};

#endif