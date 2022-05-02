#pragma once
#include <Engine/Graphics/Texture/TextureFormat.h>
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API VKTextureFormatUtils
	{
	public:
		VKTextureFormatUtils() = delete;
		~VKTextureFormatUtils() = delete;

		FORCEINLINE static TextureFormat get_format(const VkFormat vkFormat);
		FORCEINLINE static VkFormat get_vk_format(const TextureFormat format);
	};


}