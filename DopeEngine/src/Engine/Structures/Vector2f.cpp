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

}