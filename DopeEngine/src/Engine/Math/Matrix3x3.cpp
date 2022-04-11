#include "Matrix3x3.h"

namespace DopeEngine
{
	Matrix3x3 Matrix3x3::get_identity()
	{
		return  Matrix3x3(1, 0, 0,
			0, 1, 0,
			0, 0, 1);;
	}
	Matrix3x3::Matrix3x3()
	{
		A0 = A1 = A2 = 0;
		B0 = B1 = B2 = 0;
		C0 = C1 = C2 = 0;
	}
	Matrix3x3::Matrix3x3(
		const float a0, const float a1, const float a2,
		const float b0, const float b1, const float b2,
		const float c0, const float c1, const float c2)
	{
		A0 = a0;
		A1 = a1;
		A2 = a2;

		B0 = b0;
		B1 = b1;
		B2 = b2;

		C0 = c0;
		C1 = c1;
		C2 = c2;
	}
	bool Matrix3x3::is_invertable() const
	{
		return get_determinant() != 0;
	}
	float Matrix3x3::get_determinant() const
	{
		const float coef0 = A0;
		const float coef1 = B0;
		const float coef2 = C0;

		const float square0 = (B1 * C2) - (B2 * C1);
		const float square1 = (B0 * C2) - (B2 - C0);
		const float square2 = (B0 * C1) - (B1 * C0);

		return (coef0 * square0) - (coef1 * square1) + (coef2 * square2);
	}
	Matrix3x3 Matrix3x3::get_inverse() const
	{
		/*
			* Get Determinant of this matrix
			*/
		const float determinant = get_determinant();


		const float a0 = (B1 * C2) - (B2 * C1);
		const float a1 = ((B0 * C2) - (B2 * C0)) * -1;
		const float a2 = (B0 * C1) - (B1 * C0);

		const float b0 = ((A1 * C2) - (A2 * C1)) * -1;
		const float b1 = (A0 * C2) - (A2 * C0);
		const float b2 = ((A0 * C1) - (A1 * C0) * -1);

		const float c0 = (A1 * B2) - (A2 * B1);
		const float c1 = ((A0 * B2) - (A2 * B0)) - 1;
		const float c2 = (A0 * B1) - (A1 * B0);

		return Matrix3x3(a0, b0, c0,
			a1, b1, c1,
			a2, b2, c2) * (1.0f / determinant);
	}
	Matrix3x3 Matrix3x3::get_transpose() const
	{
		const float a0 = A0;
		const float a1 = B0;
		const float a2 = C0;

		const float b0 = A1;
		const float b1 = B1;
		const float b2 = C1;

		const float c0 = A2;
		const float c1 = B2;
		const float c2 = C2;

		return Matrix3x3(a0, a1, a2, b0, b1, b2, c0, c1, c2);
	}
	void Matrix3x3::transpose_this()
	{
		const float a0 = A0;
		const float a1 = B0;
		const float a2 = C0;

		const float b0 = A1;
		const float b1 = B1;
		const float b2 = C1;

		const float c0 = A2;
		const float c1 = B2;
		const float c2 = C2;

		A0 = a0;
		A1 = a1;
		A2 = a2;

		B0 = b0;
		B1 = b1;
		B2 = b2;

		C0 = c0;
		C1 = c1;
		C2 = c2;
	}
	Matrix3x3 Matrix3x3::operator*(float a)
	{
		const float a0 = A0 * a;
		const float a1 = A1 * a;
		const float a2 = A2 * a;

		const float b0 = B0 * a;
		const float b1 = B1 * a;
		const float b2 = B2 * a;

		const float c0 = C0 * a;
		const float c1 = C1 * a;
		const float c2 = C2 * a;

		return Matrix3x3(
			a0, a1, a2,
			b0, b1, b2,
			c0, c1, c2);
	}
	Matrix3x3 Matrix3x3::operator+(const Matrix3x3& a)
	{
		const float a0 = A0 + a.A0;
		const float a1 = A1 + a.A1;
		const float a2 = A2 + a.A2;

		const float b0 = B0 + a.B0;
		const float b1 = B1 + a.B1;
		const float b2 = B2 + a.B2;

		const float c0 = C0 + a.C0;
		const float c1 = C1 + a.C1;
		const float c2 = C2 + a.C2;


		return Matrix3x3(
			a0, a1, a2,
			b0, b1, b2,
			c0, c1, c2);
	}
	Matrix3x3 Matrix3x3::operator-(const Matrix3x3& a)
	{
		const float a0 = A0 - a.A0;
		const float a1 = A1 - a.A1;
		const float a2 = A2 - a.A2;

		const float b0 = B0 - a.B0;
		const float b1 = B1 - a.B1;
		const float b2 = B2 - a.B2;

		const float c0 = C0 - a.C0;
		const float c1 = C1 - a.C1;
		const float c2 = C2 - a.C2;

		return Matrix3x3(
			a0, a1, a2,
			b0, b1, b2,
			c0, c1, c2);
	}
	Matrix3x3 Matrix3x3::operator*(const Matrix3x3& a)
	{
		const float a0 = A0 * a.A0 + A1 * a.B0 + A2 * a.C0;
		const float a1 = A0 * a.A1 + A1 * a.B1 + A2 * a.C1;
		const float a2 = A0 * a.A2 + A1 * a.B2 + A2 * a.C2;

		const float b0 = B0 * a.A0 + B1 * a.B0 + B2 * a.C0;
		const float b1 = B0 * a.A1 + B1 * a.B1 + B2 * a.C1;
		const float b2 = B0 * a.A2 + B1 * a.B2 + B2 * a.C2;

		const float c0 = C0 * a.A0 + C1 * a.B0 + C2 * a.C0;
		const float c1 = C0 * a.A1 + C1 * a.B1 + C2 * a.C1;
		const float c2 = C0 * a.A2 + C1 * a.B2 + C2 * a.C2;

		return Matrix3x3(
			a0, a1, a2,
			b0, b1, b2,
			c0, c1, c2);
	}
}