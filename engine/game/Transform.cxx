#include "Transform.hxx"

Transform::Transform() : changed(true) { }

void Transform::update(const Transform& parent)
{
	this -> changed = false;
	
	this -> transform = Matrix3::translation(this -> position) * Matrix3::scalation(this -> scale) * Matrix3::rotation(this -> orientation);
	this -> transform *= parent.getTransform();
}

void Transform::setOrientation(const Float orientation)
{
	this -> changed = true;
	this -> orientation = orientation;
}

void Transform::setScale(const Vector2& scale)
{
	this -> changed = true;
	this -> scale = scale;
}

void Transform::setPosition(const Vector2& position)
{
	this -> changed = true;
	this -> position = position;
}

Bool Transform::changed() const { return this -> changed; }

Float Transform::getOrientation() const { return this -> orientation; }

const Vector2& Transform::getScale() const { return this -> scale; }
const Vector2& Transform::getPosition() const { return this -> position; }

const Matrix3& Transform::getMatrix() const { return this -> matrix; }