#ifndef SEGMENT_H
#define SEGMENT_H

class Segment
{
	public:
		Segment(const Vector2& pointA, const Vector2& pointB);
		
		void cut(const Vector<Segment>& segments);
		
		Vector2 getNearestPoint(const Vector2& point) const;
		
		const Vector2& getPointA() const;
		const Vector2& getPointB() const;
		
		const Vector2& getNormal() const;
	
	private:
		Vector2 pointA;
		Vector2 pointB;
		
		Vector2 normal;
};

#endif