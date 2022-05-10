#include "Vector3i.h"
#include <cmath>
namespace DopeEngine
{
	float Vector3i::dot_product(const Vector3i& a, const Vector3i& b)
	{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
	}
	Vector3i Vector3i::cross_product(const Vector3i& a, const Vector3i& b)
	{
		return Vector3i(
			a.Y * b.Z - a.Z * b.Y,
			a.Z * b.X - a.X * b.Z,
			a.X * b.Y - a.Y * b.X);
	}
	float Vector3i::get_length() const
	{
		return (sqrt(X*X) + sqrt(Y*Y) + sqrt(Z*Z));
	}
	Vector3i Vector3i::get_normalized() const
	{
		const float length = get_length();
		return Vector3i(X/length,Y/length,Z/length);
	}
	void Vector3i::normalize_this()
	{
		const float length = get_length();
		X /= length;
		Y /= length;
		Z /= length;
	}
	void Vector3i::operator=(const Vector3i& other)
	{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
	}
	void Vector3i::operator=(const float other)
	{
		X = Y = Z = other;
	}
	void Vector3i::operator+=(const Vector3i& other)
	{
		X += other.X;
		Y += other.Y;
		Z += other.Z;

	}
	void Vector3i::operator-=(const Vector3i& other)
	{
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;
	}
	void Vector3i::operator*=(const Vector3i& other)
	{
		X *= other.X;
		Y *= other.Y;
		Z *= other.Z;
	}
	void Vector3i::operator/=(const Vector3i& other)
	{
		X /= other.X;
		Y /= other.Y;
		Z /= other.Z;
	}
	void Vector3i::operator+=(const float other)
	{
		X += other;
		Y += other;
		Z += other;
	}
	void Vector3i::operator-=(const float other)
	{
		X -= other;
		Y -= other;
		Z -= other;
	}
	void Vector3i::operator*=(const float other)
	{
		X *= other;
		Y *= other;
		Z *= other;
	}
	void Vector3i::operator/=(const float other)
	{
		X /= other;
		Y /= other;
		Z /= other;
	}
}