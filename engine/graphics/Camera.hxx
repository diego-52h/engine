#ifndef CAMERA_H
#define CAMERA_H

#include "Transform.hxx"

class Node;

class Camera
{
	public:
		Camera(Node& parent);
		
		Transform& getTransform();
	
	private:
		Node& parent;
		
		Transform transform;
};

#endif