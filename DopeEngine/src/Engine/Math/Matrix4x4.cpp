#include "Matrix4x4.h"
#include <Engine/Math/Matrix3x3.h>
#include <Engine/Math/Math.h>
namespace DopeEngine
{
	Matrix4x4 Matrix4x4::get_identity()
	{
		return Matrix4x4
		(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}
	Matrix4x4 Matrix4x4::get_zero()
	{
		return Matrix4x4(
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0);
	}
	Matrix4x4 Matrix4x4::create_translation(const Vector3f& position)
	{
		Matrix4x4 matrix = Matrix4x4::get_identity();
		matrix.A3 = position.X;
		matrix.B3 = position.Y;
		matrix.C3 = position.Z;

		return matrix;
	}
	Matrix4x4 Matrix4x4::create_scale(const Vector3f& scale)
	{
		Matrix4x4 matrix = Matrix4x4::get_identity();
		matrix.A0 = scale.X;
		matrix.B1 = scale.Y;
		matrix.C2 = scale.Z;
		matrix.D3 = 1.0f;
		return matrix;
	}
	Matrix4x4 Matrix4x4::create_rotation_x(float rotation)
	{
		Matrix4x4 matrix = Matrix4x4::get_identity();
		matrix.B1 = Math::cos(rotation * DegToRadCoef);
		matrix.B2 = Math::sin(rotation * DegToRadCoef);
		matrix.C1 = -Math::sin(rotation * DegToRadCoef);
		matrix.C2 = Math::cos(rotation * DegToRadCoef);

		return matrix;
	}
	Matrix4x4 Matrix4x4::create_rotation_y(float rotation)
	{
		Matrix4x4 matrix = Matrix4x4::get_identity();
		matrix.A0 = Math::cos(rotation * DegToRadCoef);
		matrix.A2 = -Math::sin(rotation * DegToRadCoef);
		matrix.C0 = Math::sin(rotation * DegToRadCoef);
		matrix.C2 = Math::cos(rotation * DegToRadCoef);
		return matrix;
	}
	Matrix4x4 Matrix4x4::create_rotation_z(float rotation)
	{
		Matrix4x4 matrix = Matrix4x4::get_identity();
		matrix.A0 = Math::cos(rotation * DegToRadCoef);
		matrix.A1 = -Math::sin(rotation * DegToRadCoef);
		matrix.B0 = Math::sin(rotation * DegToRadCoef);
		matrix.B1 = Math::cos(rotation * DegToRadCoef);
		matrix.C2 = 1.0f;
		matrix.D3 = 1.0f;
		return matrix;
	}
	Matrix4x4 Matrix4x4::create_ortho_projection(float left, float right, float bottom, float top, float far, float near, float aspectRatio)
	{
		Matrix4x4 matrix = Matrix4x4::get_identity();
		matrix.A0 = 2.0f / (right - left);
		matrix.B1 = 2.0f / (top - bottom);
		matrix.C2 = -2.0f / (far - near);
		matrix.D0 = -(right + left) / (right - left);
		matrix.D1 = -(top + bottom) / (top - bottom);
		matrix.D2 = -(far + near) / (far - near);
		return matrix;
	}
	Matrix4x4 Matrix4x4::create_perspective_projection(float fov, float nearPlane, float farPlane, float aspect)
	{
		Matrix4x4 matrix = Matrix4x4::get_zero();

		const float tanHalfFov = Math::tan(fov / 2);
		matrix.A0 = 1.0f / (aspect * tanHalfFov);
		matrix.B1 = 1.0f / (tanHalfFov);
		matrix.C2 = (farPlane + nearPlane) / (farPlane - nearPlane);
		matrix.C3 = 1.0f;
		matrix.D2 = (2 * farPlane * nearPlane) / (farPlane - nearPlane);
		return matrix;
	}
	Matrix4x4 Matrix4x4::create_look_at(const Vector3f& observerPosition, const Vector3f& lookPosition, const Vector3f& relativeUpVector)
	{
		const Vector3f f((lookPosition - observerPosition).get_normalized());
		const Vector3f s(Vector3f::cross_product(f, relativeUpVector).get_normalized());
		const Vector3f u(Vector3f::cross_product(s, f));

		Matrix4x4 matrix = Matrix4x4::get_identity();
		matrix.A0 = s.X;
		matrix.B0 = s.Y;
		matrix.C0 = s.Z;
		matrix.A1 = u.X;
		matrix.B1 = u.Y;
		matrix.C1 = u.Z;
		matrix.A2 = -f.X;
		matrix.B2 = -f.Y;
		matrix.C2 = -f.Z;
		matrix.D0 = -Vector3f::dot_product(s, observerPosition);
		matrix.D1 = -Vector3f::dot_product(u, observerPosition);
		matrix.D2 = -Vector3f::dot_product(f, observerPosition);

		return matrix.get_transpose();
	}
	Matrix4x4::Matrix4x4()
	{
		A0 = A1 = A2 = A3 = 0;
		B0 = B1 = B2 = B3 = 0;
		C0 = C1 = C2 = C3 = 0;
		D0 = D1 = D2 = D3 = 0;
	}
	Matrix4x4::Matrix4x4(float a0, float a1, float a2, float a3, float b0, float b1, float b2, float b3, float c0, float c1, float c2, float c3, float d0, float d1, float d2, float d3)
	{
		A0 = a0;
		A1 = a1;
		A2 = a2;
		A3 = a3;

		B0 = b0;
		B1 = b1;
		B2 = b2;
		B3 = b3;

		C0 = c0;
		C1 = c1;
		C2 = c2;
		C3 = c3;

		D0 = d0;
		D1 = d1;
		D2 = d2;
		D3 = d3;
	}
	bool Matrix4x4::is_invertable() const
	{
		return get_determinant() != 0;
	}
	float Matrix4x4::get_determinant() const
	{
		const float coef0 = A0;
		const float coef1 = B0;
		const float coef2 = C0;
		const float coef3 = D0;

		const Matrix3x3 mat0;
		const Matrix3x3 mat1;
		const Matrix3x3 mat2;
		const Matrix3x3 mat3;

		return (mat0.get_determinant() * coef0) - (mat1.get_determinant() * coef1) + (mat2.get_determinant() * coef2) - (mat3.get_determinant() * coef3);
	}
	Matrix4x4 Matrix4x4::get_transpose() const
	{
		const float a0 = A0;
		const float a1 = B0;
		const float a2 = C0;
		const float a3 = D0;

		const float b0 = A1;
		const float b1 = B1;
		const float b2 = C1;
		const float b3 = D1;

		const float c0 = A2;
		const float c1 = B2;
		const float c2 = C2;
		const float c3 = D2;

		const float d0 = A3;
		const float d1 = B3;
		const float d2 = C3;
		const float d3 = D3;

		return Matrix4x4(a0, a1, a2, a3, b0, b1, b2, b3, c0, c1, c2, c3, d0, d1, d2, d3);
	}
	void Matrix4x4::transpose_this()
	{
		const float a0 = A0;
		const float a1 = B0;
		const float a2 = C0;
		const float a3 = D0;

		const float b0 = A1;
		const float b1 = B1;
		const float b2 = C1;
		const float b3 = D1;

		const float c0 = A2;
		const float c1 = B2;
		const float c2 = C2;
		const float c3 = D2;

		const float d0 = A3;
		const float d1 = B3;
		const float d2 = C3;
		const float d3 = D3;

		A0 = a0;
		A1 = a1;
		A2 = a2;
		A3 = a3;

		B0 = b0;
		B1 = b1;
		B2 = b2;
		B3 = b3;

		C0 = c0;
		C1 = c1;
		C2 = c2;
		C3 = c3;

		D0 = d0;
		D1 = d1;
		D2 = d2;
		D3 = d3;
	}
	
	Matrix4x4 Matrix4x4::operator+(const Matrix4x4& a)
	{
		const float a0 = A0 + a.A0;
		const float a1 = A1 + a.A1;
		const float a2 = A2 + a.A2;
		const float a3 = A3 + a.A3;

		const float b0 = B0 + a.B0;
		const float b1 = B1 + a.B1;
		const float b2 = B2 + a.B2;
		const float b3 = B3 + a.B3;

		const float c0 = C0 + a.C0;
		const float c1 = C1 + a.C1;
		const float c2 = C2 + a.C2;
		const float c3 = C3 + a.C3;

		const float d0 = D0 + a.D0;
		const float d1 = D1 + a.D1;
		const float d2 = D2 + a.D2;
		const float d3 = D3 + a.D3;

		return Matrix4x4(
			a0, a1, a2, a3,
			b0, b1, b2, b3,
			c0, c1, c2, c3,
			d0, d1, d2, d3);
	}
	Matrix4x4 Matrix4x4::operator-(const Matrix4x4& a)
	{
		const float a0 = A0 - a.A0;
		const float a1 = A1 - a.A1;
		const float a2 = A2 - a.A2;
		const float a3 = A3 - a.A3;

		const float b0 = B0 - a.B0;
		const float b1 = B1 - a.B1;
		const float b2 = B2 - a.B2;
		const float b3 = B3 - a.B3;

		const float c0 = C0 - a.C0;
		const float c1 = C1 - a.C1;
		const float c2 = C2 - a.C2;
		const float c3 = C3 - a.C3;

		const float d0 = D0 - a.D0;
		const float d1 = D1 - a.D1;
		const float d2 = D2 - a.D2;
		const float d3 = D3 - a.D3;

		return Matrix4x4(
			a0, a1, a2, a3,
			b0, b1, b2, b3,
			c0, c1, c2, c3,
			d0, d1, d2, d3);
	}
	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& a)
	{
		const float a0 = A0 * a.A0 + A1 * a.B0 + A2 * a.C0 + A3 * a.D0;
		const float a1 = A0 * a.A1 + A1 * a.B1 + A2 * a.C1 + A3 * a.D1;
		const float a2 = A0 * a.A2 + A1 * a.B2 + A2 * a.C2 + A3 * a.D2;
		const float a3 = A0 * a.A3 + A1 * a.B3 + A2 * a.C3 + A3 * a.D3;

		const float b0 = B0 * a.A0 + B1 * a.B0 + B2 * a.C0 + B3 * a.D0;
		const float b1 = B0 * a.A1 + B1 * a.B1 + B2 * a.C1 + B3 * a.D1;
		const float b2 = B0 * a.A2 + B1 * a.B2 + B2 * a.C2 + B3 * a.D2;
		const float b3 = B0 * a.A3 + B1 * a.B3 + B2 * a.C3 + B3 * a.D3;

		const float c0 = C0 * a.A0 + C1 * a.B0 + C2 * a.C0 + C3 * a.D0;
		const float c1 = C0 * a.A1 + C1 * a.B1 + C2 * a.C1 + C3 * a.D1;
		const float c2 = C0 * a.A2 + C1 * a.B2 + C2 * a.C2 + C3 * a.D2;
		const float c3 = C0 * a.A3 + C1 * a.B3 + C2 * a.C3 + C3 * a.D3;

		const float d0 = D0 * a.A0 + D1 * a.B0 + D2 * a.C0 + D3 * a.D0;
		const float d1 = D0 * a.A1 + D1 * a.B1 + D2 * a.C1 + D3 * a.D1;
		const float d2 = D0 * a.A2 + D1 * a.B2 + D2 * a.C2 + D3 * a.D2;
		const float d3 = D0 * a.A3 + D1 * a.B3 + D2 * a.C3 + D3 * a.D3;

		return Matrix4x4(
			a0, a1, a2, a3,
			b0, b1, b2, b3,
			c0, c1, c2, c3,
			d0, d1, d2, d3);
	}
}