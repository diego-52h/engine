#include <cmath>

#include "Vector2.h"

Vector2::Vector2()
{
	this -> toZero();
}

Vector2::Vector2(const float x, const float y)
{
	this -> x = x;
	this -> y = y;
}

Vector2::~Vector2()
{
}

void Vector2::toZero()
{
	this -> x = 0.0f;
	this -> y = 0.0f;
}

void Vector2::toInverse()
{
	this -> x = -this -> x;
	this -> y = -this -> y;
}

void Vector2::normalise()
{
	float length = this -> getLength();
	
	if(length != 0.0f)
	{
		length = 1.0f / length;
		
		this -> x *= length;
		this -> y *= length;
	}
}

float Vector2::getLength()
{
	return std::sqrt((this -> x * this -> x) + (this -> y * this -> y));
}

float Vector2::getMinElement()
{
	return (this -> x < this -> y) ? this -> x : this -> y;
}

float Vector2::getMaxElement()
{
	return (this -> x > this -> y) ? this -> x : this -> y;
}

Vector2 Vector2::getNormalised()
{
	Vector2 normVector = *this;
	
	normVector.normalise();
	
	return normVector;
}

Vector2 Vector2::getPerpendicular()
{
	Vector2 perpVector = Vector2(this -> y, -this -> x);
	
	return perpVector;
}

float Vector2::dotProduct(const Vector2& vectorA, const Vector2& vectorB)
{
	return (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y);
}