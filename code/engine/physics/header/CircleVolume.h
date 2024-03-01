#ifndef CIRCLE_VOLUME_H
#define CIRCLE_VOLUME_H

#include <vector>

#include "Vector2.h"

#include "CollisionVolume.h"
#include "GeometryUtil.h"

class Transform;

class CircleVolume : public CollisionVolume
{
	public:
		CircleVolume(Transform* transform, float radius);
		~CircleVolume();
		
		float getRadius() const;
		
		virtual void getClippingInfo(const Vector2& axis, Side& side, Vector2& sideNormal, std::vector<Line>& cuttingLines) const override;
		virtual void getVerticesOnAxis(const Vector2& axis, Vector2& min, Vector2& max) const override;
		virtual void getPossibleCollisionAxes(const CollisionVolume* volumeB, std::vector<Vector2>& possibleCollisionAxes) const override;
		
		virtual Vector2 getClosestPoint(const Vector2& point) const override;
	
	protected:
		float radius;
};

#endif