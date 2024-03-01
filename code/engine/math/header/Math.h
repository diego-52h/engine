#ifndef MATH_H
#define MATH_H

namespace Math
{
	class Vector2;
	
	static const float PI = 3.1415926535f;
	static const float PI_OVER_360 = PI / 360.0f;
	
	inline float degreesToRadians(float degrees) { return (degrees / 180.0f) * PI; }
	inline float radiansToDegrees(float radians) { return (radians / PI) * 180.0f; }
}

#endif