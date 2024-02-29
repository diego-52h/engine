#ifndef POLYGON_H
#define POLYGON_H

#include "Type.hxx"

class Vertex
{
	friend class Polygon;
	
	public:
		const Vector2& getPosition() const;
	
	private:
		Int_16 ID;
		
		Vector2 position;
	
	private:
		Vertex(const Int_16 ID, const Vector2& position);
};

class Side
{
	friend class Polygon;
	
	public:
		const Vertex& getVertexA() const;
		const Vertex& getVertexB() const;
		
		const Vector2& getNormal() const;
	
	private:
		Int_16 ID;
		
		Vector2 normal;
		
		const Vertex& vertexA;
		const Vertex& vertexB;
	
	private:
		Side(const Int_16 ID, const Vertex& vertexA, const Vertex& vertexB);
};

class Polygon
{
	public:
		Polygon(const Vector<Vector2>& vertices);
		
		Vector<Reference<const Side>> getConnectedSides(const Side& side) const;
		Vector<Reference<const Side>> getConnectedSides(const Vertex& vertex) const;
		
		Array<Reference<const Vertex>, 2> getMinMaxOnAxis(const Vector2& axis) const;
		
		const Vector<Side>& getSides() const;
	
	private:
		Int_16 sideCount;
		
		Vector<Side> sides;
		Vector<Vertex> vertices;
	
	private:
		Int_16 getPrevID(const Int_16 ID);
		Int_16 getNextID(const Int_16 ID);
};

#endif