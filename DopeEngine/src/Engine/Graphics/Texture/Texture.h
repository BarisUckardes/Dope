#pragma once
#include <Engine/Graphics/Device/GraphicsDeviceObject.h>
#include <Engine/Graphics/Texture/TextureDescription.h>
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics api agnostic texture abstraction class
	/// </summary>
	class DOPE_ENGINE_API Texture : public GraphicsDeviceObject
	{
	public:
		Texture(const TextureDescription& description);
		virtual ~Texture() = default;

		/// <summary>
		/// Returns the usage flags
		/// </summary>
		/// <returns></returns>
		TextureUsage get_usage() const;

		/// <summary>
		/// Returns the texture format
		/// </summary>
		/// <returns></returns>
		TextureFormat get_format() const;

		/// <summary>
		/// Returns the type of the texture
		/// </summary>
		/// <returns></returns>
		TextureType get_type() const;

		/// <summary>
		/// Returns the width of this texture in pixels
		/// </summary>
		/// <returns></returns>
		unsigned int get_width() const;

		/// <summary>
		/// Returns the height of this texture in pixels
		/// </summary>
		/// <returns></returns>
		unsigned int get_height() const;

		/// <summary>
		/// Returns the depth of this texture in pixels
		/// </summary>
		/// <returns></returns>
		unsigned int get_depth() const;

		/// <summary>
		/// Returns the mip level count of this texture
		/// </summary>
		/// <returns></returns>
		unsigned int get_mip_count() const;

	private:
		TextureUsage Usage;
		TextureFormat Format;
		TextureType Type;
		unsigned int Width;
		unsigned int Height;
		unsigned int Depth;
		unsigned int MipCount;
	};


}