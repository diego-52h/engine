#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <vector>

class GameObject;
class World;

class Manifold;

struct CollisionPair
{
	GameObject* objectA;
	GameObject* objectB;
};

class PhysicsEngine
{
	public:
		PhysicsEngine();
		~PhysicsEngine();
		
		void setWorld(World* world);
		
		void update(float dt);
	
	protected:
		float timeOffset;
		
		World* world;
		
		std::vector<Manifold*> manifolds;
		std::vector<CollisionPair> broadPhaseCollisions;
	
	protected:
		void broadPhase();
		void narrowPhase();
		
		void clearForces();
		
		void integrateForPosition(float dt);
		void integrateForVelocity(float dt);
};

#endif