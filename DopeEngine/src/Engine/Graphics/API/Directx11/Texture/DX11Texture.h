#pragma once
#include <Engine/Graphics/Texture/Texture.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
namespace DopeEngine
{
	class DX11GraphicsDevice;
	class DOPE_ENGINE_API DX11Texture : public Texture
	{
	public:
		DX11Texture(const TextureDescription& desc, DX11GraphicsDevice* device);
		virtual ~DX11Texture() final override;

		FORCEINLINE DXPTR<ID3D11Texture1D> get_dx11_texture1d() const;
		FORCEINLINE DXPTR<ID3D11Texture2D> get_dx11_texture2d() const;
		FORCEINLINE DXPTR<ID3D11Texture3D> get_dx11_texture3d() const;

	private:
		void create(const TextureDescription& desc, DX11GraphicsDevice* device);
		void create2d(const TextureDescription& desc, DX11GraphicsDevice* device);
		void create3d(const TextureDescription& desc, DX11GraphicsDevice* device);
		void createcube(const TextureDescription& desc, DX11GraphicsDevice* device);
	private:
		DXPTR<ID3D11Texture1D> Texture1D;
		DXPTR<ID3D11Texture2D> Texture2D;
		DXPTR<ID3D11Texture3D> Texture3D;
	};


}