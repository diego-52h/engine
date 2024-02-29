#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "CollisionVolume.hxx"

#include "Matrix3.hxx"
#include "Polygon.hxx"

class CollisionBox : public CollisionVolume
{
	public:
		CollisionBox(GameNode& parent, const Vector2& size);
		
		Vector2 getNearestPoint(const Vector2& point) const;
		Segment getContactSegment(const Vector2& normal, Vector<Segment>& connectedSegments) const;
		
		Vector<Vector2> getCollisionAxes(const CollisionVolume& volumeB) const;
		
		Array<Vector2, 2> getMinMaxOnAxis(const Vector2& axis) const;
	
	private:
		Matrix3 scalation;
		
		static Polygon box;
};

Polygon CollisionBox::box = Polygon({{-0.5f, 0.5f}, {0.5f, 0.5f}, {0.5f, -0.5f}, {-0.5f, -0.5f}});

#endif