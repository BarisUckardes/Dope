#pragma once
#include <Engine/Graphics/Texture/TextureFormat.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API TextureUtils
	{
	public:
		TextureUtils() = delete;
		~TextureUtils() = delete;

		FORCEINLINE static unsigned int get_format_size(const TextureFormat format);
	};


}