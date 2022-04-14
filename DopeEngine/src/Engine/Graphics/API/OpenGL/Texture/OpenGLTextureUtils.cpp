#include "OpenGLTextureUtils.h"
#include <Glad/glad.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	TEXTURE_FORMAT OpenGLTextureUtils::get_format(const TextureFormat format)
	{
		switch (format)
		{
			case DopeEngine::TextureFormat::Red:
				return GL_RED;
				break;
			case DopeEngine::TextureFormat::RGB8f:
				return GL_RGB;
				break;
			case DopeEngine::TextureFormat::RGB16f:
				return GL_RGB;
				break;
			case DopeEngine::TextureFormat::RGB32f:
				return GL_RGB;
				break;
			case DopeEngine::TextureFormat::RGBA8f:
				return GL_RGBA;
				break;
			case DopeEngine::TextureFormat::RGBA16f:
				return GL_RGBA;
				break;
			case DopeEngine::TextureFormat::RGBA32F:
				return GL_RGBA;
				break;
			default:
				return GL_NONE;
				break;
		}
	}
	TEXTURE_INTERNAL_FORMAT OpenGLTextureUtils::get_internal_format(const TextureFormat format)
	{
		switch (format)
		{
			case DopeEngine::TextureFormat::Red:
				return GL_RED;
				break;
			case DopeEngine::TextureFormat::RGB8f:
				return GL_RGB8;
				break;
			case DopeEngine::TextureFormat::RGB16f:
				return GL_RGB16F;
				break;
			case DopeEngine::TextureFormat::RGB32f:
				return GL_RGB32F;
				break;
			case DopeEngine::TextureFormat::RGBA8f:
				return GL_RGBA8;
				break;
			case DopeEngine::TextureFormat::RGBA16f:
				return GL_RGBA16F;
				break;
			case DopeEngine::TextureFormat::RGBA32F:
				return GL_RGBA32F;
				break;
			default:
				break;
		}
	}
	TEXTURE_DATA_TYPE OpenGLTextureUtils::get_data_type(const TextureFormat format)
	{
		switch (format)
		{
			case DopeEngine::TextureFormat::Red:
				return GL_UNSIGNED_BYTE;
				break;
			case DopeEngine::TextureFormat::RGB8f:
				return GL_UNSIGNED_BYTE;
				break;
			case DopeEngine::TextureFormat::RGB16f:
				return GL_UNSIGNED_BYTE;
				break;
			case DopeEngine::TextureFormat::RGB32f:
				return GL_UNSIGNED_BYTE;
				break;
			case DopeEngine::TextureFormat::RGBA8f:
				return GL_UNSIGNED_BYTE;
				break;
			case DopeEngine::TextureFormat::RGBA16f:
				return GL_UNSIGNED_BYTE;
				break;
			case DopeEngine::TextureFormat::RGBA32F:
				return GL_UNSIGNED_BYTE;
				break;
			default:
				break;
		}
	}
	TEXTURE_TYPE OpenGLTextureUtils::get_texture_type(const TextureType type)
	{
		switch (type)
		{
			case DopeEngine::TextureType::Texture1D:
				return GL_TEXTURE_1D;
				break;
			case DopeEngine::TextureType::Texture2D:
				return GL_TEXTURE_2D;
				break;
			case DopeEngine::TextureType::Texture3D:
				return GL_TEXTURE_3D;
				break;
			case DopeEngine::TextureType::CubeTexture:
				return GL_TEXTURE_CUBE_MAP;
				break;
			default:
				ASSERT(false, "OpenGLTextureUtils", "Invalid TextureType, cannot convert TextureType to GL_TEXTURE_?");
				break;
		}
	}
}