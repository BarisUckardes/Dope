#include "Math.h"
#include <cmath>

namespace DopeEngine
{
	float Math::square_root(float value)
	{
		return sqrt(value);
	}
	float Math::cos(float rads)
	{
		return cosf(rads);
	}
	float Math::sin(float rads)
	{
		return sinf(rads);
	}
	float Math::tan(float rads)
	{
		return tanf(rads);
	}
	float Math::linear_interpolate(float from, float to, float alpha)
	{
		const float direction = to - from;
		return from + direction * alpha;
	}
	float Math::absolute(float value)
	{
		return (value > 0) ? value : -value;
	}
	float Math::clamp(float value, float min, float max)
	{
		return value > max ? max : value < min ? min : value;
	}
	float Math::minn(float a, float b)
	{
		return a > b ? b : a;
	}
	float Math::maxx(float a, float b)
	{
		return a > b ? a : b;
	}
}