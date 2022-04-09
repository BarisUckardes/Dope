#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API ColorRgba
	{
	public:
		ColorRgba(const Byte red, const Byte green, const Byte blue, const Byte alpha) : Red(red),Green(green),Blue(blue),Alpha(alpha) {}
		ColorRgba() : Red(0),Green(0),Blue(0),Alpha(0) {}
		~ColorRgba() = default;

		Byte Red;
		Byte Green;
		Byte Blue;
		Byte Alpha;
	};


}