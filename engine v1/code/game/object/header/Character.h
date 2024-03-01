#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include "Breakable.h"

class World;

class Weapon;

class Character : public Breakable
{
	public:
		Weapon* weapons[3];
	
	public:
		Character(World* world, const std::string& path);
		~Character();
		
		void moveL();
		void moveR();
		void moveU();
		void moveD();
		
		void punch();
		void shoot();
		
		void prevWeapon();
		void nextWeapon();
		
		virtual void update(float dt);
		
		virtual bool onCollision(GameObject* objectB);
	
	protected:
		int currentWeapon;
		
		// Weapon* weapons[3];
	
	private:
		float speed;
		
		float movementX;
		float movementY;
};

#endif