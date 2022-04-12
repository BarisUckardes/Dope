#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	/// <summary>
	/// Color holds r-g-b-a as byte
	/// </summary>
	struct DOPE_ENGINE_API ColorRgbaByte final
	{
		ColorRgbaByte(const Byte red, const Byte green, const Byte blue, const Byte alpha) : Red(red),Green(green),Blue(blue),Alpha(alpha) {}
		ColorRgbaByte() : Red(0),Green(0),Blue(0),Alpha(0) {}
		~ColorRgbaByte() = default;

		/// <summary>
		/// Red component
		/// </summary>
		Byte Red;

		/// <summary>
		/// Green component
		/// </summary>
		Byte Green;

		/// <summary>
		/// Blue component
		/// </summary>
		Byte Blue;

		/// <summary>
		/// Alpha component
		/// </summary>
		Byte Alpha;
	};
}