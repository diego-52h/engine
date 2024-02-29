#include "ContactConstraint.hxx"

ContactConstraint::ContactConstraint(const Collision& collision) : collision(collision)
{
	Vector<Segment> connectedSegmentsA;
	Vector<Segment> connectedSegmentsB;
	
	Vector2 normal = this -> collision.getNormal();
	
	Segment contactSegmentA = this -> collision.getVolumeA() -> getContactSegment(this -> collision.getNodeA().getTransform(), normal, connectedSegmentsA);
	Segment contactSegmentB = this -> collision.getVolumeB() -> getContactSegment(this -> collision.getNodeB().getTransform(), normal, connectedSegmentsB);
	
	if(contactSegmentA.getPointA() == contactSegmentA.getPointB())
	{
		Vector2 pointA = contactSegmentA.getPointA();
		Vector2 pointB = contactSegmentA.getPointA() + (normal * this -> collision.getDistance());
		
		this -> addContact(this -> collision.getDistance(), normal, pointA, pointB);
		
		return;
	}
	
	if(contactSegmentB.getPointA() == contactSegmentB.getPointB())
	{
		Vector2 pointA = contactSegmentB.getPointA() - (normal * this -> collision.getDistance());
		Vector2 pointB = contactSegmentB.getPointA();
		
		this -> addContact(this -> collision.getDistance(), normal, pointA, pointB);
		
		return;
	}
	
	Bool swapped = std::fabs(Vector2::dot(normal, contactSegmentB.getNormal())) > std::fabs(normal, contactSegmentA.getNormal());
	
	if(swapped)
	{
		std::swap(contactSegmentA, contactSegmentB);
		
		std::swap(connectedSegmentsA, connectedSegmentsB);
	}
	
	contactSegmentB.cut(connectedSegmentsA);
	contactSegmentB.cut({segmentA});
	
	for(const Vector2& point : {contactSegment.getPointA(), contactSegment.getPointB()})
	{
		Float distance;
		
		Vector2 wPointA;
		Vector2 wPointB;
		
		if(swapped)
		{
			distance = -Vector2::dot(point - contactSegmentB.getNearestPoint(point), normal);
			
			wPointA = point;
			wPointB = point - (normal * distance);
		}
		
		else
		{
			distance = +Vector2::dot(point - contactSegmentB.getNearestPoint(point), normal);
			
			wPointA = point + (normal * distance);
			wPointB = point;
		}
		
		if(distance > 0.0f)
			this -> addContact(distance, normal, wPointA, wPointB);
	}
}

void ContactConstraint::updateConstraint(const Int_16 dt)
{
	for(const Contact& contact : this -> contacts)
		updateContact(contact, dt);
}

void ContactConstraint::resolveConstraint()
{
	for(const Contact& contact : this -> contacts)
		resolveContact(contact);
}

Bool ContactConstraint::exists() const { return this -> contacts.size() > 0; }

void ContactConstraint::appendContact(const Float distance, const Vector2& normal, const Vector2& wPointA, const Vector2& wPointB)
{
	Contact contact;
	
	contact.distance = distance;
	contact.restitution = 0.0f;
	
	contact.normal = normal;
	
	contact.lPointA = wPointA - this -> collision.getNodeA().getTransform().getWPosition();
	contact.lPointB = wPointB - this -> collision.getNodeB().getTransform().getWPosition();
	
	this -> contacts.push_back(contact);
}

