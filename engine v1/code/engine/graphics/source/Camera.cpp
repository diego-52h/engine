#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::setTransform(Transform& transform)
{
	this -> transform = transform;
}

void Camera::update(float dt)
{
	this -> transform.updateMatrices();
}

Transform& Camera::getTransform()
{
	return this -> transform;
}

const Transform& Camera::getTransform() const
{
	return this -> transform;
}