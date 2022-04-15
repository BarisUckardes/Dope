#include "DX11Framebuffer.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Texture/DX11Texture.h>
namespace DopeEngine
{
	DX11Framebuffer::DX11Framebuffer(const FramebufferDescription& desc, DX11GraphicsDevice* device) : Framebuffer(desc)
	{
		/*
		* Create framebuffer
		*/
		create(desc,device);
	}
	DX11Framebuffer::~DX11Framebuffer()
	{

	}
	const Array<ID3D11RenderTargetView*>& DX11Framebuffer::get_dx11_rtvs_fast() const
	{
		return RenderTargets;
	}
	Array<ID3D11RenderTargetView*> DX11Framebuffer::get_dx11_rtvs_slow() const
	{
		return RenderTargets;
	}
	ID3D11DepthStencilView* DX11Framebuffer::get_dx11_depth_rtv() const
	{
		return DepthTarget;
	}
	void DX11Framebuffer::create(const FramebufferDescription& desc, DX11GraphicsDevice* device)
	{
		/*
		* Iterate attachment descs for creating render targets
		*/
		const Array<FramebufferAttachmentDescription> attachmentDescs = desc.AttachmentDescriptions;
		for (unsigned int i = 0; i < attachmentDescs.get_cursor(); i++)
		{
			/*
			* Get attachment desc
			*/
			const FramebufferAttachmentDescription& attachmentDesc = attachmentDescs[i];

			/*
			* Create texture desc
			*/
			TextureDescription textureDescription = {};
			textureDescription.Width = desc.Width;
			textureDescription.Height = desc.Height;
			textureDescription.Depth = 0;
			textureDescription.Format = attachmentDesc.Format;
			textureDescription.Type = TextureType::Texture2D;
			textureDescription.Usage = TextureUsage::FramebufferAttachment;

			/*
			* Create texture
			*/
			DX11Texture* dx11Texture = (DX11Texture*)device->create_texture(textureDescription);
			D3D11_TEXTURE2D_DESC dx11TextureDesc;
			dx11Texture->get_dx11_texture()->GetDesc(&dx11TextureDesc);

			/*
			* Create attachment render target desc
			*/
			D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
			rtvDesc.Format = dx11TextureDesc.Format;
			rtvDesc.ViewDimension = attachmentDescs.get_cursor() > 1 ? D3D11_RTV_DIMENSION_TEXTURE2DARRAY : D3D11_RTV_DIMENSION_TEXTURE2D;
			rtvDesc.Texture2D.MipSlice = 0;

			/*
			* Create render target
			*/
			ID3D11RenderTargetView* rtv = nullptr;
			device->get_dx11_device()->CreateRenderTargetView(dx11Texture->get_dx11_texture(), &rtvDesc, &rtv);

			/*
			* Register rtv
			*/
			RenderTargets.add(rtv);
		}

		/*
		* Create depth attachment if requested
		*/
		if (desc.CreateDepthAttachment)
		{
			/*
			* Create texture desc
			*/
			TextureDescription textureDesc = {};
			textureDesc.Width = desc.Width;
			textureDesc.Height = desc.Height;
			textureDesc.Depth = 0;
			textureDesc.Format = TextureFormat::Red;
			textureDesc.Type = TextureType::Texture2D;
			textureDesc.Usage = (TextureUsage::FramebufferAttachment | TextureUsage::DepthStencil);

			/*
			* Create texture
			*/
			DX11Texture* dx11Texture = (DX11Texture*)device->create_texture(textureDesc);
			D3D11_TEXTURE2D_DESC dx11TextureDesc;
			dx11Texture->get_dx11_texture()->GetDesc(&dx11TextureDesc);

			/*
			* Create rtv desc
			*/
			D3D11_DEPTH_STENCIL_VIEW_DESC rtvDesc;
			rtvDesc.Format = dx11TextureDesc.Format;
			rtvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			rtvDesc.Texture2D.MipSlice = 0;

			/*
			* Create depth rtv
			*/
			device->get_dx11_device()->CreateDepthStencilView(dx11Texture->get_dx11_texture(), &rtvDesc, &DepthTarget);
		}
	}
}