#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
	public:
		union
		{
			struct
			{
				float x;
				float y;
			};
			
			float values[2];
		};
	
	public:
		Vector2();
		Vector2(const float x, const float y);
		~Vector2();
		
		void toZero();
		void toInverse();
		void normalise();
		
		float getLength();
		float getMinElement();
		float getMaxElement();
		
		Vector2 getNormalised();
		Vector2 getPerpendicular();
		
		static float dotProduct(const Vector2& vectorA, const Vector2& vectorB);
		
		inline Vector2 operator+(const Vector2& vectorB) const { return Vector2(this -> x + vectorB.x, this -> y + vectorB.y); }
		inline Vector2 operator-(const Vector2& vectorB) const { return Vector2(this -> x - vectorB.x, this -> y - vectorB.y); }
		inline Vector2 operator*(const Vector2& vectorB) const { return Vector2(this -> x * vectorB.x, this -> y * vectorB.y); }
		inline Vector2 operator/(const Vector2& vectorB) const { return Vector2(this -> x / vectorB.x, this -> y / vectorB.y); }
		
		inline Vector2 operator-() const { return Vector2(-this -> x, -this -> y); }
		inline Vector2 operator*(const float value) const { return Vector2(this -> x * value, this -> y * value); }
		inline Vector2 operator/(const float value) const { return Vector2(this -> x / value, this -> y / value); }
		
		inline void operator+=(const Vector2& vectorB) { this -> x += vectorB.x; this -> y += vectorB.y; }
		inline void operator-=(const Vector2& vectorB) { this -> x -= vectorB.x; this -> y -= vectorB.y; }
		inline void operator*=(const Vector2& vectorB) { this -> x *= vectorB.x; this -> y *= vectorB.y; }
		inline void operator/=(const Vector2& vectorB) { this -> x /= vectorB.x; this -> y /= vectorB.y; }
		
		inline void operator*=(const float value) { this -> x *= value; this -> y *= value; }
		inline void operator/=(const float value) { this -> x /= value; this -> y /= value; }
		
		inline float operator[](int index) const { return this -> values[index]; }
		inline float& operator[](int index) { return this -> values[index]; }
		
		inline bool operator==(const Vector2& vectorB) const { return (this -> x == vectorB.x) && (this -> y == vectorB.y); }
		inline bool operator!=(const Vector2& vectorB) const { return (this -> x != vectorB.x) && (this -> y != vectorB.y); }
};

#endif