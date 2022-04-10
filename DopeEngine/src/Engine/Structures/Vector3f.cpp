#include "Vector3f.h"
#include <cmath>s
namespace DopeEngine
{
	float Vector3f::dot_product(const Vector3f& a, const Vector3f& b)
	{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
	}
	Vector3f Vector3f::cross_product(const Vector3f& a, const Vector3f& b)
	{
		return Vector3f(
			a.Y * b.Z - a.Z * b.Y,
			a.Z * b.X - a.X * b.Z,
			a.X * b.Y - a.Y * b.X);
	}
	float Vector3f::get_length() const
	{
		return (sqrt(X*X) + sqrt(Y*Y) + sqrt(Z*Z));
	}
	Vector3f Vector3f::get_normalized() const
	{
		const float length = get_length();
		return Vector3f(X/length,Y/length,Z/length);
	}
	void Vector3f::normalize_this()
	{
		const float length = get_length();
		X /= length;
		Y /= length;
		Z /= length;
	}
}