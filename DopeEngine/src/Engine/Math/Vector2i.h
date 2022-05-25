#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// X-Y-Z Axis Float Vector
	/// </summary>
	class DOPE_ENGINE_API Vector2i final
	{
	public:

		Vector2i(const float x, const float y) : X(x), Y(y) {}
		Vector2i(const float value) : X(value), Y(value) {}
		Vector2i() : X(0), Y(0) {}

		FORCEINLINE float get_length() const;
		FORCEINLINE Vector2i get_normalized() const;
		FORCEINLINE void normalize_this();

		/*
		* Operators
		*/
		void operator=(const Vector2i& other);
		void operator=(const float other);
		void operator+=(const Vector2i& other);
		void operator-=(const Vector2i& other);
		void operator*=(const Vector2i& other);
		void operator/=(const Vector2i& other);
		void operator+=(const float other);
		void operator-=(const float other);
		void operator*=(const float other);
		void operator/=(const float other);

		float X;
		float Y;
	};
	static Vector2i operator+(const Vector2i& a, const Vector2i& b)
	{
		return Vector2i(a.X + b.X, a.Y + b.Y);
	}
	static Vector2i operator-(const Vector2i& a, const Vector2i& b)
	{
		return Vector2i(a.X - b.X, a.Y - b.Y);
	}
	static Vector2i operator*(const Vector2i& a, const Vector2i& b)
	{
		return Vector2i(a.X * b.X, a.Y * b.Y);
	}
	static Vector2i operator/(const Vector2i& a, const Vector2i& b)
	{
		return Vector2i(a.X / b.X, a.Y / b.Y);
	}
	static Vector2i operator+(const Vector2i& a, float value)
	{
		return Vector2i(a.X + value, a.Y + value);
	}
	static Vector2i operator-(const Vector2i& a, float value)
	{
		return Vector2i(a.X - value, a.Y - value);
	}
	static Vector2i operator*(const Vector2i& a, float value)
	{
		return Vector2i(a.X * value, a.Y * value);
	}
	static Vector2i operator/(const Vector2i& a, float value)
	{
		return Vector2i(a.X / value, a.Y / value);
	}

}