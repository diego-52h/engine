#ifndef MATRIX2_H
#define MATRIX2_H

#include "Vector2.h"

class Matrix2
{
	public:
		float values[2][2];
	
	public:
		Matrix2();
		Matrix2(float values[4]);
		~Matrix2();
		
		void toZero();
		void toIdentity();
		
		Matrix2 getInverse() const;
		
		static Matrix2 rotationMatrix(float radians);
		
		inline Vector2 operator*(const Vector2& vectorB) const
		{
			Vector2 output;
			
			output.x = (this -> values[0][0] * vectorB.x) + (this -> values[0][1] * vectorB.y);
			output.y = (this -> values[1][0] * vectorB.x) + (this -> values[1][1] * vectorB.y);
			
			return output;
		}
		
		inline Matrix2 operator*(const Matrix2& matrixB) const
		{
			Matrix2 output;
			
			for(int i = 0; i < 2; i++)
			{
				for(int j = 0; j < 2; j++)
				{
					for(int k = 0; k < 2; k++)
						output.values[i][j] = (this -> values[i][0] * matrixB.values[0][j]) + (this -> values[i][1] * matrixB.values[1][j]);
				}
			}
			
			return output;
		}
};

#endif