void ContactConstraint::updateContact(const Contact& contact, const Int_16 dt)
{
	DynamicsComponent& dynamicsComponentA = (this -> collision.getNodeA().getDynamicsComponent() != nullptr) ? *this -> collision.getNodeA().getDynamicsComponent() : DynamicsComponent(false, {0, 0, 0, 0});
	DynamicsComponent& dynamicsComponentB = (this -> collision.getNodeB().getDynamicsComponent() != nullptr) ? *this -> collision.getNodeB().getDynamicsComponent() : DynamicsComponent(false, {0, 0, 0, 0});
	
	const Properties& propertiesA = dynamicsComponentA.getProperties();
	const Properties& propertiesB = dynamicsComponentB.getProperties();
	
	Float elasticity = propertiesA.elasticity * propertiesB.elasticity;
	
	Vector2 perpA = contact.lPointA.getPerp();
	Vector2 perpB = contact.lPointB.getPerp();
	
	Vector2 velocityA = dynamicsComponentA.getLinearVelocity() + (perpA * dynamicsComponentA.getAngularVelocity());
	Vector2 velocityB = dynamicsComponentB.getLinearVelocity() + (perpB * dynamicsComponentB.getAngularVelocity());
	
	Vector2 dv = velocityB - velocityA;
	
	Float velocity = Vector2::dot(dv, contact.normal);
	
	contact.restitution = (-BAUMGARTE_SCALAR * (std::min(contact.distance + BAUMGARTE_SLOP, 0.0f) / dt)) + ((elasticity * velocity) / this -> contacts.size());
}

void ContactConstraint::resolveContact(const Contact& contact)
{
	DynamicsComponent& dynamicsComponentA = (this -> collision.getNodeA().getDynamicsComponent() != nullptr) ? *this -> collision.getNodeA().getDynamicsComponent() : DynamicsComponent(false, {0, 0, 0, 0});
	DynamicsComponent& dynamicsComponentB = (this -> collision.getNodeB().getDynamicsComponent() != nullptr) ? *this -> collision.getNodeB().getDynamicsComponent() : DynamicsComponent(false, {0, 0, 0, 0});
	
	const Properties& propertiesA = dynamicsComponentA.getProperties();
	const Properties& propertiesB = dynamicsComponentB.getProperties();
	
	Vector2 perpA = contact.lPointA.getPerp();
	Vector2 perpB = contact.lPointB.getPerp();
	
	Vector2 velocityA = dynamicsComponentA.getLinearVelocity() + (perpA * dynamicsComponentA.getAngularVelocity());
	Vector2 velocityB = dynamicsComponentB.getLinearVelocity() + (perpB * dynamicsComponentB.getAngularVelocity());
	
	Vector2 dv = velocityB - velocityA;
	
	Float velocity = Vector2::dot(dv, contact.normal);
	
	if(std::fabs(velocity) > Math::EPS)
	{
		Float angularMassA = propertiesA.inverseInertia * Math::pow(Vector2::dot(perpA, contact.normal), 2);
		Float angularMassB = propertiesB.inverseInertia * Math::pow(Vector2::dot(perpB, contact.normal), 2);
		
		Float totalMass = angularMassA + angularMassB + propertiesA.inverseMass + propertiesB.inverseMass;
		
		if(totalMass > 0.0f)
		{
			Vector2 impulse = contact.normal * (std::max(contact.restitution - velocity, 0.0f) / totalMass);
			
			dynamicsComponentA.addLinearImpulse(-impulse);
			dynamicsComponentB.addLinearImpulse(+impulse);
			
			dynamicsComponentA.addAngularImpulse(Vector2::dot(perpA, -impulse));
			dynamicsComponentB.addAngularImpulse(Vector2::dot(perpB, +impulse));
		}
	}
	
	Vector2 tangent = dv - (contact.normal * velocity);
	
	if(tangent.getLength() > Math::EPS)
	{
		tangent.toNorm();
		
		Float angularMassA = propertiesA.inverseInertia * Math::pow(Vector2::dot(perpA, tangent), 2);
		Float angularMassB = propertiesB.inverseInertia * Math::pow(Vector2::dot(perpB, tangent), 2);
		
		Float totalMass = angularMassA + angularMassB + propertiesA.inverseMass + propertiesB.inverseMass;
		
		if(totalMass > 0.0f)
		{
			Float friction = ;
			
			Vector2 impulse = tangent * ((friction * -Vector2::dot(dv, tangent)) / totalMass);
			
			dynamicsComponentA.addLinearImpulse(-impulse);
			dynamicsComponentB.addLinearImpulse(+impulse);
			
			dynamicsComponentA.addAngularImpulse(Vector2::dot(perpA, -impulse));
			dynamicsComponentB.addAngularImpulse(Vector2::dot(perpB, +impulse));
		}
	}
}