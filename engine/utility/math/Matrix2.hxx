#ifndef MATRIX2_H
#define MATRIX2_H

#include "Vector2.hxx"

class Matrix2
{
	public:
		Float values[2][2];
	
	public:
		Matrix2();
		Matrix2(const Float values[4]);
		
		void toZero();
		void toIdentity();
		
		Matrix2 getInverse() const;
		
		static Matrix2 rotation(const Float radians);
		
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
			
			for(Int_16 i = 0; i < 2; i++)
			{
				for(Int_16 j = 0; j < 2; j++)
				{
					for(Int_16 k = 0; k < 2; k++)
						output.values[i][j] = (this -> values[i][0] * matrixB.values[0][j]) + (this -> values[i][1] * matrixB.values[1][j]);
				}
			}
			
			return output;
		}
};

#endif