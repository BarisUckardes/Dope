#include "Vector2f.h"
#include "Vector2f.h"
#include <cmath>


namespace DopeEngine
{
    float Vector2f::get_length() const
    {
        return (sqrt(X * X) + sqrt(Y * Y));
    }

    Vector2f Vector2f::get_normalized() const
    {
        const float length = get_length();
        return Vector2f(X / length,Y / length);
    }

    void Vector2f::normalize_this()
    {
        const float length = get_length();
        X /= length;
        Y /= length;
    }

	void Vector2f::operator=(const Vector2f& other)
	{
		X = other.X;
		Y = other.Y;
	}
	void Vector2f::operator=(const float other)
	{
		X = Y = other;
	}
	void Vector2f::operator+=(const Vector2f& other)
	{
		X += other.X;
		Y += other.Y;
	}
	void Vector2f::operator-=(const Vector2f& other)
	{
		X -= other.X;
		Y -= other.Y;
	}
	void Vector2f::operator*=(const Vector2f& other)
	{
		X *= other.X;
		Y *= other.Y;
	}
	void Vector2f::operator/=(const Vector2f& other)
	{
		X /= other.X;
		Y /= other.Y;
	}
	void Vector2f::operator+=(const float other)
	{
		X += other;
		Y += other;
	}
	void Vector2f::operator-=(const float other)
	{
		X -= other;
		Y -= other;
	}
	void Vector2f::operator*=(const float other)
	{
		X *= other;
		Y *= other;
	}
	void Vector2f::operator/=(const float other)
	{
		X /= other;
		Y /= other;
	}


}