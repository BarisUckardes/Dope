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

		TextureUsage Usage;
		TextureFormat Format;
		TextureType Type;
		unsigned int Width;
		unsigned int Height;
		unsigned int Depth;
		unsigned int MipCount;
		const Byte* InitialData;
	};
}