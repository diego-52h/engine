#ifndef CONSTRAINT_H
#define CONSTRAINT_H

class Constraint
{
	public:
		virtual void updateConstraint(const Int_16 dt) = 0;
		virtual void resolveConstraint() = 0;
};

#endif