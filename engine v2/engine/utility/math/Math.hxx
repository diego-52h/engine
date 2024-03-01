#ifndef MATH_H
#define MATH_H

#include <cmath>

namespace Math
{
	static const Float PI = 3.1415926535f;
	
	static const Float EPS = 1e-6f;
	static const Float INF = 1e35f;
	
	inline Float toSeconds(const Int_16 ms) { return ms / 1000.0f; };
	
	inline Float degreesToRadians(const Float degrees) { return (degrees / 180.0f) * PI; }
	inline Float radiansToDegrees(const Float radians) { return (radians / PI) * 180.0f; }
	
	inline Int_16 log(Int_16 base, Int_16 argument) { return std::log(argument) / std::log(base); }
	
	inline Int_16 pow(Int_16 base, Int_16 exponent)
	{
		Int_16 value = base;
		Int_16 power = 1;
		
		while(exponent != 0)
		{
			if(exponent & 1)
				value *= power;
			
			power *= power;
			
			exponent >>= 1;
		}
		
		return value;
	}
};

#endif