#include "DX11Texture.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Texture/DX11TextureUtils.h>
namespace DopeEngine
{
	DX11Texture::DX11Texture(const TextureDescription& desc, DX11GraphicsDevice* device) : Texture(desc)
	{
		/*
		* Create
		*/
		create(desc, device);
	}
	DX11Texture::~DX11Texture()
	{

	}
	ID3D11Texture2D* DX11Texture::get_dx11_texture() const
	{
		return TextureBase;
	}
	ID3D11ShaderResourceView* DX11Texture::get_dx11_shader_resource() const
	{
		return ResourceView;
	}
	void DX11Texture::create(const TextureDescription& desc, DX11GraphicsDevice* device)
	{
		/*
		* Create texture desc
		*/
		const TextureType textureType = get_type();
		D3D_SRV_DIMENSION dimension = D3D_SRV_DIMENSION_UNKNOWN;
		switch (textureType)
		{
			case DopeEngine::TextureType::Texture1D:
				dimension =  D3D_SRV_DIMENSION_TEXTURE1D;
				break;
			case DopeEngine::TextureType::Texture2D:
				dimension = D3D_SRV_DIMENSION_TEXTURE2D;
				create2d(desc, device);
				break;
			case DopeEngine::TextureType::Texture3D:
				dimension = D3D_SRV_DIMENSION_TEXTURE3D;
				create3d(desc, device);
				break;
			case DopeEngine::TextureType::CubeTexture:
				dimension = D3D_SRV_DIMENSION_TEXTURECUBE;
				createcube(desc, device);
				break;
			default:
				break;
		}

		/*
		* Validate and create shader resource view
		*/
		createShaderResourceView(device,dimension, DX11TextureUtils::get_format(desc.Format));
	}
	void DX11Texture::create2d(const TextureDescription& desc, DX11GraphicsDevice* device)
	{

		/*
		* Create texture2D desc
		*/
		D3D11_TEXTURE2D_DESC textureDesc;
		textureDesc.Width = desc.Width;
		textureDesc.Height = desc.Height;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = DX11TextureUtils::get_usage(desc.Usage);
		textureDesc.BindFlags = DX11TextureUtils::get_bind_flags(desc.Usage);
		textureDesc.Format = DX11TextureUtils::get_format(desc.Format);

		/*
		* Create texture init subresource
		*/
		D3D11_SUBRESOURCE_DATA initSubData;
		initSubData.pSysMem = nullptr;
		initSubData.SysMemPitch = 0;
		initSubData.SysMemSlicePitch = 0;

		/*
		* Create texture
		*/
		device->get_dx11_device()->CreateTexture2D(&textureDesc, &initSubData, &TextureBase);

		
	}
	void DX11Texture::create3d(const TextureDescription& desc, DX11GraphicsDevice* device)
	{

	}
	void DX11Texture::createcube(const TextureDescription& desc, DX11GraphicsDevice* device)
	{

	}

	void DX11Texture::createShaderResourceView(DX11GraphicsDevice* device, D3D_SRV_DIMENSION dimension, DXGI_FORMAT format)
	{
		/*
		* Create shader resource view desc
		*/
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = format;
		srvDesc.ViewDimension = dimension;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = -1;

		/*
		* Create shader resource view
		*/
		device->get_dx11_device()->CreateShaderResourceView(TextureBase,&srvDesc,&ResourceView);
	}
	
}