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

		/// <summary>
		/// Returns the square root of the given value
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		static  float square_root(const float value);

		/// <summary>
		/// Returns the sin of the given rads
		/// </summary>
		/// <param name="rads"></param>
		/// <returns></returns>
		static  float sin(const float rads);

		/// <summary>
		/// Returns the cos of the given rads
		/// </summary>
		/// <param name="rads"></param>
		/// <returns></returns>
		static  float cos(const float rads);

		/// <summary>
		/// Returns the tan of the given rads
		/// </summary>
		/// <param name="rads"></param>
		/// <returns></returns>
		static  float tan(const float rads);

		/// <summary>
		/// Linearly interpolates the value
		/// </summary>
		/// <param name="from"></param>
		/// <param name="to"></param>
		/// <param name="alpha"></param>
		/// <returns></returns>
		static  float linear_interpolate(const float from, const float to, const float alpha);

		/// <summary>
		/// Returns the absolute value of the given value
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		static  float absolute(const float value);

		/// <summary>
		/// Clamps the given value between min/max
		/// </summary>
		/// <param name="value"></param>
		/// <param name="min"></param>
		/// <param name="max"></param>
		/// <returns></returns>
		static  float clamp(const float value, const float min, const float max);

		/// <summary>
		/// Returns the min value between two values
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static  float min(const float a, const float b);

		/// <summary>
		/// Returns the max value between two values
		/// </summary>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		static  float max(const float a, const float b);
	};


}