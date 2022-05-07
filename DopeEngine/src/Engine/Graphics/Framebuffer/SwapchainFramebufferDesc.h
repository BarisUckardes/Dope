#pragma once
#include <Engine/Graphics/Texture/TextureFormat.h>

namespace DopeEngine
{
	/// <summary>
	/// Used in creation of swapchain framebuffers
	/// </summary>
	struct DOPE_ENGINE_API SwapchainFramebufferDesc
	{

		SwapchainFramebufferDesc(const unsigned int width,const unsigned int height,const unsigned int count,const TextureFormat format,const TextureFormat depthFormat,const bool generateDepth) :
			Width(width),Height(height),Count(count),Format(format),DepthFormat(depthFormat),GenerateDepth(generateDepth)
		{}
		SwapchainFramebufferDesc() = default;
		~SwapchainFramebufferDesc() = default;

		/// <summary>
		/// The width of the backbuffers
		/// </summary>
		unsigned int Width;

		/// <summary>
		/// The height of the backbuffers
		/// </summary>
		unsigned int Height;

		/// <summary>
		/// The backbuffer count
		/// </summary>
		unsigned int Count;

		/// <summary>
		/// Backbuffer formats
		/// </summary>
		TextureFormat Format;

		/// <summary>
		/// Depth format
		/// </summary>
		TextureFormat DepthFormat;

		/// <summary>
		/// Whether generate depth or not
		/// </summary>
		bool GenerateDepth;
	};
}