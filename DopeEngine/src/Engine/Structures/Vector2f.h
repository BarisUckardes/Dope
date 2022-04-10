#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// X-Y Axis Float Vector
	/// </summary>
	class Vector2f
	{
	public:
		Vector2f(const float x, const float y) : X(x),Y(y) {}
		Vector2f(const float value) : X(value),Y(value) {}
		Vector2f() : X(0),Y(0) {}

		/// <summary>
		/// Returns the length of the vector(distance from the origin)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE float get_length() const;

		/// <summary>
		/// Returns it as a unit vector
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector2f get_normalized() const;

		/// <summary>
		/// Makes this vector a unit vector
		/// </summary>
		FORCEINLINE void normalize_this();

		/// <summary>
		/// The x-axis component
		/// </summary>
		float X;

		/// <summary>
		/// The y-axis component
		/// </summary>
		float Y;

		/*
		* Operators
		*/
		void operator=(const Vector2f& other);
		void operator=(const float other);
		void operator+=(const Vector2f& other);
		void operator-=(const Vector2f& other);
		void operator*=(const Vector2f& other);
		void operator/=(const Vector2f& other);
		void operator+=(const float other);
		void operator-=(const float other);
		void operator*=(const float other);
		void operator/=(const float other);
	};

	static Vector2f operator+(const Vector2f& a, const Vector2f& b)
	{
		return Vector2f(a.X + b.X, a.Y + b.Y);
	}
	static Vector2f operator-(const Vector2f& a, const Vector2f& b)
	{
		return Vector2f(a.X - b.X, a.Y - b.Y);
	}
}