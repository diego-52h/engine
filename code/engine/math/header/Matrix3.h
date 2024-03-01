#ifndef MATRIX3_H
#define MATRIX3_H

#include "Matrix2.h"
#include "Vector2.h"

class Matrix3
{
	public:
		float values[3][3];
	
	public:
		Matrix3();
		Matrix3(float values[9]);
		Matrix3(const Matrix2& matrix);
		~Matrix3();
		
		void toZero();
		void toIdentity();
		void toTranspose();
		
		Matrix2 getMatrix2() const;
		
		Matrix3 getInverse() const;
		Matrix3 getAbsolute() const;
		Matrix3 getTranspose() const;
		
		static Matrix3 rotationMatrix(float radians);
		
		static Matrix3 scalingMatrix(const Vector2& scale);
		static Matrix3 translationMatrix(const Vector2& translation);
		
		inline Vector2 operator*(const Vector2& vectorB) const
		{
			Vector2 output;
			
			output.x = (this -> values[0][0] * vectorB.x) + (this -> values[0][1] * vectorB.y) + this -> values[0][2];
			output.y = (this -> values[1][0] * vectorB.x) + (this -> values[1][1] * vectorB.y) + this -> values[1][2];
			
			float aux = (this -> values[2][0] * vectorB.x) + (this -> values[2][1] * vectorB.y) + this -> values[2][2];
			
			output.x /= aux;
			output.y /= aux;
			
			return output;
		}
		
		inline Matrix3 operator*(const Matrix3& matrixB) const
		{
			Matrix3 output;
			
			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					for(int k = 0; k < 3; k++)
						output.values[i][j] = (this -> values[i][0] * matrixB.values[0][j]) + (this -> values[i][1] * matrixB.values[1][j]) + (this -> values[i][2] * matrixB.values[2][j]);
				}
			}
			
			return output;
		}
};

#endif