#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Framebuffer output description for the Pipeline
	/// </summary>
	struct DOPE_ENGINE_API OutputDescription
	{
		OutputDescription(const unsigned int offsetX,const unsigned int offsetY,const unsigned int width,const unsigned int height) : OffsetX(offsetX),OffsetY(offsetY),Width(width),Height(height) {}
		OutputDescription() = default;
		~OutputDescription() = default;

		/// <summary>
		/// Pixel start offset x
		/// </summary>
		unsigned int OffsetX;

		/// <summary>
		/// Pixel start offset y
		/// </summary>
		unsigned int OffsetY;

		/// <summary>
		/// Draw rect width
		/// </summary>
		unsigned int Width;

		/// <summary>
		/// Draw rect height
		/// </summary>
		unsigned int Height;
	};
}