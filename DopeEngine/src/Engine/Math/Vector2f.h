#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// X-Y Axis Float Vector
	/// </summary>
	class DOPE_ENGINE_API Vector2f final
	{
	public:
		Vector2f(const float x, const float y) : X(x),Y(y) {}
		Vector2f(const float value) : X(value),Y(value) {}
		Vector2f() : X(0),Y(0) {}


		FORCEINLINE float get_length() const;
		FORCEINLINE Vector2f get_normalized() const;
		FORCEINLINE void normalize_this();

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

		float X;
		float Y;
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