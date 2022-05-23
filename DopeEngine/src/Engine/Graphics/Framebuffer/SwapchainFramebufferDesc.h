#pragma once
#include <Engine/Graphics/Texture/TextureFormat.h>

namespace DopeEngine
{
	/// <summary>
	/// Used in creation of swapchain framebuffers
	/// </summary>
	struct DOPE_ENGINE_API SwapchainFramebufferDesc
	{

		SwapchainFramebufferDesc(const unsigned int width,const unsigned int height,const unsigned int bufferCount,const TextureFormat format,const TextureFormat depthFormat,const bool generateDepth) :
			Width(width),Height(height),BufferCount(bufferCount),Format(format),DepthFormat(depthFormat),GenerateDepth(generateDepth)
		{}
		SwapchainFramebufferDesc() = default;
		~SwapchainFramebufferDesc() = default;

		unsigned int Width;
		unsigned int Height;
		unsigned int BufferCount;
		TextureFormat Format;
		TextureFormat DepthFormat;
		bool GenerateDepth;
	};
}