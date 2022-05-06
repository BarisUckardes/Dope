#pragma once
#include <Engine/Graphics/Texture/TextureFormat.h>
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>
#include <Engine/Graphics/Texture/TextureType.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API VKTextureUtils
	{
	public:
		VKTextureUtils() = delete;
		~VKTextureUtils() = delete;

		FORCEINLINE static TextureFormat get_format(const VkFormat vkFormat);
		FORCEINLINE static VkFormat get_vk_format(const TextureFormat format);
		FORCEINLINE static VkImageViewType get_vk_image_view_type(const TextureType usage);
	};
}