#include "Collision.hxx"

#include "Math.hxx"

#include "GameNode.hxx"
#include "CollisionVolume.hxx"

Collision::Collision(CollisionVolume& volumeA, CollisionVolume& volumeB) : volumeA(volumeA), volumeB(volumeB)
{
	Vector<Vector2> axes;
	{
		Vector<Vector2> axesA = this -> volumeA.getCollisionAxes(volumeB);
		Vector<Vector2> axesB = this -> volumeB.getCollisionAxes(volumeA);
		
		axes.insert(std::end(axes), std::begin(axesA), std::end(axesA));
		axes.insert(std::end(axes), std::begin(axesB), std::end(axesB));
	}
	
	Vector<Vector2> collisionAxes;
	
	for(const Vector2& axis : axes)
	{
		if(axis.getLen() < Math::EPS)
			continue;
		
		for(const Vector2& collisionAxis : collisionAxes)
		{
			if(Vector2::dot(collisionAxis, axis.getNorm()) >= (1.0f - Math::EPS))
				goto REPEATED;
		}
		
		collisionAxes.push_back(axis.getNorm());
		
		REPEATED: {}
	}
	
	this -> distance = 0.0f;
	
	for(const Vector2& axis : collisionAxes)
	{
		const auto& [minA, maxA] = this -> volumeA.getMinMaxOnAxis(axis);
		const auto& [minB, maxB] = this -> volumeB.getMinMaxOnAxis(axis);
		
		Float pointA = Vector2::dot(axis, minA);
		Float pointB = Vector2::dot(axis, maxA);
		Float pointC = Vector2::dot(axis, minB);
		Float pointD = Vector2::dot(axis, maxB);
		
		if((pointA <= pointC) && (pointC < pointB))
		{
			Float distance = pointC - pointB;
			
			if(distance > this -> distance)
			{
				this -> distance = distance;
				
				this -> normal = +axis;
			}
		}
		
		if((pointC <= pointA) && (pointA < pointD))
		{
			Float distance = pointA - pointD;
			
			if(distance > this -> distance)
			{
				this -> distance = distance;
				
				this -> normal = -axis;
			}
		}
		
		if(this -> distance == 0.0f)
			return;
	}
}

Bool Collision::exists() const { return this -> distance > 0.0f; }

Float Collision::getDistance() const { return this -> distance; }

const Vector2& Collision::getNormal() const { return this -> normal; }

CollisionVolume& Collision::getVolumeA() { return this -> volumeA; }
CollisionVolume& Collision::getVolumeB() { return this -> volumeB; }