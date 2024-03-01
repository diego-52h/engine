#include <cmath>

#include <assert.h>

#include "Transform.h"

Transform::Transform()
{
	this -> parent = nullptr;
	
	this -> setWorldOrientation(0.0f);
	
	this -> setWorldScale(Vector2(1, 1));
	this -> setWorldPosition(Vector2(0, 0));
}

Transform::~Transform()
{
}

void Transform::updateMatrices()
{
	this -> localTransform = Matrix3::translationMatrix(this -> localPosition) * Matrix3::scalingMatrix(this -> localScale) * Matrix3::rotationMatrix(this -> localOrientation);
	
	if(this -> parent != nullptr)
		this -> worldTransform = this -> parent -> getWorldTransform() * this -> localTransform;
	
	else
		this -> worldTransform = this -> localTransform;
}

void Transform::setLocalOrientation(float orientation)
{
	this -> localOrientation = orientation;
}

void Transform::setWorldOrientation(float orientation)
{
	if(this -> parent != nullptr)
		this -> localOrientation = this -> parent -> getLocalOrientation() - orientation;
	
	else
		this -> localOrientation = orientation;
}

void Transform::setLocalScale(const Vector2& scale)
{
	assert((scale.x > 0) && (scale.y > 0));
	
	this -> localScale = scale;
}

void Transform::setWorldScale(const Vector2& scale)
{
	assert((scale.x > 0) && (scale.y > 0));
	
	if(this -> parent != nullptr)
		this -> localScale = scale / this -> parent -> getLocalScale();
	
	else
		this -> localScale = scale;
}

void Transform::setLocalPosition(const Vector2& position)
{
	this -> localPosition = position;
}

void Transform::setWorldPosition(const Vector2& position)
{
	if(this -> parent != nullptr)
		this -> localPosition = this -> parent -> getLocalPosition() - position;
	
	else
		this -> localPosition = position;
}

void Transform::setParentTransform(const Vector2& localPosition, Transform* parent)
{
	this -> parent = parent;
	
	this -> setLocalOrientation(0.0f);
	
	this -> setLocalScale(Vector2(1, 1));
	this -> setLocalPosition(localPosition);
}

float Transform::getLocalOrientation() const
{
	return this -> localOrientation;
}

float Transform::getWorldOrientation() const
{
	return Transform::getOrientation(this -> worldTransform);
}

Vector2 Transform::getLocalScale() const
{
	return this -> localScale;
}

Vector2 Transform::getWorldScale() const
{
	return Transform::getScale(this -> worldTransform);
}

Vector2 Transform::getLocalPosition() const
{
	return this -> localPosition;
}

Vector2 Transform::getWorldPosition() const
{
	return Transform::getPosition(this -> worldTransform);
}

Matrix3 Transform::getLocalTransform() const
{
	return this -> localTransform;
}

Matrix3 Transform::getWorldTransform() const
{
	return this -> worldTransform;
}

float Transform::getOrientation(const Matrix3& transform)
{
	Vector2 scale = Transform::getScale(transform);
	
	float orientation1 = transform.values[0][1] / scale.y;
	float orientation2 = transform.values[0][0] / scale.x;
	
	return std::atan2(orientation1, orientation2);
}

Vector2 Transform::getScale(const Matrix3& transform)
{
	float scaleX = Vector2(transform.values[0][0], transform.values[1][0]).getLength();
	float scaleY = Vector2(transform.values[0][1], transform.values[1][1]).getLength();
	
	return Vector2(scaleX, scaleY);
}

Vector2 Transform::getPosition(const Matrix3& transform)
{
	return Vector2(transform.values[0][2], transform.values[1][2]);
}