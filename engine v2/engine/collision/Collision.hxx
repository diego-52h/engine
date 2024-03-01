#ifndef COLLISION_H
#define COLLISION_H

#include "Vector2.hxx"

class CollisionVolume;

class Collision
{
	public:
		Collision(CollisionVolume& volumeA, CollisionVolume& volumeB);
		
		Bool exists() const;
		
		Float getDistance() const;
		
		const Vector2& getNormal() const;
		
		CollisionVolume& getVolumeA();
		CollisionVolume& getVolumeB();
	
	private:
		Float distance;
		
		Vector2 normal;
		
		CollisionVolume& volumeA;
		CollisionVolume& volumeB;
};

#endif