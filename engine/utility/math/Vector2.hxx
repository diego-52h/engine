#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
	public:
		union
		{
			struct
			{
				Float x;
				Float y;
			};
			
			Float values[2];
		};
	
	public:
		Vector2();
		Vector2(const Float x, const Float y);
		
		void toZero();
		void toNorm();
		void toPerp();
		
		Float getMin() const;
		Float getMax() const;
		Float getLen() const;
		
		Vector2 getNorm() const;
		Vector2 getPerp() const;
		
		static Float dot(const Vector2& vectorA, const Vector2& vectorB);
		
		inline Vector2 operator+() const { return Vector2(+this -> x, +this -> y); }
		inline Vector2 operator-() const { return Vector2(-this -> x, -this -> y); }
		
		inline Vector2 operator+(const Vector2& vectorB) const { return Vector2(this -> x + vectorB.x, this -> y + vectorB.y); }
		inline Vector2 operator-(const Vector2& vectorB) const { return Vector2(this -> x - vectorB.x, this -> y - vectorB.y); }
		inline Vector2 operator*(const Vector2& vectorB) const { return Vector2(this -> x * vectorB.x, this -> y * vectorB.y); }
		inline Vector2 operator/(const Vector2& vectorB) const { return Vector2(this -> x / vectorB.x, this -> y / vectorB.y); }
		
		inline Vector2 operator*(const Float value) const { return Vector2(this -> x * value, this -> y * value); }
		inline Vector2 operator/(const Float value) const { return Vector2(this -> x / value, this -> y / value); }
		
		inline void operator+=(const Vector2& vectorB) { this -> x += vectorB.x; this -> y += vectorB.y; }
		inline void operator-=(const Vector2& vectorB) { this -> x -= vectorB.x; this -> y -= vectorB.y; }
		inline void operator*=(const Vector2& vectorB) { this -> x *= vectorB.x; this -> y *= vectorB.y; }
		inline void operator/=(const Vector2& vectorB) { this -> x /= vectorB.x; this -> y /= vectorB.y; }
		
		inline void operator*=(const Float value) { this -> x *= value; this -> y *= value; }
		inline void operator/=(const Float value) { this -> x /= value; this -> y /= value; }
		
		inline Float operator[](Int_16 index) const { return this -> values[index]; }
		
		inline Bool operator==(const Vector2& vectorB) const { return (this -> x == vectorB.x) && (this -> y == vectorB.y); }
		inline Bool operator!=(const Vector2& vectorB) const { return (this -> x != vectorB.x) && (this -> y != vectorB.y); }
		
		inline Float& operator[](Int_16 index) { return this -> values[index]; }
		
};

#endif