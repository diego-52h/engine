#include "DynamicsEngine.hxx"

DynamicsEngine::DynamicsEngine(GameSection& section) : section(section)
{
	this -> setSection(section);
}

void DynamicsEngine::setSection(GameSection& section)
{
	this -> section = section;
	
	this -> staticTree = CollisionTree(this -> section.size, 1, 1);
	this -> activeTree = CollisionTree(this -> section.size, 1, 1);
	
	this -> staticTree.construct(this -> section.getStaticNodes());
}

void DynamicsEngine::update(const Int_16 dt)
{
	this -> createConstraints();
	
	for(Constraint& constraint : this -> constraints)
		constraint.update();
	
	this -> integrateForVelocity(dt);
	
	for(Constraint& constraint : this -> constraints)
		constraint.solve();
	
	this -> integrateForPosition(dt);
}

void DynamicsEngine::createConstraints()
{
	this -> activeTree.construct(this -> section.getActiveNodes());
	
	for(const Collision& collision : activeTree.getCollisions())
	{
		ContactConstraint constraint(collision);
		
		if(constraint.exists())
		{
			Bool solveCollisionA = ;
			Bool solveCollisionB = ;
			
			if(solveCollisionA && solveCollisionB)
				this -> constraints.push_back(constraint);
		}
	}
	
	for(const GameNode& node : this -> section.getActiveNodes())
	{
		for(const Collision& collision : staticTree.getCollisions(node))
		{
			ContactConstraint constraint(collision);
			
			if(constraint.exists())
			{
				Bool solveCollisionA = ;
				Bool solveCollisionB = ;
				
				if(solveCollisionA && solveCollisionB)
					this -> constraints.push_back(constraint);
			}
		}
	}
}

void DynamicsEngine::integrateForPosition(const Int_16 dt)
{
	for(const ActiveNode& node : this -> section.getActiveNodes())
	{
		if(node.getDynamicsComponent() == nullptr)
			continue;
		
		DynamicsComponent& dynamicsComponent = *node.getDynamicsComponent();
		
		Transform& transform = node.getTransform();
		
		Float seconds = Math::toSeconds(dt);
		
		Vector2 position = transform.getPosition();
		Vector2 linVelocity = dynamicsComponent.getLinearVelocity();
		
		transform.setPosition(position + (linVelocity * seconds));
		
		Float orientation = transform.getOrientation();
		Float angVelocity = dynamicsComponent.getAngularVelocity();
		
		transform.setOrientation(orientation + (angVelocity * seconds));
	}
}

void DynamicsEngine::integrateForVelocity(const Int_16 dt)
{
	for(const GameNode& node : this -> section.getNodes())
	{
		if(node.getDynamicsComponent() == nullptr)
			continue;
		
		DynamicsComponent& dynamicsComponent = *node.getDynamicsComponent();
		
		Float seconds = Math::toSeconds(dt);
		
		Vector2 linForce = dynamicsComponent.getLinearForce();
		Vector2 linAccel = linForce * dynamicsComponent.getProperties().inverseMass;
		
		dynamicsComponent.addLinearVelocity(linAccel * seconds);
		
		Float angForce = dynamicsComponent.getAngularForce();
		Float angAccel = angForce * dynamicsComponent.getProperties().inverseInertia;
		
		dynamicsComponent.addAngularVelocity(angAccel * seconds);
	}
}