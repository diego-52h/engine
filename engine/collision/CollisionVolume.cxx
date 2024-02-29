#include "CollisionVolume.hxx"

GameNode& CollisionVolume::getParent() { return this -> parent; }

const Transform& CollisionVolume::getTransform() const { return this -> parent.getTransform(); }

CollisionVolume::CollisionVolume(const Transform& transform, const Vector2& maxSize) : transform(transform), maxSize(maxSize) { }