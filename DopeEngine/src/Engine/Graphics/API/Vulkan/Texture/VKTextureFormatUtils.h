#pragma once
#include <Engine/Graphics/Texture/TextureFormat.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API VKTextureFormatUtils
	{
	public:
		VKTextureFormatUtils() = delete;
		~VKTextureFormatUtils() = delete;

		FORCEINLINE static TextureFormat get_format(const unsigned int vkFormat);
		FORCEINLINE static unsigned int get_vk_format(const TextureFormat format);
	};


}