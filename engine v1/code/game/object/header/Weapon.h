#ifndef WEAPON_H
#define WEAPON_H

#include <string>

#include "Object.h"

class World;

class Weapon : public Object
{
	public:
		Weapon(World* world, const std::string& path);
		~Weapon();
		
		void shoot();
		
		virtual void onAnimationFinished(const std::string& animation) override;
		
		virtual bool onCollision(GameObject* objectB) override;
	
	protected:
		int maxAmmoCount;
		int maxClipCount;
		
		int currentAmmoCount;
		int currentClipCount;
};

#endif