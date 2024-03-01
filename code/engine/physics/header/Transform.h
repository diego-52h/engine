#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Matrix2.h"
#include "Matrix3.h"
#include "Vector2.h"

class Transform
{
	public:
		Transform();
		~Transform();
		
		void updateMatrices();
		
		void setLocalOrientation(float orientation);
		void setWorldOrientation(float orientation);
		
		void setLocalScale(const Vector2& scale);
		void setWorldScale(const Vector2& scale);
		
		void setLocalPosition(const Vector2& position);
		void setWorldPosition(const Vector2& position);
		
		void setParentTransform(const Vector2& localPosition, Transform* parent);
		
		float getLocalOrientation() const;
		float getWorldOrientation() const;
		
		Vector2 getLocalScale() const;
		Vector2 getWorldScale() const;
		
		Vector2 getLocalPosition() const;
		Vector2 getWorldPosition() const;
		
		Matrix3 getLocalTransform() const;
		Matrix3 getWorldTransform() const;
		
		static float getOrientation(const Matrix3& transform);
		
		static Vector2 getScale(const Matrix3& transform);
		static Vector2 getPosition(const Matrix3& transform);
	
	private:
		float localOrientation;
		
		Vector2 localScale;
		Vector2 localPosition;
		
		Matrix3 localTransform;
		Matrix3 worldTransform;
		
		Transform* parent;
};

#endif