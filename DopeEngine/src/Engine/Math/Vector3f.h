#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// X-Y-Z Axis Float Vector
	/// </summary>
	class DOPE_ENGINE_API Vector3f final
	{
	public:

		static float dot_product(const Vector3f& a, const Vector3f& b);
		static Vector3f cross_product(const Vector3f& a, const Vector3f& b);

		Vector3f(const float x,const float y,const float z) : X(x),Y(y),Z(z) {}
		Vector3f(const float value) : X(value),Y(value),Z(value) {}
		Vector3f() : X(0),Y(0),Z(0) {}
		FORCEINLINE float get_length() const;
		FORCEINLINE Vector3f get_normalized() const;
		FORCEINLINE void normalize_this();

		/*
		* Operators
		*/
		void operator=(const Vector3f& other);
		void operator=(const float other);
		void operator+=(const Vector3f& other);
		void operator-=(const Vector3f& other);
		void operator*=(const Vector3f& other);
		void operator/=(const Vector3f& other);
		void operator+=(const float other);
		void operator-=(const float other);
		void operator*=(const float other);
		void operator/=(const float other);

		float X;
		float Y;
		float Z;

	};
	static Vector3f operator+(const Vector3f& a, const Vector3f& b)
	{
		return Vector3f(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
	}
	static Vector3f operator-(const Vector3f& a, const Vector3f& b)
	{
		return Vector3f(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
	}
	static Vector3f operator*(const Vector3f& a, const Vector3f& b)
	{
		return Vector3f(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
	}
	static Vector3f operator/(const Vector3f& a, const Vector3f& b)
	{
		return Vector3f(a.X / b.X, a.Y / b.Y, a.Z / b.Z);
	}
	static Vector3f operator+(const Vector3f& a, float value)
	{
		return Vector3f(a.X + value, a.Y + value, a.Z + value);
	}
	static Vector3f operator-(const Vector3f& a, float value)
	{
		return Vector3f(a.X - value, a.Y - value, a.Z - value);
	}
	static Vector3f operator*(const Vector3f& a, float value)
	{
		return Vector3f(a.X * value, a.Y * value, a.Z * value);
	}
	static Vector3f operator/(const Vector3f& a, float value)
	{
		return Vector3f(a.X / value, a.Y / value, a.Z / value);
	}

}