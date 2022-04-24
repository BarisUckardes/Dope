#include "DX12SwapchainFramebuffer.h"
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Core/ConsoleLog.h>
namespace DopeEngine
{
    DX12SwapchainFramebuffer::DX12SwapchainFramebuffer(const unsigned int initialWidth, const unsigned int initialHeight, DX12GraphicsDevice* device, Window* targetWindow) : SwapchainFramebuffer(initialWidth,initialHeight,(GraphicsDevice*)device,targetWindow)
    {
        /*
        * Initialize
        */
        Swapchain = nullptr;

        /*
        * Create
        */
        create(device);
    }

    DX12SwapchainFramebuffer::~DX12SwapchainFramebuffer()
    {

    }

    const Array<DXPTR<ID3D12Resource>>& DX12SwapchainFramebuffer::get_dx12_swapchain_rtvs() const
    {
        return RenderTargetViews;
    }

    DXPTR<ID3D12Resource> DX12SwapchainFramebuffer::get_dx12_current_rtv() const
    {
       // LOG("DX12SwapchainFramebuffer", "Current index: %d", Swapchain->GetCurrentBackBufferIndex());
        return RenderTargetViews[Swapchain->GetCurrentBackBufferIndex()];
    }

    unsigned int DX12SwapchainFramebuffer::get_dx12_swapchain_current_rtv_index() const
    {
        return Swapchain->GetCurrentBackBufferIndex();
    }

    void DX12SwapchainFramebuffer::_increment_backbuffer_index()
    {

    }

    void DX12SwapchainFramebuffer::create(DX12GraphicsDevice* device)
    {
        /*
        * Get rtvs
        */
        RenderTargetViews = device->get_dx12_swapchain_rtvs();

        /*
        * Get swapchain
        */
        Swapchain = device->get_dx12_swapchain();
    }

}