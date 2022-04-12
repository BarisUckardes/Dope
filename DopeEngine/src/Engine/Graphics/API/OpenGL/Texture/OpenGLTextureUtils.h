#pragma once
#include <Engine/Graphics/Texture/TextureFormat.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>
namespace DopeEngine
{
	/// <summary>
	/// General purpose texture utils
	/// </summary>
	class DOPE_ENGINE_API OpenGLTextureUtils
	{
	public:
		OpenGLTextureUtils() = delete;
		~OpenGLTextureUtils() = delete;


		FORCEINLINE static TEXTURE_FORMAT get_format(const TextureFormat format);
		FORCEINLINE static TEXTURE_INTERNAL_FORMAT get_internal_format(const TextureFormat format);
		FORCEINLINE static TEXTURE_DATA_TYPE get_data_type(const TextureFormat format);

	};
}