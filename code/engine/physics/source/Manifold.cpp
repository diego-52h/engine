#include <cmath>

#include <algorithm>

#include "CollisionDetection.h"
#include "CollisionVolume.h"
#include "GeometryUtil.h"
#include "Manifold.h"
#include "PhysicsObject.h"
#include "Transform.h"

#define BAUMGARTE_SCALAR 0.1f
#define BAUMGARTE_SLOP 0.001f

Manifold::Manifold()
{
	this -> physicsObjectA = nullptr;
	this -> physicsObjectB = nullptr;
}

Manifold::Manifold(const CollisionData& collisionData)
{
	Vector2 normalA;
	Vector2 normalB;
	
	Side sideA;
	Side sideB;
	
	std::vector<Line> cuttingLinesA;
	std::vector<Line> cuttingLinesB;
	
	this -> physicsObjectA = collisionData.physicsObjectA;
	this -> physicsObjectB = collisionData.physicsObjectB;
	
	collisionData.physicsObjectA -> getCollisionVolume() -> getClippingInfo(collisionData.normal, sideA, normalA, cuttingLinesA);
	collisionData.physicsObjectB -> getCollisionVolume() -> getClippingInfo(-collisionData.normal, sideB, normalB, cuttingLinesB);
	
	if((sideA.numPoints == 0) || (sideB.numPoints == 0))
		return;
	
	else if(sideA.numPoints == 1)
		this -> addContactPoint(sideA.firstPoint, sideA.firstPoint + (collisionData.normal * collisionData.penetration), collisionData.normal, collisionData.penetration);
	
	else if(sideB.numPoints == 1)
		this -> addContactPoint(sideB.firstPoint - (collisionData.normal * collisionData.penetration), sideB.firstPoint, collisionData.normal, collisionData.penetration);
	
	else
	{
		bool swapped = std::fabs(Vector2::dotProduct(collisionData.normal, normalB)) > std::fabs(Vector2::dotProduct(collisionData.normal, normalA));
		
		if(swapped)
		{
			std::swap(normalA, normalB);
			std::swap(sideA, sideB);
			std::swap(cuttingLinesA, cuttingLinesB);
		}
		
		Line referenceLine = Line(normalA, Vector2::dotProduct(normalA, sideA.firstPoint));
		
		cuttingLinesA.push_back(referenceLine);
		
		GeometryUtil::cutSide(sideB, cuttingLinesA);
		
		float penetration;
		
		Vector2 worldPositionA;
		Vector2 worldPositionB;
		
		for(const Vector2& point : {sideB.firstPoint, sideB.finalPoint})
		{
			penetration = -Vector2::dotProduct(point - GeometryUtil::getClosestPointOnSide(point, sideA), collisionData.normal);
			
			if(swapped)
			{
				worldPositionA = point;
				worldPositionB = point - (collisionData.normal * penetration);
			}
			
			else
			{
				penetration = -penetration;
				
				worldPositionA = point + (collisionData.normal * penetration);
				worldPositionB = point;
			}
			
			if(penetration < 0.0f)
				this -> addContactPoint(worldPositionA, worldPositionB, collisionData.normal, penetration);
		}
	}
}

Manifold::~Manifold()
{
}

void Manifold::update(float dt)
{
	for(ContactPoint& contactPoint : this -> contactPoints)
		this -> updateContactPoint(contactPoint, dt);
}

void Manifold::applyImpulse()
{
	for(ContactPoint& contactPoint : this -> contactPoints)
		this -> solveContactPoint(contactPoint);
}

void Manifold::addContactPoint(const Vector2& worldPositionA, const Vector2& worldPositionB, const Vector2& normal, float penetration)
{
	ContactPoint contactPoint;
	
	contactPoint.restitution = 0.0f;
	contactPoint.penetration = penetration;
	
	contactPoint.normal = normal;
	contactPoint.localPositionA = worldPositionA - this -> physicsObjectA -> getTransform() -> getWorldPosition();
	contactPoint.localPositionB = worldPositionB - this -> physicsObjectB -> getTransform() -> getWorldPosition();
	
	this -> contactPoints.push_back(contactPoint);
}

