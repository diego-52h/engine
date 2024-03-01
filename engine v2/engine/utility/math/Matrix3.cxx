#include <cmath>
#include <cassert>

#include "Matrix3.hxx"

Matrix3::Matrix3()
{
	this -> toIdentity();
}

Matrix3::Matrix3(const Float values[9])
{
	for(Int_16 i = 0; i < 3; i++)
	{
		for(Int_16 j = 0; j < 3; j++)
			this -> values[i][j] = values[(i * 3) + j];
	}
}

Matrix3::Matrix3(const Matrix2& matrix)
{
	this -> toIdentity();
	
	for(Int_16 i = 0; i < 2; i++)
	{
		for(Int_16 j = 0; j < 2; j++)
			this -> values[i][j] = matrix.values[i][j];
	}
}

void Matrix3::toZero()
{
	for(Int_16 i = 0; i < 3; i++)
	{
		for(Int_16 j = 0; j < 3; j++)
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
	
	for(Int_16 i = 0; i < 3; i++)
	{
		for(Int_16 j = 0; j < 3; j++)
			this -> values[i][j] = tempMatrix.values[j][i];
	}
}

Float Matrix3::getOrientation() const
{
	Vector2 scale = this -> getScale(transform);
	
	Float orientation1 = this -> values[0][1] / scale.y;
	Float orientation2 = this -> values[0][0] / scale.x;
	
	return std::atan2(orientation1, orientation2);
}

Vector2 Matrix3::getScale() const
{
	Float scaleX = Vector2(this -> values[0][0], this -> values[1][0]).getLength();
	Float scaleY = Vector2(this -> values[0][1], this -> values[1][1]).getLength();
	
	return Vector2(scaleX, scaleY);
}

Vector2 Matrix3::getPosition() const
{
	Float positionX = this -> values[0][2];
	Float positionY = this -> values[1][2];
	
	return Vector2(positionX, positionY);
}

Matrix2 Matrix3::getMatrix2() const
{
	Matrix2 matrix;
	
	for(Int_16 i = 0; i < 2; i++)
	{
		for(Int_16 j = 0; j < 2; j++)
			matrix.values[i][j] = this -> values[i][j];
	}
	
	return matrix;
}

Matrix3 Matrix3::getInverse() const
{
	Matrix3 cofactorMatrix;
	
	Int_16 x1;
	Int_16 x2;
	
	Int_16 y1;
	Int_16 y2;
	
	Int_16 indices[3][2] = {
		{1, 2},
		{0, 2},
		{0, 1},
	};
	
	for(Int_16 i = 0; i < 3; i++)
	{
		for(Int_16 j = 0; j < 3; j++)
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
	
	Float determinant = (this -> values[0][0] * cofactorMatrix.values[0][0]) + (this -> values[0][1] * cofactorMatrix.values[0][1]) + (this -> values[0][2] * cofactorMatrix.values[0][2]);
	
	for(Int_16 i = 0; i < 3; i++)
	{
		for(Int_16 j = 0; j < 3; j++)
			inverseMatrix.values[i][j] = adjointMatrix.values[i][j] / determinant;
	}
	
	return inverseMatrix;
}

Matrix3 Matrix3::getAbsolute() const
{
	Matrix3 absolute;
	
	for(Int_16 i = 0; i < 3; i++)
	{
		for(Int_16 j = 0; j < 3; j++)
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

Matrix3 Matrix3::rotation(const Float orientation)
{
	Matrix3 rotationMatrix;
	
	Float sin = std::sin(orientation);
	Float cos = std::cos(orientation);
	
	rotationMatrix.values[0][0] = cos;
	rotationMatrix.values[0][1] = sin;
	rotationMatrix.values[1][0] = -sin;
	rotationMatrix.values[1][1] = cos;
	
	return rotationMatrix;
}

Matrix3 Matrix3::scalation(const Vector2& scale)
{
	Matrix3 scalationMatrix;
	
	scalationMatrix.values[0][0] = scale.x;
	scalationMatrix.values[1][1] = scale.y;
	
	return scalationMatrix;
}

Matrix3 Matrix3::translation(const Vector2& position)
{
	Matrix3 translationMatrix;
	
	translationMatrix.values[0][2] = position.x;
	translationMatrix.values[1][2] = position.y;
	
	return translationMatrix;
}