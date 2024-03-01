#ifndef HULL_H
#define HULL_H

#include <vector>

#include "Vector2.h"

struct HullSide
{
	int id;
	int firstVertexId;
	int finalVertexId;
	
	Vector2 normal;
	
	std::vector<int> adjacentSides;
};

struct HullVertex
{
	int id;
	
	Vector2 position;
	
	std::vector<int> enclosingSides;
	
	HullVertex()
	{
	}
	
	HullVertex(int id, Vector2 position)
	{
	}
};

class Hull
{
	public:
		std::vector<HullSide> sides;
		std::vector<HullVertex> vertices;
	
	public:
		Hull();
		~Hull();
		
		int addSide(const Vector2& normal, int firstVertexId, int finalVertexId);
		int addVertex(const Vector2& vertexPosition);
		
		void getMinMaxVerticesOnAxis(const Vector2& axis, int* min, int* max) const;
		
		const HullSide& getSide(int id) const;
		const HullVertex& getVertex(int id) const;
};

#endif