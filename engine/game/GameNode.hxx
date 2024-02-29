#ifndef GAME_NODE_H
#define GAME_NODE_H

#include "Type.hxx"

#include "AABB.hxx"
#include "Camera.hxx"
#include "Transform.hxx"

class GameNode;
class GameSection;

class StaticNode;
class ActiveNode;

class GraphicsComponent;
class DynamicsComponent;

class Node
{
	public:
		const Transform& getTransform() const;
		
		const Vector<Camera> getCameras() const;
		const Vector<Reference<GameNode>> getSons() const;
	
	private:
		Transform transform;
		
		Vector<Camera> cameras;
		Vector<Reference<GameNode>> sons;
	
	protected:
		Node(const Transform& transform);
		
		void appendSon(GameNode& son);
		void removeSon(GameNode& son);
};

class BaseNode : public Node
{
	friend class GameSection;
	
	public:
		void update();
	
	private:
		BaseNode();
};

class GameNode : public Node
{
	public:
		~GameNode();
		
		virtual void update(const Bool parentChanged);
		
		void setGraphicsComponent(U_Pointer<GraphicsComponent> graphicsComponent);
		void setDynamicsComponent(U_Pointer<DynamicsComponent> dynamicsComponent);
		
		const Int_16 getID() const;
		
		const AABB getVolume() const;
		
		GraphicsComponent* getGraphicsComponent();
		DynamicsComponent* getDynamicsComponent();
		
		Vector<U_Pointer<CollisionVolume>>& getVolumes();
	
	private:
		Node& parent;
		
		Int_16 ID;
		
		AABB volume;
		
		U_Pointer<GraphicsComponent> graphicsComponent;
		U_Pointer<DynamicsComponent> dynamicsComponent;
		
		Vector<U_Pointer<CollisionVolume>> volumes;
	
	protected:
		GameNode(const Transform& transform, Node& parent, const String& name);
};

class StaticNode : public GameNode
{
	public:
		StaticNode(const Transform& transform, Node& parent, const String& name);
		
		StaticNode(const Transform& transform, ActiveNode& parent, const String& name) = delete;
};

class ActiveNode : public GameNode
{
	public:
		ActiveNode(const Transform& transform, Node& parent, const String& name);
		
		void setParent(Node& parent);
		
		Transform& getTransform();
};

#endif