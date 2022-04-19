#pragma once
#include <Engine/Graphics/Texture/TextureDescription.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX11TextureUtils
	{
	public:
		DX11TextureUtils() = delete;
		~DX11TextureUtils() = delete;

		FORCEINLINE static D3D11_USAGE get_usage(const TextureUsage usage);
		FORCEINLINE static unsigned int get_bind_flags(const TextureUsage usage);
		FORCEINLINE static DXGI_FORMAT get_format(const TextureFormat format);
		FORCEINLINE static D3D11_SRV_DIMENSION get_dimension(const TextureType type);
		FORCEINLINE static unsigned int get_cpu_access(const TextureUsage usage);
	};
}