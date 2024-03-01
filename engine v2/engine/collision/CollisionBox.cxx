#include "CollisionBox.hxx"

#include <cassert>

#include "Math.hxx"
#include "GameNode.hxx"

CollisionBox::CollisionBox(GameNode& parent, const Vector2& size) : CollisionVolume(parent)
{
	this -> scalation = Matrix3::scalation(size);
}

Vector2 CollisionBox::getNearestPoint(const Vector2& point) const
{
	Matrix3 sclTransform = this -> getTransform().getMatrix() * this -> scalation;
	Matrix3 invTransform = sclTransform.getInverse();
	
	Vector2 localPoint = invTransform * point;
	
	Float newDistance = 0.0f;
	Float minDistance = Math::INF;
	
	Vector2 newPoint;
	Vector2 minPoint;
	
	for(const Side& side : CollisionBox::box.getSides())
	{
		const Vector2& pointA = side.getVertexA().getPosition();
		const Vector2& pointB = side.getVertexB().getPosition();
		
		newPoint = Segment(pointA, pointB).getNearestPoint(localPoint);
		newDistance = Vector2::dot(newPoint - localPoint, newPoint - localPoint);
		
		if(newDistance < minDistance)
		{
			minPoint = newPoint;
			
			minDistance = newDistance;
		}
	}
	
	return sclTransform * minPoint;
}

Segment CollisionBox::getContactSegment(const Vector2& normal, Vector<Segment>& connectedSegments) const
{
	Matrix3 sclTransform = this -> getTransform().getMatrix() * this -> scalation;
	Matrix2 invTransform = sclTransform.getMatrix2().getInverse();
	
	Vector2 localNormal = (invTransform * normal).getNorm();
	
	auto [minVertex, maxVertex] = CollisionBox::box.getMinMaxOnAxis(localNormal);
	
	const Side* bestSide;
	
	Float newProjection = 0.0f;
	Float maxProjection = -Math::INF;
	
	for(const Side& side : CollisionBox::box.getConnectedSides(maxVertex))
	{
		newProjection = Vector2::dot(localNormal, side.getNormal());
		
		if(newProjection > maxProjection)
		{
			bestSide = &side;
			
			maxProjection = newProjection;
		}
	}
	
	assert(bestSide != nullptr);
	
	Vector2 pointA;
	Vector2 pointB;
	
	for(const Side& side : CollisionBox::box.getConnectedSides(*bestSide))
	{
		pointA = sclTransform * (side.getVertexA().getPosition());
		pointB = sclTransform * (side.getVertexB().getPosition());
		
		connectedSegments.push_back(Segment(pointA, pointB));
	}
	
	pointA = sclTransform * (*bestSide).getVertexA().getPosition();
	pointB = sclTransform * (*bestSide).getVertexB().getPosition();
	
	return Segment(pointA, pointB);
}

Vector<Vector2> CollisionBox::getCollisionAxes(const CollisionVolume& volumeB) const
{
	Matrix2 rotation = Matrix2::rotation(this -> getTransform().getMatrix().getOrientation());
	
	return {rotation * Vector2(1.0f, 0.0f), rotation * Vector2(0.0f, 1.0f)};
}

Array<Vector2, 2> CollisionBox::getMinMaxOnAxis(const Vector2& axis) const
{
	Matrix3 sclTransform = this -> getTransform().getMatrix() * this -> scalation;
	Matrix2 invTransform = sclTransform.getMatrix2().getInverse();
	
	Vector2 localAxis = (invTransform * axis).getNorm();
	
	auto [minVertex, maxVertex] = CollisionBox::box.getMinMaxOnAxis(localAxis);
	
	Vector2 minPoint = sclTransform * minVertex.get().getPosition();
	Vector2 maxPoint = sclTransform * maxVertex.get().getPosition();
	
	return {minPoint, maxPoint};
}