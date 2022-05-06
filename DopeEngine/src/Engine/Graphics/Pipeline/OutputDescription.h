#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Array.h>
#include <Engine/Graphics/Texture/TextureFormat.h>
namespace DopeEngine
{
	/// <summary>
	/// Framebuffer output description for the Pipeline
	/// </summary>
	struct DOPE_ENGINE_API OutputDescription
	{
		OutputDescription(const unsigned int offsetX,const unsigned int offsetY,const unsigned int width,const unsigned int height,
			const Array<TextureFormat>& outputFormats,const bool swapchain) :
			OffsetX(offsetX),OffsetY(offsetY),Width(width),Height(height),OutputFormats(outputFormats),Swapchain(swapchain) {}
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

		/// <summary>
		/// Whether its a swapchain or not
		/// </summary>
		bool Swapchain;
		/// <summary>
		/// Attachment formats
		/// </summary>
		Array<TextureFormat> OutputFormats;

	};
}