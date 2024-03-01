#include "Camera.hxx"

Camera::Camera(Node& parent) : parent(parent) { }

Transform& Camera::getTransform() { return this -> transform; }