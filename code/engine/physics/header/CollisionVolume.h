#ifndef COLLISION_VOLUME_H
#define COLLISION_VOLUME_H

#include <vector>

#include "Vector2.h"

#include "GeometryUtil.h"

class Transform;

enum class VolumeType
{
	BOX,
	CIRCLE,
	INVALID,
};

class CollisionVolume
{
	public:
		VolumeType type;
	
	public:
		CollisionVolume(Transform* transform);
		~CollisionVolume();
		
		virtual void getClippingInfo(const Vector2& axis, Side& side, Vector2& sideNormal, std::vector<Line>& cuttingLines) const = 0;
		virtual void getVerticesOnAxis(const Vector2& axis, Vector2& minVertex, Vector2& maxVertex) const = 0;
		virtual void getPossibleCollisionAxes(const CollisionVolume* volumeB, std::vector<Vector2>& possibleCollisionAxes) const = 0;
		
		virtual Vector2 getClosestPoint(const Vector2& point) const = 0;
	
	protected:
		Transform* transform;
};

#endif