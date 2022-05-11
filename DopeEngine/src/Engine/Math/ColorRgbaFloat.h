#pragma once
#include <Engine/Core/Symbols.h>
namespace DopeEngine
{
	/// <summary>
	/// Color holds r-g-b-a as float
	/// </summary>
	struct DOPE_ENGINE_API ColorRgbaFloat final
	{
		ColorRgbaFloat(const float red, const float green, const float blue, const float alpha) : Red(red), Green(green), Blue(blue), Alpha(alpha) {}
		ColorRgbaFloat() : Red(0), Green(0), Blue(0), Alpha(0) {}
		~ColorRgbaFloat() = default;

		/// <summary>
		/// Red component
		/// </summary>
		float Red;

		/// <summary>
		/// Green component
		/// </summary>
		float Green;

		/// <summary>
		/// Blue component
		/// </summary>
		float Blue;

		/// <summary>
		/// Alpha component
		/// </summary>
		float Alpha;
	};

	static ColorRgbaFloat operator*(const ColorRgbaFloat& a, const ColorRgbaFloat& b)
	{
		return ColorRgbaFloat(a.Red * b.Red, a.Green * b.Green, a.Blue * b.Blue, a.Alpha * b.Alpha);
	}
}