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

		FORCEINLINE ID3D11Texture2D* get_dx11_texture() const;
		FORCEINLINE ID3D11ShaderResourceView* get_dx11_shader_resource() const;
	private:
		void create(const TextureDescription& desc, DX11GraphicsDevice* device);
		void create2d(const TextureDescription& desc, DX11GraphicsDevice* device);
		void create3d(const TextureDescription& desc, DX11GraphicsDevice* device);
		void createcube(const TextureDescription& desc, DX11GraphicsDevice* device);
		void createShaderResourceView(DX11GraphicsDevice* device,D3D_SRV_DIMENSION dimension,DXGI_FORMAT format);
	private:
		ID3D11Texture2D* TextureBase;
		ID3D11ShaderResourceView* ResourceView;
	};


}