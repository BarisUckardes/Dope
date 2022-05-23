#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Required fields to create a Viewport state
	/// </summary>
	struct DOPE_ENGINE_API ViewportDesc
	{
		ViewportDesc(const unsigned int offsetX, const unsigned int offsetY, const unsigned int width, const unsigned int height, const float minDepth, const float maxDepth) :
			OffsetX(offsetX),OffsetY(offsetY),Width(width),Height(height),MinDepth(minDepth),MaxDepth(maxDepth) {}
		ViewportDesc() : OffsetX(0),OffsetY(0),Width(0),Height(0),MinDepth(0),MaxDepth(0) {}
		~ViewportDesc() = default;

		unsigned int OffsetX;
		unsigned int OffsetY;
		unsigned int Width;
		unsigned int Height;
		float MinDepth;
		float MaxDepth;
	};
}