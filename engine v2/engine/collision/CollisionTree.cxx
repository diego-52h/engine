#include "CollisionTree.hxx"

#include "Type.hxx"

#include "Math.hxx"
#include "GameNode.hxx"
#include "CollisionVolume.hxx"

CollisionTree::CollisionTree(const Vector2& size, const Int_16 maxDepth, const Int_16 maxItems) : maxItems(maxItems)
{
	this -> tree.resize((Math::pow(4, maxDepth + 1) - 1) / 3);
	
	this -> tree[0].hasSons = false;
	this -> tree[0].boxAABB = {size, {0, 0}};
	
	this -> traverse([this](Int_16 nodeID, Int_16 nextID) -> Bool
	{
		if(nextID == 0)
			return true;
		
		Node& node = tree[nodeID];
		Node& next = tree[nextID];
		
		Int_16 sector = nextID - (4 * nodeID);
		
		Vector2 size = node.boxAABB.getSize() / 2;
		Vector2 position = node.boxAABB.getPosition();
		
		switch(sector)
		{
			case 1: { position = {position.x - size.x, position.y + size.y}; } break;
			case 2: { position = {position.x + size.x, position.y + size.y}; } break;
			case 3: { position = {position.x - size.x, position.y - size.y}; } break;
			case 4: { position = {position.x + size.x, position.y - size.y}; } break;
		}
		
		next.hasSons = false;
		next.boxAABB = {size, position};
		
		return true;
	});
}

void CollisionTree::construct(const Vector<Reference<GameNode>> nodes)
{
	this -> tree[0].items.clear();
	
	for(GameNode& node : nodes)
	{
		for(CollisionVolume& volume : node.getVolumes())
		{
			AABB boxAABB = node.getVolume();
			
			this -> tree[0].items.push_back({boxAABB, volume});
		}
	}
	
	this -> traverse([this](const Int_16 nodeID, const Int_16 nextID) -> Bool
	{
		if(nextID == 0)
			return true;
		
		Node& node = this -> tree[nodeID];
		Node& next = this -> tree[nextID];
		
		if(node.items.size() >= this -> maxItems)
		{
			next.items.clear();
			
			for(const Item& item : node.items)
			{
				if(AABB::intersection(next.boxAABB, item.boxAABB))
					next.items.push_back(item);
			}
			
			node.hasSons = true;
			
			return true;
		}
		
		return false;
	});
}

Vector<Collision> CollisionTree::getCollisions() const
{
	Vector<Collision> collisions;
	
	this -> traverse([this, &collisions](const Int_16 nodeID, const Int_16 nextID) -> Bool
	{
		if(nextID != 0)
			return true;
		
		Node& node = this -> tree[nodeID];
		
		if(node.hasSons)
			return true;
		
		for(Int_16 index1 = 0; index1 < node.items.size(); index1++)
		{
			for(Int_16 index2 = index1; index2 < node.items.size(); index2++)
			{
				const Item& item1 = node.items[index1];
				const Item& item2 = node.items[index2];
				
				if(!AABB::intersection(item1.boxAABB, item2.boxAABB))
					continue;
				
				Collision collision(item1.volume, item2.volume);
				
				if(collision.exists())
					collisions.push_back(collision);
			}
		}
		
		return false;
	});
	
	return collisions;
}

Vector<Collision> CollisionTree::getCollisions(GameNode& node) const
{
	Vector<Item> items;
	Vector<Collision> collisions;
	
	for(CollisionVolume& volume : node.getVolumes())
	{
		AABB boxAABB = node.getVolume();
		
		items.push_back({boxAABB, volume});
	}
	
	this -> traverse([this, &items, &collisions](const Int_16 nodeID, const Int_16 nextID) -> Bool
	{
		if(nextID != 0)
			return true;
		
		Node& node = this -> tree[nodeID];
		
		if(node.hasSons)
			return true;
		
		for(Int_16 index1 = 0; index1 < node.items.size(); index1++)
		{
			for(Int_16 index2 = 0; index2 < items.size(); index2++)
			{
				const Item& item1 = node.items[index1];
				const Item& item2 = items[index2];
				
				if(!AABB::intersection(node.boxAABB, item2.boxAABB))
					continue;
				
				Collision collision = Collision(item1.volume, item2.volume);
				
				if(collision.exists())
					collisions.push_back(collision);
			}
		}
		
		return false;
	});
	
	return collisions;
}

void CollisionTree::traverse(std::function<Bool (const Int_16, const Int_16)> operation)
{
	std::queue<Int_16> remaining;
	
	remaining.push(0);
	
	while(!remaining.empty())
	{
		Int_16 node = remaining.front(); remaining.pop();
		
		if(!operation(node, 0))
			continue;
		
		for(Int_16 i = 1; i <= 4; i++)
		{
			Int_16 next = (4 * node) + i;
			
			if(next >= this -> tree.size())
				continue;
			
			if(!operation(node, next))
				continue;
			
			remaining.push(next);
		}
	}
}