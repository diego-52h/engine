#ifndef COLLISION_TREE_H
#define COLLISION_TREE_H

#include "Type.hxx"

#include "AABB.hxx"
#include "Collision.hxx"

class Vector2;
class GameNode;
class CollisionVolume;

class CollisionTree
{
	public:
		CollisionTree(const Vector2& size, const Int_16 maxItems, const Int_16 maxDepth);
		
		void construct(const Vector<Reference<GameNode>> nodes);
		
		Vector<Collision> getCollisions() const;
		Vector<Collision> getCollisions(GameNode& node) const;
	
	private:
		struct Item
		{
			AABB boxAABB;
			
			CollisionVolume& volume;
		};
		
		struct Node
		{
			AABB boxAABB;
			
			Bool hasSons;
			
			Vector<Item> items;
		};
		
		Int_16 maxItems;
		
		Vector<Node> tree;
	
	private:
		void traverse(std::function<Bool (const Int_16, const Int_16)> operation) const;
};

#endif