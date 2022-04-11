#pragma once
#include <Engine/Graphics/Device/DeviceObject.h>
#include <Engine/Graphics/Texture/TextureDescription.h>
#include <Engine/Core/Definitions.h>
namespace DopeEngine
{
	/// <summary>
	/// Graphics api agnostic texture abstraction class
	/// </summary>
	class DOPE_ENGINE_API Texture : public DeviceObject
	{
	public:
		Texture(const TextureDescription& description);
		virtual ~Texture() = default;

		/// <summary>
		/// Returns the usage flags
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureUsage get_usage() const;

		/// <summary>
		/// Returns the texture format
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureFormat get_format() const;

		/// <summary>
		/// Returns the type of the texture
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureType get_type() const;

		/// <summary>
		/// Returns the width of this texture in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_width() const;

		/// <summary>
		/// Returns the height of this texture in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_height() const;

		/// <summary>
		/// Returns the depth of this texture in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_depth() const;

		/// <summary>
		/// Returns the mip level count of this texture
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_mip_count() const;

		/// <summary>
		/// updates the texture data
		/// </summary>
		/// <param name="data"></param>
		virtual void update(const Byte* data) = 0;
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