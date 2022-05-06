#include "VKTextureUtils.h"
#include <Engine/Core/Assert.h>


namespace DopeEngine
{
    TextureFormat VKTextureUtils::get_format(const VkFormat vkFormat)
    {
        switch (vkFormat)
        {
            case VK_FORMAT_R8_UNORM:
                return TextureFormat::R8unorm;
                break;
            case VK_FORMAT_R8G8B8_UNORM:
                return TextureFormat::RGB8f;
                break;
            case VK_FORMAT_R16G16B16_SFLOAT:
                return TextureFormat::RGB16f;
                break;
            case VK_FORMAT_R32G32B32_SFLOAT:
                return TextureFormat::RGB32f;
                break;
            case VK_FORMAT_R8G8B8A8_UNORM:
                return TextureFormat::RGBA8unorm;
                break;
            case VK_FORMAT_R16G16B16A16_SFLOAT:
                return TextureFormat::RGBA16f;
                break;
            case VK_FORMAT_R32G32B32A32_SFLOAT:
                return TextureFormat::RGBA32F;
                break;
            default:
                ASSERT(false, "VKTextureUtils", "Invalid VkFormat value, cannot produce TextureFormat");
                break;
        }
    }

    VkFormat VKTextureUtils::get_vk_format(const TextureFormat format)
    {
        switch (format)
        {
            case DopeEngine::TextureFormat::R8unorm:
                return VK_FORMAT_R8_UNORM;
                break;
            case DopeEngine::TextureFormat::RGB8f:
                return VK_FORMAT_R8G8B8_UNORM;
                break;
            case DopeEngine::TextureFormat::RGB16f:
                return VK_FORMAT_R16G16B16_SFLOAT;
                break;
            case DopeEngine::TextureFormat::RGB32f:
                return VK_FORMAT_R32G32B32_SFLOAT;
                break;
            case DopeEngine::TextureFormat::RGBA8f:
                return VK_FORMAT_R8G8B8A8_UNORM;
                break;
            case DopeEngine::TextureFormat::RGBA8unorm:
                return VK_FORMAT_R8G8B8A8_UNORM;
                break;
            case DopeEngine::TextureFormat::RGBA16f:
                return VK_FORMAT_R16G16B16A16_SFLOAT;
                break;
            case DopeEngine::TextureFormat::RGBA32F:
                return VK_FORMAT_R32G32B32A32_SFLOAT;
                break;
            default:
                ASSERT(false,"VKTextureUtils", "Invalid TextureFormat value, cannot produce VkFormat");
                break;
        }
    }

    VkImageViewType VKTextureUtils::get_vk_image_view_type( TextureType usage)
    {
        switch (usage)
        {
            case DopeEngine::TextureType::Texture1D:
                return VK_IMAGE_VIEW_TYPE_1D;
                break;
            case DopeEngine::TextureType::Texture2D:
                return VK_IMAGE_VIEW_TYPE_2D;
                break;
            case DopeEngine::TextureType::Texture3D:
                return VK_IMAGE_VIEW_TYPE_3D;
                break;
            case DopeEngine::TextureType::CubeTexture:
                return VK_IMAGE_VIEW_TYPE_CUBE;
                break;
            default:
                ASSERT(false, "VKTextureUtils", "Invalid TextureType, cannot produce VkImageViewType");
                break;
        }
    }

}