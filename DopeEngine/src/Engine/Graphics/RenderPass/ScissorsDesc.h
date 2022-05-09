#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	struct DOPE_ENGINE_API ScissorsDesc
	{
		ScissorsDesc(const unsigned int offsetX,const unsigned int offsetY,const unsigned int width,const unsigned int height) : OffsetX(offsetX),OffsetY(offsetY),Width(width),Height(height) {}
		ScissorsDesc() : OffsetX(0),OffsetY(0),Width(0),Height(0) {}
		~ScissorsDesc() = default;

		unsigned int OffsetX;
		unsigned int OffsetY;
		unsigned int Width;
		unsigned int Height;
	};
}