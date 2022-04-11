#include "Texture.h"

namespace DopeEngine
{
	Texture::Texture(const TextureDescription& description)
	{
		Usage = description.Usage;
		Format = description.Format;
		Type = description.Type;
		Width = description.Width;
		Height = description.Height;
		Depth = description.Depth;
		MipCount = description.MipCount;
	}
	TextureUsage Texture::get_usage() const
	{
		return Usage;
	}
	TextureFormat Texture::get_format() const
	{
		return Format;
	}
	TextureType Texture::get_type() const
	{
		return Type;
	}
	unsigned int Texture::get_width() const
	{
		return Width;
	}
	unsigned int Texture::get_height() const
	{
		return Height;
	}
	unsigned int Texture::get_depth() const
	{
		return Depth;
	}
	unsigned int Texture::get_mip_count() const
	{
		return MipCount;
	}
}