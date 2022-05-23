#include "DX12SwapchainFramebuffer.h"
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Directx11/Texture/DX11TextureUtils.h>
#include <Engine/Platform/Windows/Window/WindowsWindow.h>
namespace DopeEngine
{
    DX12SwapchainFramebuffer::DX12SwapchainFramebuffer(const SwapchainFramebufferDesc& desc, DX12GraphicsDevice* device, Window* targetWindow)
		: SwapchainFramebuffer(desc,(GraphicsDevice*)device,targetWindow)
    {
        /*
        * Initialize
        */
        Swapchain = nullptr;

        /*
        * Create
        */
        create(device,targetWindow);
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
        return RenderTargetViews[Swapchain->GetCurrentBackBufferIndex()];
    }

	DXPTR<IDXGISwapChain3> DX12SwapchainFramebuffer::get_dx12_swapchain() const
	{
		return Swapchain;
	}

	DXPTR<ID3D12DescriptorHeap> DX12SwapchainFramebuffer::get_dx12_rtv_heap() const
	{
		return RtvHeap;
	}

    unsigned int DX12SwapchainFramebuffer::get_dx12_swapchain_current_rtv_index() const
    {
        return Swapchain->GetCurrentBackBufferIndex();
    }

    void DX12SwapchainFramebuffer::_increment_backbuffer_index()
    {

    }

	void DX12SwapchainFramebuffer::on_swapchain_resize_impl()
	{

	}

    void DX12SwapchainFramebuffer::create(DX12GraphicsDevice* device,Window* window)
    {
		WindowsWindow* win32Window = (WindowsWindow*)window;

		DXPTR<IDXGIFactory4> factory = device->get_dx12_factory();
		DXPTR<ID3D12CommandQueue> commandQueue = device->get_dx12_command_queue();
		DXPTR<ID3D12Device> dx12Device = device->get_dx12_device();

		DXGI_MODE_DESC bufferDesc = {};
		bufferDesc.Width = window->get_width();
		bufferDesc.Height = window->get_height();
		bufferDesc.Format = DX11TextureUtils::get_format(get_swapchain_buffer_format());

		DXGI_SAMPLE_DESC sampleDesc = {};
		sampleDesc.Count = 1;

		const unsigned int bufferCount = get_swapchain_buffer_count();
		DXGI_SWAP_CHAIN_DESC swapchainDesc = {  };
		ZeroMemory(&swapchainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		swapchainDesc.BufferCount = bufferCount;
		swapchainDesc.BufferDesc = bufferDesc;
		swapchainDesc.Windowed = true;
		swapchainDesc.SampleDesc = sampleDesc;
		swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapchainDesc.OutputWindow = win32Window->get_win32_window_handle();


		HRESULT tempSwapchainCreateHR = factory->CreateSwapChain(commandQueue.Get(), &swapchainDesc, (IDXGISwapChain**)Swapchain.GetAddressOf());
		ASSERT(SUCCEEDED(tempSwapchainCreateHR), "DX12GraphicsDevice", "Temp swapchain creation failed!!");

		factory->MakeWindowAssociation(win32Window->get_win32_window_handle(), DXGI_MWA_NO_ALT_ENTER);

		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {  };
		rtvHeapDesc.NumDescriptors = bufferCount;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		HRESULT createRtvDescriptorHeapHR = dx12Device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(RtvHeap.GetAddressOf()));
		ASSERT(SUCCEEDED(createRtvDescriptorHeapHR), "DX12GraphicsDevice", "Rtv descriptor creation failed!");


		const unsigned int rtvDescriptorSize = dx12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle = RtvHeap->GetCPUDescriptorHandleForHeapStart();
		for (unsigned int i = 0; i < bufferCount; i++)
		{
			DXPTR<ID3D12Resource> rtv;

			HRESULT rtvGetHR = Swapchain->GetBuffer(i, IID_PPV_ARGS(rtv.GetAddressOf()));
			ASSERT(SUCCEEDED(rtvGetHR), "DX12GraphicsDevice", "Get swapchain buffer failed!");

			dx12Device->CreateRenderTargetView(rtv.Get(), nullptr, rtvStartHandle);

			rtvStartHandle.ptr += rtvDescriptorSize;

			RenderTargetViews.add(rtv);
		}
    }

}