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


		/// <summary>
		/// Offset-X in screen coordinates
		/// </summary>
		unsigned int OffsetX;

		/// <summary>
		/// Offset-Y in screen coordinates
		/// </summary>
		unsigned int OffsetY;

		/// <summary>
		/// Width of the viewport rect
		/// </summary>
		unsigned int Width;

		/// <summary>
		/// Height of the viewport rect
		/// </summary>
		unsigned int Height;

		/// <summary>
		/// Min pixel depth
		/// </summary>
		float MinDepth;

		/// <summary>
		/// Max pixel depth
		/// </summary>
		float MaxDepth;
	};
}