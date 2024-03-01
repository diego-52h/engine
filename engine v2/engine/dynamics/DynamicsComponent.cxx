#include "DynamicsComponent.hxx"

DynamicsComponent::DynamicsComponent(const Properties& properties) : properties(properties)
{
	this -> reset();
}

void DynamicsComponent::reset()
{
	this -> angularForce = 0.0f;
	
	this -> linearForce.toZero();
}

void DynamicsComponent::addAngularForce(const Float force) { this -> angularForce += force; }
void DynamicsComponent::addAngularVelocity(const Float velocity) {this -> angularVelocity += velocity; }

void DynamicsComponent::addLinearForce(const Vector2& force) { this -> linearForce += force; }
void DynamicsComponent::addLinearVelocity(const Vector2& velocity) { this -> linearVelocity += velocity; }

Properties& DynamicsComponent::getProperties() { return this -> properties; }

Float DynamicsComponent::getAngularForce() const { return this -> angularForce; }
Float DynamicsComponent::getAngularVelocity() const { return this -> angularVelocity; }

const Vector2& DynamicsComponent::getLinearForce() const { return this -> linearForce; }
const Vector2& DynamicsComponent::getLinearVelocity() const { return this -> linearVelocity; }