#ifndef AABB_H
#define AABB_H

#include "Vector2.hxx"

class AABB
{
	public:
		AABB();
		AABB(const Vector2& size, const Vector2& position);
		
		void setSize(const Vector2& size);
		void setPosition(const Vector2& position);
		
		const Vector2& getSize() const;
		const Vector2& getPosition() const;
		
		static Bool intersection(const AABB& AABB1, const AABB& AABB2);
	
	private:
		Vector2 size;
		Vector2 position;
};

#endif