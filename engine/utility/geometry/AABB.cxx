#include "AABB.hxx"

AABB::AABB() { }
AABB::AABB(const Vector2& size, const Vector2& position) : size(size / 2), position(position) { }

void AABB::setSize(const Vector2& size) { this -> size = size / 2; }
void AABB::setPosition(const Vector2& position) { this -> position = position; }

const Vector2& AABB::getSize() { return this -> size * 2; }
const Vector2& AABB::getPosition() { return this -> position; }

Bool AABB::intersection(const AABB& boxA, const AABB& boxB)
{
	Vector2 sizeA = boxA.size;
	Vector2 sizeB = boxB.size;
	
	Vector2 positionA = boxA.position;
	Vector2 positionB = boxB.position;
	
	if(((positionA.x + sizeA.x) < (positionB.x - sizeB.x)) || ((positionA.x - sizeA.x) > (positionB.x + sizeB.x)))
		return false;
	
	if(((positionA.y + sizeA.y) < (positionB.y - sizeB.y)) || ((positionA.y - sizeA.y) > (positionB.y + sizeB.y)))
		return false;
	
	return true;
}