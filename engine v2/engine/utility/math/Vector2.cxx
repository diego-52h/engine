#include "Vector2.hxx"

Vector2::Vector2() : x(0), y(0) { }
Vector2::Vector2(const Float x, const Float y) : x(x), y(y) { }

void Vector2::toZero()
{
	this -> x = 0.0f;
	this -> y = 0.0f;
}

void Vector2::toNorm()
{
	Float length = this -> getLength();
	
	if(length != 0.0f)
	{
		length = 1.0f / length;
		
		this -> x *= length;
		this -> y *= length;
	}
}

void Vector2::toPerp()
{
	Float x = this -> x;
	Float y = this -> y;
	
	this -> x = y;
	this -> y = -x;
}

Float Vector2::getMin() const { return Math::min(this -> x, this -> y); }
Float Vector2::getMax() const { return Math::max(this -> x, this -> y); }
Float Vector2::getLen() const { return Math::sqrt((this -> x * this -> x) + (this -> y * this -> y)); }

Vector2 Vector2::getNorm() const { return *this.toNorm(); }
Vector2 Vector2::getPerp() const { return *this.toPerp(); }

Float Vector2::dot(const Vector2& vectorA, const Vector2& vectorB) { return (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y); }