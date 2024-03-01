#ifndef CAMERA_H
#define CAMERA_H

#include "Transform.h"

class Camera
{
	public:
		Camera();
		~Camera();
		
		void setTransform(Transform& transform);
		
		void update(float dt);
		
		Transform& getTransform();
		
		const Transform& getTransform() const;
	
	protected:
		Transform transform;
};

#endif