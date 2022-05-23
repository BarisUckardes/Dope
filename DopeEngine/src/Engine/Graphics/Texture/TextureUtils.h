#pragma once
#include <Engine/Graphics/Texture/TextureFormat.h>

namespace DopeEngine
{
	/// <summary>
	/// Util operations for texture
	/// </summary>
	class DOPE_ENGINE_API TextureUtils
	{
	public:
		TextureUtils() = delete;
		~TextureUtils() = delete;

		static unsigned int get_format_size(const TextureFormat format);
	};


}