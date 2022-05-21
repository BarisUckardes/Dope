#include "DX11SwapchainFramebuffer.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Graphics/API/Directx11/Texture/DX11TextureUtils.h>
namespace DopeEngine
{
	DX11SwapchainFramebuffer::DX11SwapchainFramebuffer(const SwapchainFramebufferDesc& desc, DX11GraphicsDevice* device, Window* window) : SwapchainFramebuffer(desc,(GraphicsDevice*)device,window)
	{
		/*
		* Initialize
		*/
		Swapchain = device->get_dx11_swapchain();
		Device = device->get_dx11_device();

		/*
		* Create
		*/
		create(device);
	}
	DX11SwapchainFramebuffer::~DX11SwapchainFramebuffer()
	{

	}
	DXPTR<ID3D11RenderTargetView> DX11SwapchainFramebuffer::get_dx11_swapchain_rtv() const
	{
		return SwapchainRenderTargetViews[0];
	}
	void DX11SwapchainFramebuffer::on_swapchain_resize_impl()
	{
		/*
		* Release former rtvs
		*/
		SwapchainRenderTargetViews.clear();

		/*
		* Resize swapchain buffers
		*/
		Swapchain->ResizeBuffers(0,0,0, DXGI_FORMAT_UNKNOWN, 0);

		/*
		* Re-create render target views
		*/
		for (unsigned int i = 0; i < get_swapchain_buffer_count(); i++)
		{
			/*
			* Create backbuffer
			*/
			ID3D11Texture2D* backBuffer;
			Swapchain->GetBuffer(i, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

			/*
			* Create render target
			*/
			DXPTR<ID3D11RenderTargetView> rtv;
			Device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
			SwapchainRenderTargetViews.add(rtv);

			/*
			* Release backbuffer
			*/
			backBuffer->Release();
		}
	}

	void DX11SwapchainFramebuffer::create(DX11GraphicsDevice* device)
	{
		for (unsigned int i = 0; i < get_swapchain_buffer_count(); i++)
		{
			/*
			* Create backbuffer
			*/
			ID3D11Texture2D* backBuffer;
			Swapchain->GetBuffer(i, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

			/*
			* Create render target
			*/
			DXPTR<ID3D11RenderTargetView> rtv;
			Device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
			SwapchainRenderTargetViews.add(rtv);

			/*
			* Release backbuffer
			*/
			backBuffer->Release();
		}
	}
}