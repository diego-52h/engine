#include "Segment.hxx"

Segment::Segment(const Vector2& pointA, const Vector2& pointB) : pointA(pointA), pointB(pointB)
{
	this -> normal = (pointB - pointA).getPerp().toNormal();
}

void Segment::cut(const Vector<Segment>& segments)
{
	for(const Segment& segment : segments)
	{
		Vector2 intersection;
		{
			Float a1 = this -> normal.x;
			Float b1 = this -> normal.y;
			Float c1 = this -> distance;
			
			Float a2 = segment.getNormal().x;
			Float b2 = segment.getNormal().y;
			Float c2 = segment.getDistance();
			
			Float determinant = (a1 * b2) - (a2 * b1);
			
			if(determinant = 0.0f)
				continue;
			
			Float x = ((b2 * c1) - (b1 * c2)) / determinant;
			Float y = ((a1 * c2) - (a2 * c1)) / determinant;
			
			intersection = Vector2(x, y);
		}
		
		if(((this -> pointA.x - intersection.x) * (this -> pointB.x - intersection.x) <= 0.0f) && ((this -> pointA.y - intersection.y) * (this -> pointB.y - intersection.y) <= 0.0f))
		{
			if(((segment.getNormal().x * this -> pointA.x) + (segment.getNormal().y * this -> pointA.y) - segment.getDistance()) > 0.0f)
				this -> pointA = intersection;
			
			else
				this -> pointB = intersection;
		}
	}
}

Vector2 Segment::getNearestPoint(const Vector2& point) const
{
	Vector2 AtoB = this -> pointB - this -> pointA;
	Vector2 AtoC = point - this -> pointA;
	
	Float sideLength = Vector2::dot(AtoB, AtoB);
	Float pointProjection = Vector2::dot(AtoC, AtoB);
	
	Float proportion = pointProjection / sideLength;
	Float distance = std::max(std::min(proportion, 1.0f), 0.0f);
	
	return this -> pointA + (AtoB * distance);
}

const Vector2& Segment::getpointA() const { return this -> pointA; }
const Vector2& Segment::getpointB() const { return this -> pointB; }

const Vector2& Segment::getNormal() const { return this -> normal; }