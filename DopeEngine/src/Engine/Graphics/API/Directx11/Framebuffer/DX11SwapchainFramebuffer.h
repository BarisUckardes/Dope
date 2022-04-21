#pragma once
#include <Engine/Graphics/Framebuffer/SwapchainFramebuffer.h>
#include <Engine/Graphics/API/Directx11/Core/DX11Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX11SwapchainFramebuffer : public SwapchainFramebuffer
	{
	public:
		DX11SwapchainFramebuffer(const unsigned int initialWidth, const unsigned int initialHeight, DX11GraphicsDevice* device, Window* window);
		virtual ~DX11SwapchainFramebuffer() final override;

		 DXPTR<ID3D11RenderTargetView> get_dx11_swapchain_rtv() const;
	private:
		void create(DX11GraphicsDevice* device);

	private:
		DXPTR<ID3D11RenderTargetView> Rtv;
	};


}