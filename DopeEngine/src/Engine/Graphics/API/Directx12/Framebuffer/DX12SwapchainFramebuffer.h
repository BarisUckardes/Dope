#pragma once
#include <Engine/Graphics/Framebuffer/SwapchainFramebuffer.h>
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API DX12SwapchainFramebuffer : public SwapchainFramebuffer
	{
	public:
		DX12SwapchainFramebuffer(const unsigned int initialWidth,const unsigned int initialHeight,DX12GraphicsDevice* device, Window* targetWindow);
		virtual ~DX12SwapchainFramebuffer() final override;

		const Array<DXPTR<ID3D12Resource>>& get_dx12_swapchain_rtvs() const;
		DXPTR<ID3D12Resource> get_dx12_current_rtv() const;
	private:
		void create(DX12GraphicsDevice* device);
	private:
		DXPTR<IDXGISwapChain3> Swapchain;
		Array<DXPTR<ID3D12Resource>> RenderTargetViews;
	};


}