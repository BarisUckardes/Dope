#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Math/Vector3f.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API Matrix4x4 final
	{
	public:
		static Matrix4x4 get_identity();
		static Matrix4x4 get_zero();
		static Matrix4x4 create_translation(const Vector3f& translation);
		static Matrix4x4 create_scale(const Vector3f& scale);
		static Matrix4x4 create_rotation_x(float rotation);
		static Matrix4x4 create_rotation_y(float rotation);
		static Matrix4x4 create_rotation_z(float rotation);
		static Matrix4x4 create_ortho_projection(
			const float left,	const float right,
			const float bottom, const float top,
			const float near,	const float far,
			const float aspectRatio = 1.0f);
		static Matrix4x4 create_perspective_projection(
			const float fov,
			const float nearPlane, const float farPlane,
			const float aspectRatio = 1.0f);
		static Matrix4x4 create_look_at(
			const Vector3f& observerPosition,
			const Vector3f& lookPosition,
			const Vector3f& relativeUpVector);

		Matrix4x4(
			const float a0, const float a1, const float a2, const float a3,
			const float b0, const float b1, const float b2, const float b3,
			const float c0, const float c1, const float c2, const float c3,
			const float d0, const float d1, const float d2, const float d3
		);
		Matrix4x4();

		 bool is_invertable() const;
		 float get_determinant() const;
		 Matrix4x4 get_transpose() const;
		 void transpose_this();

		Matrix4x4 operator +(const Matrix4x4& a);
		Matrix4x4 operator -(const Matrix4x4& a);
		Matrix4x4 operator*(const Matrix4x4& a);

		float A0, A1, A2, A3;
		float B0, B1, B2, B3;
		float C0, C1, C2, C3;
		float D0, D1, D2, D3;
	};


}