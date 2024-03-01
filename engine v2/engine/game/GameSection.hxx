#ifndef GAME_SECTION_H
#define GAME_SECTION_H

#include "Type.h"

class GameSection
{
	public:
		GameSection(const Float w, const Float h);
		
		void update();
		
		void removeNode(const UInt16 ID);
		void appendNode(U_Pointer<GameNode> node);
		
		void operateOnStatic(std::function<Bool (StaticNode& node)> operation);
		void operateOnActive(std::function<Bool (ActiveNode& node)> operation);
		
		const BaseNode& getRoot() const;
		const GameNode& getNode(const UInt16 ID) const;
	
	private:
		Vector2 size;
		
		BaseNode root;
		
		Queue<UInt16> IDs;
		
		Vector<StaticNode&> staticNodes;
		Vector<ActiveNode&> activeNodes;
		
		Vector<U_Pointer<GameNode>> nodes;
};

#endif