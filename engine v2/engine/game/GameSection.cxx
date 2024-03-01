#include "GameSection.hxx"

void GameSection::update() { this -> root.update(); }

const BaseNode& getRoot() const { return this -> root; }

void GameSection::operateOnStatic(std::function<Bool (StaticNode& node)> operation)
{
	for(StaticNode& node : this -> GameNodes())
	{
		if(node == staticNode)
			operation(node);
	}
}

void GameSection::operateOnActive(std::function<Bool (ActiveNode& node)> operation) { ; }

const Vector<U_Pointer<GameNode>> getNodes() const { return this -> nodes; }