#include "GameNode.hxx"

/* ---------- */

const Transform& Node::getTransform() const { return this -> transform; }

const Vector<Camera> Node::getCameras() const { return this -> cameras; }
const Vector<Reference<GameNode>> Node::getSons() const { return this -> sons; }

Node::Node(const Transform& transform) : transform(transform) { }

void Node::appendSon(GameNode& son) { }
void Node::removeSon(GameNode& son) { }

/* ---------- */

BaseNode::BaseNode() : Node(Transform())
{
	this -> cameras.push_back(Camera(*this));
}

/* ---------- */

GameNode::~GameNode()
{
	this -> parent.removeSon(*this);
}

void GameNode::update(const Bool parentChanged)
{
	Bool change = parentChanged;
}

void GameNode::setGraphicsComponent(U_Pointer<GraphicsComponent> grpahicsComponent) { this -> graphicsComponent = graphicsComponent; }
void GameNode::setDynamicsComponent(U_Pointer<DynamicsComponent> dynamicsComponent) { this -> dynamicsComponent = dynamicsComponent; }

const AABB GameNode::getVolume() const { return this -> volume; }

const String& GameNode::getName() const { return this -> name; }

GraphicsComponent* GameNode::getGraphicsComponent() { return this -> graphicsComponent; }
DynamicsComponent* GameNode::getDynamicsComponent() { return this -> dynamicsComponent; }

Vector<CollisionVolume>& GameNode::getVolumes() { return this -> volumes; }

GameNode::GameNode(const Transform& transform, Node& parent, const String& name) : Node(transform), parent(parent), name(name)
{
	this -> parent.appendSon(*this);
}

/* ---------- */

StaticNode::StaticNode(const Transform& transform, Node& parent, const String& name) : GameNode(transform, parent, name) { }

/* ---------- */

ActiveNode::ActiveNode(const Transform& transform, Node& parent, const String& name) : GameNode(transform, parent, name) { }

void ActiveNode::setParent(Node& parent)
{
	this -> parent.removeSon(*this);
	
	this -> parent = parent;
	
	this -> parent.appendSon(*this);
}

Transform& ActiveNode::getTransform() { return this -> transform; }