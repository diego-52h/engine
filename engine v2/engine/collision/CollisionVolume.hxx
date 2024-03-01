#ifndef COLLISION_VOLUME_H
#define COLLISION_VOLUME_H

#include "Type.hxx"

#include "Vector2.hxx"
#include "Segment.hxx"

class GameNode;
class Transform;

class CollisionVolume
{
	public:
		GameNode& getParent();
		
		const Transform& getTransform() const;
		
		virtual Vector2 getNearestPoint(const Vector2& point) const = 0;
		virtual Segment getContactSegment(const Vector2& normal, Vector<Segment>& connectedSegments) const = 0;
		
		virtual Vector<Vector2> getCollisionAxes(const CollisionVolume& volumeB) const = 0;
		
		virtual Array<Vector2, 2> getMinMaxOnAxis(const Vector2& axis) const = 0;
	
	private:
		GameNode& parent;
	
	protected:
		CollisionVolume(GameNode& parent);
};

#endif