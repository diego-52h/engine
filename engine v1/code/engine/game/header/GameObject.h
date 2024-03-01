#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <memory>

#include "Transform.h"

class World;
class PhysicsObject;
class GraphicsObject;

class GameObject
{
	public:
		GameObject(World* world);
		~GameObject();
		
		Transform& getTransform();
		
		PhysicsObject* getPhysicsObject() const;
		GraphicsObject* getGraphicsObject() const;
		
		const Transform& getTransform() const;
		
		virtual void update(float dt);
		virtual void onAnimationAdvanced(const std::string& animation) {}
		virtual void onAnimationFinished(const std::string& animation) {}
		
		virtual bool onCollision(GameObject* objectB) { return true; }
	
	protected:
		Transform transform;
		
		World* world;
		
		PhysicsObject* physicsObject;
		GraphicsObject* graphicsObject;
};

#endif