#include <cmath>
#include <assert.h>

#include "Matrix3.h"

Matrix3::Matrix3()
{
	this -> toIdentity();
}

Matrix3::Matrix3(float values[9])
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
			this -> values[i][j] = values[(i * 3) + j];
	}
}

Matrix3::Matrix3(const Matrix2& matrix)
{
	this -> toIdentity();
	
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
			this -> values[i][j] = matrix.values[i][j];
	}
}

Matrix3::~Matrix3()
{
}

void Matrix3::toZero()
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
			this -> values[i][j] = 0.0f;
	}
}

void Matrix3::toIdentity()
{
	this -> toZero();
	
	this -> values[0][0] = 1.0f;
	this -> values[1][1] = 1.0f;
	this -> values[2][2] = 1.0f;
}

void Matrix3::toTranspose()
{
	Matrix3 tempMatrix = *this;
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
			this -> values[i][j] = tempMatrix.values[j][i];
	}
}

Matrix2 Matrix3::getMatrix2() const
{
	Matrix2 matrix;
	
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
			matrix.values[i][j] = this -> values[i][j];
	}
	
	return matrix;
}

Matrix3 Matrix3::getInverse() const
{
	Matrix3 cofactorMatrix;
	
	int x1;
	int x2;
	
	int y1;
	int y2;
	
	int indices[3][2] = {
		{1, 2},
		{0, 2},
		{0, 1},
	};
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			x1 = indices[i][0];
			x2 = indices[i][1];
			
			y1 = indices[j][0];
			y2 = indices[j][1];
			
			cofactorMatrix.values[i][j] = (this -> values[x1][y1] * this -> values[x2][y2]) - (this -> values[x1][y2] * this -> values[x2][y1]);
			
			if((i == 1) ^ (j == 1))
				cofactorMatrix.values[i][j] *= -1;
		}
	}
	
	Matrix3 adjointMatrix = cofactorMatrix.getTranspose();
	Matrix3 inverseMatrix;
	
	float determinant = (this -> values[0][0] * cofactorMatrix.values[0][0]) + (this -> values[0][1] * cofactorMatrix.values[0][1]) + (this -> values[0][2] * cofactorMatrix.values[0][2]);
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
			inverseMatrix.values[i][j] = adjointMatrix.values[i][j] / determinant;
	}
	
	return inverseMatrix;
}

Matrix3 Matrix3::getAbsolute() const
{
	Matrix3 absolute;
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
			absolute.values[i][j] = std::abs(this -> values[i][j]);
	}
	
	return absolute;
}

Matrix3 Matrix3::getTranspose() const
{
	Matrix3 transpose = *this;
	
	transpose.toTranspose();
	
	return transpose;
}

Matrix3 Matrix3::rotationMatrix(float radians)
{
	Matrix3 rotationMatrix;
	
	float sin = std::sin(radians);
	float cos = std::cos(radians);
	
	rotationMatrix.values[0][0] = cos;
	rotationMatrix.values[0][1] = sin;
	rotationMatrix.values[1][0] = -sin;
	rotationMatrix.values[1][1] = cos;
	
	return rotationMatrix;
}

Matrix3 Matrix3::scalingMatrix(const Vector2& scale)
{
	Matrix3 scalingMatrix;
	
	scalingMatrix.values[0][0] = scale.x;
	scalingMatrix.values[1][1] = scale.y;
	
	return scalingMatrix;
}

Matrix3 Matrix3::translationMatrix(const Vector2& translation)
{
	Matrix3 translationMatrix;
	
	translationMatrix.values[0][2] = translation.x;
	translationMatrix.values[1][2] = translation.y;
	
	return translationMatrix;
}