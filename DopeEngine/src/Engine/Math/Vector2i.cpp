#include "Vector2i.h"
#include <cmath>
namespace DopeEngine
{
	float Vector2i::get_length() const
	{
		return (sqrt(X * X) + sqrt(Y * Y));
	}
	Vector2i Vector2i::get_normalized() const
	{
		const float length = get_length();
		return Vector2i(X / length, Y / length);
	}
	void Vector2i::normalize_this()
	{
		const float length = get_length();
		X /= length;
		Y /= length;
	}
	void Vector2i::operator=(const Vector2i& other)
	{
		X = other.X;
		Y = other.Y;
	}
	void Vector2i::operator=(const float other)
	{
		X = Y = other;
	}
	void Vector2i::operator+=(const Vector2i& other)
	{
		X += other.X;
		Y += other.Y;
	}
	void Vector2i::operator-=(const Vector2i& other)
	{
		X -= other.X;
		Y -= other.Y;
	}
	void Vector2i::operator*=(const Vector2i& other)
	{
		X *= other.X;
		Y *= other.Y;
	}
	void Vector2i::operator/=(const Vector2i& other)
	{
		X /= other.X;
		Y /= other.Y;
	}
	void Vector2i::operator+=(const float other)
	{
		X += other;
		Y += other;
	}
	void Vector2i::operator-=(const float other)
	{
		X -= other;
		Y -= other;
	}
	void Vector2i::operator*=(const float other)
	{
		X *= other;
		Y *= other;
	}
	void Vector2i::operator/=(const float other)
	{
		X /= other;
		Y /= other;
	}
}