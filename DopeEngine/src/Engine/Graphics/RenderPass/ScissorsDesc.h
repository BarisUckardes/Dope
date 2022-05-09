#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	struct DOPE_ENGINE_API ScissorsDesc
	{
		ScissorsDesc(const float offsetX,const float offsetY,const float width,const float height) : OffsetX(offsetX),OffsetY(offsetY),Width(width),Height(height) {}
		ScissorsDesc() : OffsetX(0),OffsetY(0),Width(0),Height(0) {}
		~ScissorsDesc() = default;

		float OffsetX;
		float OffsetY;
		float Width;
		float Height;
	};
}