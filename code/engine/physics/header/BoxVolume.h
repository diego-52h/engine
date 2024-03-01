#ifndef BOX_H
#define BOX_H

#include <vector>

#include "Vector2.h"

#include "CollisionVolume.h"
#include "GeometryUtil.h"
#include "Hull.h"

class Transform;

class BoxVolume : public CollisionVolume
{
	public:
		BoxVolume(Transform* transform, const Vector2& halfSizes);
		~BoxVolume();
		
		virtual void getClippingInfo(const Vector2& axis, Side& side, Vector2& sideNormal, std::vector<Line>& cuttingLines) const override;
		virtual void getVerticesOnAxis(const Vector2& axis, Vector2& min, Vector2& max) const override;
		virtual void getPossibleCollisionAxes(const CollisionVolume* volumeB, std::vector<Vector2>& possibleCollisionAxes) const override;
		
		virtual Vector2 getClosestPoint(const Vector2& point) const override;
	
	protected:
		Hull boxHull;
};

#endif