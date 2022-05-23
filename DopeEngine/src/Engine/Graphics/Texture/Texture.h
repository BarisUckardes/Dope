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

		FORCEINLINE TextureUsage get_usage() const;
		FORCEINLINE TextureFormat get_format() const;
		FORCEINLINE TextureType get_type() const;
		FORCEINLINE unsigned int get_width() const;
		FORCEINLINE unsigned int get_height() const;
		FORCEINLINE unsigned int get_depth() const;
		FORCEINLINE unsigned int get_mip_count() const;
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