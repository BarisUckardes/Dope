#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Simple matrix3x3 implementation
	/// </summary>
	class DOPE_ENGINE_API Matrix3x3 final
	{
	public:
		/// <summary>
		/// Returns an identity matrix
		/// </summary>
		/// <returns></returns>
		static Matrix3x3 get_identity();

		Matrix3x3();
		Matrix3x3(
			const float a0,const float a1,const float a2,
			const float b0,const float b1,const float b2,
			const float c0,const float c1,const float c2);

		/// <summary>
		/// Returns whether this matrix is invertable or not
		/// </summary>
		/// <returns></returns>
		 bool is_invertable() const;

		/// <summary>
		/// Returns the determinant of this matrix
		/// </summary>
		/// <returns></returns>
		 float get_determinant() const;

		/// <summary>
		/// Returns the inverse version of this matrix
		/// </summary>
		/// <returns></returns>
		 Matrix3x3 get_inverse() const;

		/// <summary>
		/// Returns the transposed version of this matrix
		/// </summary>
		/// <returns></returns>
		 Matrix3x3 get_transpose() const;

		/// <summary>
		/// Transposes this matrix
		/// </summary>
		 void transpose_this();

		Matrix3x3 operator*(float a);
		Matrix3x3 operator +(const Matrix3x3& a);
		Matrix3x3 operator -(const Matrix3x3& a);
		Matrix3x3 operator*(const Matrix3x3& a);

		float A0, A1, A2;
		float B0, B1, B2;
		float C0, C1, C2;
	};


}