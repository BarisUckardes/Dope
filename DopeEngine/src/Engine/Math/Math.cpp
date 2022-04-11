#include "Math.h"
#include <cmath>

namespace DopeEngine
{
	FORCEINLINE float Math::square_root(float value)
	{
		return sqrt(value);
	}
	FORCEINLINE float Math::cos(float rads)
	{
		return cos(rads);
	}
	FORCEINLINE float Math::sin(float rads)
	{
		return sin(rads);
	}
	FORCEINLINE float Math::tan(float rads)
	{
		return tan(rads);
	}
	FORCEINLINE float Math::linear_interpolate(float from, float to, float alpha)
	{
		const float direction = to - from;
		return from + direction * alpha;
	}
	FORCEINLINE float Math::absolute(float value)
	{
		return (value > 0) ? value : -value;
	}
	FORCEINLINE float Math::clamp(float value, float min, float max)
	{
		return value > max ? max : value < min ? min : value;
	}
	FORCEINLINE float Math::min(float a, float b)
	{
		return a > b ? b : a;
	}
	FORCEINLINE float Math::max(float a, float b)
	{
		return a > b ? a : b;
	}
}