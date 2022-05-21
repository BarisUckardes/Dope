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

		/// <summary>
		/// Returns the format size in bytes
		/// </summary>
		/// <param name="format"></param>
		/// <returns></returns>
		static unsigned int get_format_size(const TextureFormat format);
	};


}