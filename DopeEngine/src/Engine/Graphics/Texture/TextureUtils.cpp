#include "TextureUtils.h"
#include <Engine/Core/Assert.h>


namespace DopeEngine
{
	unsigned int TextureUtils::get_format_size(const TextureFormat format)
	{
		switch (format)
		{
			case DopeEngine::TextureFormat::R8unorm:
				return 1;
				break;
			case DopeEngine::TextureFormat::RGB8f:
				return 3;
				break;
			case DopeEngine::TextureFormat::RGB16f:
				return 6;
				break;
			case DopeEngine::TextureFormat::RGB32f:
				return 12;
				break;
			case DopeEngine::TextureFormat::RGBA8f:
				return 4;
				break;
			case DopeEngine::TextureFormat::RGBA16f:
				return 8;
				break;
			case DopeEngine::TextureFormat::RGBA32F:
				return 16;
				break;
			default:
				ASSERT(false, "TextureUtils", "Invalid TextureFormat, cannot produce the format size");
				break;
		}
	}
}