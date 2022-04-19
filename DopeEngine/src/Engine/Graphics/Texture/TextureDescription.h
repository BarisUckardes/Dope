#pragma once
#include <Engine/Core/Definitions.h>
#include <Engine/Graphics/Texture/TextureFormat.h>
#include <Engine/Graphics/Texture/TextureType.h>
#include <Engine/Graphics/Texture/TextureUsage.h>
namespace DopeEngine
{
	/// <summary>
	/// Description for creating a texture
	/// </summary>
	struct DOPE_ENGINE_API TextureDescription
	{
		TextureDescription(
			const unsigned int width, const unsigned int height, const unsigned int depth,
			const unsigned int mipcount,
			const TextureUsage usage,const TextureFormat format,const TextureType type,const Byte* initialData) : Width(width),Height(height),Depth(depth),MipCount(mipcount),Usage(usage),Format(format),Type(type),InitialData(initialData) {}
		TextureDescription() = default;
		~TextureDescription() = default;

		/// <summary>
		/// The usage flags
		/// </summary>
		TextureUsage Usage;

		/// <summary>
		/// Texture pixel format
		/// </summary>
		TextureFormat Format;

		/// <summary>
		/// Texture dimension type
		/// </summary>
		TextureType Type;

		/// <summary>
		/// Width in pixels
		/// </summary>
		unsigned int Width;

		/// <summary>
		/// Height in pixels
		/// </summary>
		unsigned int Height;

		/// <summary>
		/// Depth in pixels
		/// </summary>
		unsigned int Depth;

		/// <summary>
		/// Minification levels count
		/// </summary>
		unsigned int MipCount;

		/// <summary>
		/// Initial data ptr for readonly textures
		/// </summary>
		const Byte* InitialData;
	};
}