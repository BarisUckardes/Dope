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
		DXPTR<IDXGISwapChain3> get_dx12_swapchain() const;
		DXPTR<ID3D12DescriptorHeap> get_dx12_rtv_heap() const;
		unsigned int get_dx12_swapchain_current_rtv_index() const;

		/// <summary>
		/// Increments the current backbuffer index
		/// </summary>
		void _increment_backbuffer_index();
	private:
		void create(DX12GraphicsDevice* device,Window* window);
	private:
		DXPTR<IDXGISwapChain3> Swapchain;
		DXPTR<ID3D12DescriptorHeap> RtvHeap;
		Array<DXPTR<ID3D12Resource>> RenderTargetViews;
		unsigned int CurrentBackbufferIndex;
	};


}