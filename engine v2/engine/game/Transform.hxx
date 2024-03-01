#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Matrix3.hxx"

class Transform
{
	public:
		Transform();
		
		void update(const Transform& parent);
		
		void setOrientation(const Float orientation);
		
		void setScale(const Vector2& scale);
		void setPosition(const Vector2& position);
		
		Bool hasChanged() const;
		
		Float getOrientation() const;
		
		const Vector2& getScale() const;
		const Vector2& getPosition() const;
		
		const Matrix3& getMatrix() const;
	
	private:
		Bool changed;
		
		Float orientation;
		
		Vector2 scale;
		Vector2 position;
		
		Matrix3 matrix;
};

#endif