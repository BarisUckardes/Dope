#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// X-Y-Z Axis Float Vector
	/// </summary>
	class DOPE_ENGINE_API Vector3i final
	{
	public:
		static float dot_product(const Vector3i& a, const Vector3i& b);
		static Vector3i cross_product(const Vector3i& a, const Vector3i& b);

		Vector3i(const float x, const float y, const float z) : X(x), Y(y), Z(z) {}
		Vector3i(const float value) : X(value), Y(value), Z(value) {}
		Vector3i() : X(0), Y(0), Z(0) {}

		FORCEINLINE float get_length() const;
		FORCEINLINE Vector3i get_normalized() const;
		FORCEINLINE void normalize_this();

		/*
		* Operators
		*/
		void operator=(const Vector3i& other);
		void operator=(const float other);
		void operator+=(const Vector3i& other);
		void operator-=(const Vector3i& other);
		void operator*=(const Vector3i& other);
		void operator/=(const Vector3i& other);
		void operator+=(const float other);
		void operator-=(const float other);
		void operator*=(const float other);
		void operator/=(const float other);

		float X;
		float Y;
		float Z;

	};
	static Vector3i operator+(const Vector3i& a, const Vector3i& b)
	{
		return Vector3i(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
	}
	static Vector3i operator-(const Vector3i& a, const Vector3i& b)
	{
		return Vector3i(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
	}
	static Vector3i operator*(const Vector3i& a, const Vector3i& b)
	{
		return Vector3i(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
	}
	static Vector3i operator/(const Vector3i& a, const Vector3i& b)
	{
		return Vector3i(a.X / b.X, a.Y / b.Y, a.Z / b.Z);
	}
	static Vector3i operator+(const Vector3i& a, float value)
	{
		return Vector3i(a.X + value, a.Y + value, a.Z + value);
	}
	static Vector3i operator-(const Vector3i& a, float value)
	{
		return Vector3i(a.X - value, a.Y - value, a.Z - value);
	}
	static Vector3i operator*(const Vector3i& a, float value)
	{
		return Vector3i(a.X * value, a.Y * value, a.Z * value);
	}
	static Vector3i operator/(const Vector3i& a, float value)
	{
		return Vector3i(a.X / value, a.Y / value, a.Z / value);
	}

}