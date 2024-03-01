#include "Polygon.hxx"

/* ---------- */

Vertex::Vertex(const Int_16 ID, const Vector2& position) : ID(ID), position(position) { }

const Vector2& Vertex::getPosition() const { return this -> position; }

/* ---------- */

Side::Side(const Int_16 ID, const Vertex& vertexA, const Vertex& vertexB) : ID(ID), vertexA(vertexA), vertexB(vertex)
{
	Vector2 position1 = this -> vertexA.getPosition();
	Vector2 position2 = this -> vertexB.getPosition();
	
	this -> normal = (position2 - position1).getPerp().toNormal();
}

const Vertex& Side::getVertexA() const { return this -> vertexA; }
const Vertex& Side::getVertexB() const { return this -> vertexB; }

const Vector2& Side::getNormal() const { return this -> normal; }

/* ---------- */

Polygon::Polygon(const Vector<Vector2>& vertices) : sideCount(vertices.size())
{
	for(Int_16 ID = 0; ID < this -> sideCount; ID++)
		this -> vertices.push_back(Vertex(ID, vertices[ID]));
	
	for(Int_16 ID = 0; ID < this -> sideCount; ID++)
	{
		const Vertex& vertexA = this -> vertices[ID];
		const Vertex& vertexB = this -> vertices[this -> getNextID(ID)];
		
		this -> sides.push_back(Side(ID, vertexA, vertexB));
	}
	
	// Check if polygon is valid (not self intersecting and convex)
}

Vector<Reference<const Side>> Polygon::getConnectedSides(const Side& side) const
{
	const Side& side1 = this -> sides[this -> getPrevID(side.ID)];
	const Side& side2 = this -> sides[this -> getNextID(side.ID)];
	
	return {side1, side2};
}

Vector<Reference<const Side>> Polygon::getConnectedSides(const Vertex& vertex) const
{
	const Side& side1 = this -> sides[this -> getPrevID(vertex.ID)];
	const Side& side2 = this -> sides[vertex.ID];
	
	return {side1, side2};
}

Array<Reference<const Vertex>, 2> Polygon::getMinMaxOnAxis(const Vector2& axis) const
{
	Float minProjection = +Math::INF;
	Float maxProjection = -Math::INF;
	
	Vertex* minVertex;
	Vertex* maxVertex;
	
	for(const Vertex& vertex : this -> vertices)
	{
		Float newProjection = Vector2::dotProduct(axis, vertex.getPosition());
		
		if(newProjection < minProjection)
		{
			minVertex = vertex;
			
			minProjection = newProjection;
		}
		
		if(newProjection > maxProjection)
		{
			maxVertex = vertex;
			
			maxProjection = newProjection;
		}
	}
	
	assert((minVertex != nullptr) && (maxVertex != nullptr));
	
	return {*minVertex, *maxVertex};
}

const Vector<Side>& Polygon::getSides() const { return this -> sides; }

Int_16 Polygon::getPrevID(const Int_16 ID) { return ((ID - 1) + this -> sideCount) % this -> sideCount; }
Int_16 Polygon::getNextID(const Int_16 ID) { return ((ID + 1) % this -> sideCount); }