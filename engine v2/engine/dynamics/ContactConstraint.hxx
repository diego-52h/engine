#ifndef CONTACT_CONSTRAINT_H
#define CONTACT_CONSTRAINT_H

struct Contact
{
	Float distance;
	Float restitution;
	
	Vector2 normal;
	
	Vector2 lPointA;
	Vector2 lPointB;
};

class ContactConstraint : public Constraint
{
	public:
		ContactConstraint(const Collision& collision);
		
		void updateConstraint(const Int_16 dt);
		void resolveConstraint();
		
		Bool exists() const;
	
	private:
		Collision& collision;
		
		Vector<Contact> contacts;
	
	private:
		void appendContact(const Float distance, const Vector2& normal, const Vector2& wPointA, const Vector2& wPointB);
		
		void updateContact(const Contact& contact, const Int_16 dt);
		void resolveContact(const Contact& contact);
};

#endif