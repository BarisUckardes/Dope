#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	#define PI 3.14159265359
	#define DegToRadCoef 0.01745329252f
	#define RadToDegCoef 357.295779513f

	class DOPE_ENGINE_API Math
	{
	public:
		Math() = delete;
		~Math() = delete;

		static float square_root(const float value);
		static float sin(const float rads);
		static float cos(const float rads);
		static float tan(const float rads);
		static float linear_interpolate(const float from, const float to, const float alpha);
		static float absolute(const float value);
		static float clamp(const float value, const float min, const float max);
		static float minn(const float a, const float b);
		static float maxx(const float a, const float b);
	};


}