void Manifold::updateContactPoint(ContactPoint& contactPoint, float dt)
{
	contactPoint.restitution = 0.0f;
	
	float elasticity = this -> physicsObjectA -> getElasticity() * this -> physicsObjectB -> getElasticity();
	
	Vector2 perpRelativeA = contactPoint.localPositionA.getPerpendicular();
	Vector2 perpRelativeB = contactPoint.localPositionB.getPerpendicular();
	
	Vector2 velocityA = this -> physicsObjectA -> getLinearVelocity() + (perpRelativeA * this -> physicsObjectA -> getAngularVelocity());
	Vector2 velocityB = this -> physicsObjectB -> getLinearVelocity() + (perpRelativeB * this -> physicsObjectB -> getAngularVelocity());
	
	Vector2 dv = velocityA - velocityB;
	
	float collisionVelocity = Vector2::dotProduct(dv, contactPoint.normal);
	
	contactPoint.restitution += -BAUMGARTE_SCALAR * (std::min(contactPoint.penetration + BAUMGARTE_SLOP, 0.0f) / dt);
	contactPoint.restitution += (elasticity * collisionVelocity) / this -> contactPoints.size();
}

void Manifold::solveContactPoint(ContactPoint& contactPoint)
{
	float inverseMassA = this -> physicsObjectA -> getInverseMass();
	float inverseMassB = this -> physicsObjectB -> getInverseMass();
	
	float inverseInertiaA = this -> physicsObjectA -> getInverseInertia();
	float inverseInertiaB = this -> physicsObjectB -> getInverseInertia();
	
	Vector2 perpRelativeA = contactPoint.localPositionA.getPerpendicular();
	Vector2 perpRelativeB = contactPoint.localPositionB.getPerpendicular();
	
	Vector2 velocityA = this -> physicsObjectA -> getLinearVelocity() + (perpRelativeA * this -> physicsObjectA -> getAngularVelocity());
	Vector2 velocityB = this -> physicsObjectB -> getLinearVelocity() + (perpRelativeB * this -> physicsObjectB -> getAngularVelocity());
	
	Vector2 dv = velocityB - velocityA;
	
	float collisionVelocity = Vector2::dotProduct(dv, contactPoint.normal);
	
	if(std::fabs(collisionVelocity) > 1e-6f)
	{
		float angularMassA = inverseInertiaA * (Vector2::dotProduct(perpRelativeA, contactPoint.normal) * Vector2::dotProduct(perpRelativeA, contactPoint.normal));
		float angularMassB = inverseInertiaB * (Vector2::dotProduct(perpRelativeB, contactPoint.normal) * Vector2::dotProduct(perpRelativeB, contactPoint.normal));
		
		float constraintMass = inverseMassA + inverseMassB + angularMassA + angularMassB;
		
		if(constraintMass > 0.0f)
		{
			Vector2 impulse = contactPoint.normal * (std::max(contactPoint.restitution - collisionVelocity, 0.0f) / constraintMass);
			
			this -> physicsObjectA -> addLinearImpulse(-impulse);
			this -> physicsObjectB -> addLinearImpulse(impulse);
			
			this -> physicsObjectA -> addAngularImpulse(Vector2::dotProduct(perpRelativeA, -impulse));
			this -> physicsObjectB -> addAngularImpulse(Vector2::dotProduct(perpRelativeB, impulse));
		}
	}
	
	Vector2 tangent = dv - (contactPoint.normal * collisionVelocity);
	
	if(tangent.getLength() > 1e-6f)
	{
		tangent.normalise();
		
		float angularMassA = inverseInertiaA * (Vector2::dotProduct(perpRelativeA, tangent) * Vector2::dotProduct(perpRelativeA, tangent));
		float angularMassB = inverseInertiaB * (Vector2::dotProduct(perpRelativeB, tangent) * Vector2::dotProduct(perpRelativeB, tangent));
		
		float frictionMass = inverseMassA + inverseMassB + angularMassA + angularMassB;
		
		if(frictionMass > 0.0f)
		{
			float friction = this -> physicsObjectA -> getFriction() * this -> physicsObjectB -> getFriction();
			
			Vector2 impulse = tangent * ((friction * -Vector2::dotProduct(dv, tangent)) / frictionMass);
			
			this -> physicsObjectA -> addLinearImpulse(-impulse);
			this -> physicsObjectB -> addLinearImpulse(impulse);
			
			this -> physicsObjectA -> addAngularImpulse(Vector2::dotProduct(perpRelativeA, -impulse));
			this -> physicsObjectB -> addAngularImpulse(Vector2::dotProduct(perpRelativeB, impulse));
		}
	}
}