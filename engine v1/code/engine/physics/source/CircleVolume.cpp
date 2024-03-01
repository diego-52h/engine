#include "CircleVolume.h"
#include "Transform.h"

CircleVolume::CircleVolume(Transform* transform, float radius) : CollisionVolume(transform)
{
	this -> type = VolumeType::CIRCLE;
	
	this -> radius = radius;
}

CircleVolume::~CircleVolume()
{
}

float CircleVolume::getRadius() const
{
	return this -> radius;
}

void CircleVolume::getClippingInfo(const Vector2& axis, Side& side, Vector2& sideNormal, std::vector<Line>& cuttingLines) const
{
	side = Side(this -> transform -> getWorldPosition() + (axis * this -> radius));
	
	sideNormal = axis;
}

void CircleVolume::getVerticesOnAxis(const Vector2& axis, Vector2& min, Vector2& max) const
{
	min = this -> transform -> getWorldPosition() - (axis * (this -> transform -> getWorldScale() * this -> radius));
	max = this -> transform -> getWorldPosition() + (axis * (this -> transform -> getWorldScale() * this -> radius));
}

void CircleVolume::getPossibleCollisionAxes(const CollisionVolume* volumeB, std::vector<Vector2>& possibleCollisionAxes) const
{
	Vector2 pointA = this -> transform -> getWorldPosition();
	Vector2 pointB = volumeB -> getClosestPoint(pointA);
	
	possibleCollisionAxes.push_back((pointA - pointB).getNormalised());
}

Vector2 CircleVolume::getClosestPoint(const Vector2& point) const
{
	Vector2 position = this -> transform -> getWorldPosition();
	
	Vector2 direction = (point - position).getNormalised();
	Vector2 closestPoint = position + (direction * this -> radius);
	
	return closestPoint;
}