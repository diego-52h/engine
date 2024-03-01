#ifndef TIMER_H
#define TIMER_H

class Timer
{
	public:
		Timer();
		~Timer();
		
		void update();
		
		int getTimeDelta() const;
	
	protected:
		int initialTime;
		int elapsedTime;
};

#endif