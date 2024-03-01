#include <float.h>
#include <assert.h>

#include "Hull.h"

Hull::Hull()
{
}

Hull::~Hull()
{
}

int Hull::addSide(const Vector2& normal, int firstVertexId, int finalVertexId)
{
	HullSide newSide;
	
	newSide.id = this -> sides.size();
	newSide.firstVertexId = firstVertexId;
	newSide.finalVertexId = finalVertexId;
	
	newSide.normal = normal;
	
	for(HullSide& currSide : this -> sides)
	{
		if((newSide.firstVertexId == currSide.firstVertexId) || (newSide.firstVertexId == currSide.finalVertexId) || (newSide.finalVertexId == currSide.firstVertexId) || (newSide.finalVertexId == currSide.finalVertexId))
		{
			newSide.adjacentSides.push_back(newSide.id);
			currSide.adjacentSides.push_back(currSide.id);
		}
	}
	
	this -> vertices[firstVertexId].enclosingSides.push_back(newSide.id);
	this -> vertices[finalVertexId].enclosingSides.push_back(newSide.id);
	
	this -> sides.push_back(newSide);
	
	return newSide.id;
}

int Hull::addVertex(const Vector2& position)
{
	HullVertex newVertex;
	
	newVertex.id = this -> vertices.size();
	newVertex.position = position;
	
	this -> vertices.push_back(newVertex);
	
	return newVertex.id;
}

void Hull::getMinMaxVerticesOnAxis(const Vector2& axis, int* min, int* max) const
{
	int minVertex;
	int maxVertex;
	
	float projection;
	
	float minProjection = FLT_MAX;
	float maxProjection = -FLT_MAX;
	
	for(const HullVertex& vertex : this -> vertices)
	{
		projection = Vector2::dotProduct(axis, vertex.position);
		
		if(projection < minProjection)
		{
			minVertex = vertex.id;
			minProjection = projection;
		}
		
		if(projection > maxProjection)
		{
			maxVertex = vertex.id;
			maxProjection = projection;
		}
	}
	
	if(min != nullptr)
		*min = minVertex;
	
	if(max != nullptr)
		*max = maxVertex;
}

const HullSide& Hull::getSide(int id) const
{
	assert((id >= 0) && (id < this -> sides.size()));
	
	return this -> sides[id];
}

const HullVertex& Hull::getVertex(int id) const
{
	assert((id >= 0) && (id < this -> vertices.size()));
	
	return this -> vertices[id];
}