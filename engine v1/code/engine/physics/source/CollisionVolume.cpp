#include "CollisionVolume.h"
#include "Transform.h"

CollisionVolume::CollisionVolume(Transform* transform)
{
	this -> type = VolumeType::INVALID;
	
	this -> transform = transform;
}

CollisionVolume::~CollisionVolume()
{
}