#include "DX11Texture.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Texture/DX11TextureUtils.h>
#include <Engine/Graphics/Texture/TextureUtils.h>
#include <Engine/Core/ConsoleLog.h>
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
	DXPTR<ID3D11Texture1D> DX11Texture::get_dx11_texture1d() const
	{
		return Texture1D;
	}
	DXPTR<ID3D11Texture2D> DX11Texture::get_dx11_texture2d() const
	{
		return Texture2D;
	}
	DXPTR<ID3D11Texture3D> DX11Texture::get_dx11_texture3d() const
	{
		return Texture3D;
	}
	void DX11Texture::create(const TextureDescription& desc, DX11GraphicsDevice* device)
	{
		/*
		* Create texture desc
		*/
		const TextureType textureType = get_type();
		switch (textureType)
		{
			case DopeEngine::TextureType::Texture1D:
				break;
			case DopeEngine::TextureType::Texture2D:
				create2d(desc, device);
				break;
			case DopeEngine::TextureType::Texture3D:
				create3d(desc, device);
				break;
			case DopeEngine::TextureType::CubeTexture:
				createcube(desc, device);
				break;
			default:
				break;
		}
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
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage = DX11TextureUtils::get_usage(desc.Usage);
		textureDesc.BindFlags = DX11TextureUtils::get_bind_flags(desc.Usage);
		textureDesc.Format = DX11TextureUtils::get_format(desc.Format);
		textureDesc.MipLevels = 1;
		textureDesc.MiscFlags = 0;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.ArraySize = 1;

		/*
		* Create ýnitial data
		*/
		const unsigned int pixelSize = TextureUtils::get_format_size(desc.Format);
		D3D11_SUBRESOURCE_DATA initialSubData = { 0 };
		initialSubData.pSysMem = desc.InitialData;
		initialSubData.SysMemPitch = desc.Width* pixelSize; // TODO implement mem pitch
		initialSubData.SysMemSlicePitch = desc.Height * pixelSize;

		LOG("DX11Texture", "Initial data SysMemPitch: %d", initialSubData.SysMemPitch);

		/*
		* Validate initial data and create texture
		*/
		if(desc.InitialData !=nullptr)
			device->get_dx11_device()->CreateTexture2D(&textureDesc, &initialSubData, &Texture2D);
		else
			device->get_dx11_device()->CreateTexture2D(&textureDesc, nullptr, &Texture2D);

		
	}
	void DX11Texture::create3d(const TextureDescription& desc, DX11GraphicsDevice* device)
	{

	}
	void DX11Texture::createcube(const TextureDescription& desc, DX11GraphicsDevice* device)
	{

	}

	
}