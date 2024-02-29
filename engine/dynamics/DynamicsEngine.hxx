#ifndef DYNAMICS_ENGINE_H
#define DYNAMICS_ENGINE_H

class DynamicsEngine
{
	public:
		DynamicsEngine(GameSection& section);
		
		void update(const Int_16 dt);
		
		void setSection(GameSection& section);
	
	private:
		GameSection& section;
		
		CollisionTree staticTree;
		CollisionTree activeTree;
		
		Vector<Constraint> constraints;
	
	private:
		void createConstraints();
		
		void integrateForPosition(const Int_16 dt);
		void integrateForVelocity(const Int_16 dt);
};

#endif