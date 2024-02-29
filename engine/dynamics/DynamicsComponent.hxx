#ifndef DYNAMICS_COMPONENT_H
#define DYNAMICS_COMPONENT_H

struct Properties
{
	Float inverseMass;
	Float inverseInertia;
	
	std::string material;
};

class DynamicsComponent
{
	public:
		DynamicsComponent(const Properties& properties);
		
		void reset();
		
		void addAngularForce(const Float force);
		void addAngularVelocity(const Float velocity);
		
		void addLinearForce(const Vector& force);
		void addLinearVelocity(const Vector2& velocity);
		
		Properties& getProperties();
		
		Float getAngularForce() const;
		Float getAngularVelocity() const;
		
		const Vector2& getLinearForce() const;
		const Vector2& getLinearVelocity() const;
	
	private:
		Float angularForce;
		Float angularVelocity;
		
		Vector2 linearForce;
		Vector2 linearVelocity;
		
		Properties properties;
}

#endif