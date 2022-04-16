#include "DX11ResourceView.h"
#include <Engine/Graphics/Resource/ResourceTypeUtils.h>
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Texture/DX11Texture.h>
#include <Engine/Graphics/API/Directx11/Texture/DX11TextureUtils.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Directx11/Buffer/DX11ConstantBuffer.h>


namespace DopeEngine
{
	DX11ResourceView::DX11ResourceView(const ResourceViewDescription& desc, DX11GraphicsDevice* device) : ResourceView(desc)
	{
		create(desc, device);
	}
	DX11ResourceView::~DX11ResourceView()
	{

	}
	void DX11ResourceView::create(const ResourceViewDescription& desc, DX11GraphicsDevice* device)
	{
		/*
		* Get resource
		*/
		const DeviceObject* resource = desc.Resource;
		DeviceObjectType deviceType = resource->get_device_object_type();

		/*
		* Get resource description
		*/
		switch (deviceType)
		{
		case DopeEngine::DeviceObjectType::Texture:
			create_as_texture(resource, device);
			break;
		case DopeEngine::DeviceObjectType::Buffer:
			BufferType bufferType = ((const Buffer*)resource)->get_buffer_type();
			switch (bufferType)
			{
			case DopeEngine::BufferType::UniformBuffer:
				create_as_constant_Buffer(resource, device);
				break;
			}
			break;
		}
	}
	void DX11ResourceView::create_as_texture(const DeviceObject* deviceObject, DX11GraphicsDevice* device)
	{
		/*
		* Get texture variables
		*/
		const DX11Texture* dx11Texture = (const DX11Texture*)deviceObject;
		const TextureType textureType = dx11Texture->get_type();

		/*
		* Create shader resource view desc
		*/
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		srvDesc.Format = DX11TextureUtils::get_format(dx11Texture->get_format());
		srvDesc.ViewDimension = DX11TextureUtils::get_dimension(dx11Texture->get_type());
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = -1;

		/*
		* Get texture as resource
		*/
		ID3D11Resource* textureAsResource = {0};
		switch (textureType)
		{
			case DopeEngine::TextureType::Texture1D:
				textureAsResource = dx11Texture->get_dx11_texture1d().Get();
				break;
			case DopeEngine::TextureType::Texture2D:
				textureAsResource = dx11Texture->get_dx11_texture2d().Get();
				break;
			case DopeEngine::TextureType::Texture3D:
				textureAsResource = dx11Texture->get_dx11_texture3d().Get();
				break;
			case DopeEngine::TextureType::CubeTexture:
				break;
			default:
				ASSERT(false, "DX11ResourceView", "Invalid TextureType, cannot create ID3D11ShaderResourceView");
				break;
		}

		/*
		* Create texture resource view
		*/
		device->get_dx11_device()->CreateShaderResourceView(textureAsResource, &srvDesc, &ShaderResourceView);

	}
	void DX11ResourceView::create_as_constant_Buffer(const DeviceObject* deviceObject, DX11GraphicsDevice* device)
	{
		/*
		* Create srv desc
		*/
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;

		/*
		* Create resource view
		*/
		ID3D11Resource* constantBufferResource = ((const DX11ConstantBuffer*)deviceObject)->get_dx11_buffer().Get();

		/*
		* Create resource view
		*/
		device->get_dx11_device()->CreateShaderResourceView(constantBufferResource, &srvDesc, &ShaderResourceView);

	}

}