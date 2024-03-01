#include <cmath>
#include <assert.h>

#include "Matrix2.h"

Matrix2::Matrix2()
{
	this -> toIdentity();
}

Matrix2::Matrix2(float values[4])
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
			this -> values[i][j] = values[(i * 2) + j];
	}
}

Matrix2::~Matrix2()
{
}

void Matrix2::toZero()
{
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
			this -> values[i][j] = 0.0f;
	}
}

void Matrix2::toIdentity()
{
	this -> toZero();
	
	this -> values[0][0] = 1.0f;
	this -> values[1][1] = 1.0f;
}

Matrix2 Matrix2::getInverse() const
{
	Matrix2 inverse;
	
	float inverseDeterminant = 1 / ((this -> values[0][0] * this -> values[1][1]) - (this -> values[0][1] * this -> values[1][0]));
	
	inverse.values[0][0] = inverseDeterminant * this -> values[1][1];
	inverse.values[0][1] = inverseDeterminant * (-this -> values[0][1]);
	inverse.values[1][0] = inverseDeterminant * (-this -> values[1][0]);
	inverse.values[1][1] = inverseDeterminant * this -> values[0][0];
	
	return inverse;
}

Matrix2 Matrix2::rotationMatrix(float radians)
{
	Matrix2 rotationMatrix;
	
	float sin = std::sin(radians);
	float cos = std::cos(radians);
	
	rotationMatrix.values[0][0] = cos;
	rotationMatrix.values[0][1] = sin;
	rotationMatrix.values[1][0] = -sin;
	rotationMatrix.values[1][1] = cos;
	
	return rotationMatrix;
}