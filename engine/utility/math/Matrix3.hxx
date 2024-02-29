#ifndef MATRIX3_H
#define MATRIX3_H

#include "Matrix2.hxx"
#include "Vector2.hxx"

class Matrix3
{
	public:
		Float values[3][3];
	
	public:
		Matrix3();
		Matrix3(const Float values[9]);
		Matrix3(const Matrix2& matrix);
		
		void toZero();
		void toIdentity();
		void toTranspose();
		
		Float getOrientation() const;
		
		Vector2 getScale() const;
		Vector2 getPosition() const;
		
		Matrix2 getMatrix2() const;
		
		Matrix3 getInverse() const;
		Matrix3 getAbsolute() const;
		Matrix3 getTranspose() const;
		
		static Matrix3 rotation(const Float orientation);
		
		static Matrix3 scalation(const Vector2& scale);
		static Matrix3 translation(const Vector2& position);
		
		inline Vector2 operator*(const Vector2& vectorB) const
		{
			Vector2 output;
			
			output.x = (this -> values[0][0] * vectorB.x) + (this -> values[0][1] * vectorB.y) + this -> values[0][2];
			output.y = (this -> values[1][0] * vectorB.x) + (this -> values[1][1] * vectorB.y) + this -> values[1][2];
			
			Float aux = (this -> values[2][0] * vectorB.x) + (this -> values[2][1] * vectorB.y) + this -> values[2][2];
			
			output.x /= aux;
			output.y /= aux;
			
			return output;
		}
		
		inline Matrix3 operator*(const Matrix3& matrixB) const
		{
			Matrix3 output;
			
			for(Int_16 i = 0; i < 3; i++)
			{
				for(Int_16 j = 0; j < 3; j++)
				{
					for(Int_16 k = 0; k < 3; k++)
						output.values[i][j] = (this -> values[i][0] * matrixB.values[0][j]) + (this -> values[i][1] * matrixB.values[1][j]) + (this -> values[i][2] * matrixB.values[2][j]);
				}
			}
			
			return output;
		}
};

#endif