#include "DX11SwapchainFramebuffer.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
namespace DopeEngine
{
	DX11SwapchainFramebuffer::DX11SwapchainFramebuffer(const unsigned int initialWidth, const unsigned int initialHeight, DX11GraphicsDevice* device, Window* window) : SwapchainFramebuffer(initialWidth,initialHeight,(GraphicsDevice*)device,window)
	{
		/*
		* Initialize
		*/
		Rtv = nullptr;

		/*
		* Create
		*/
		create(device);
	}
	DX11SwapchainFramebuffer::~DX11SwapchainFramebuffer()
	{

	}
	ID3D11RenderTargetView* DX11SwapchainFramebuffer::get_dx11_swapchain_rtv() const
	{
		return Rtv;
	}
	void DX11SwapchainFramebuffer::create(DX11GraphicsDevice* device)
	{
		Rtv = device->get_swawpchain_rtv();
	}
}