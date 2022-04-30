#include "DX12SwapchainFramebuffer.h"
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
    DX12SwapchainFramebuffer::DX12SwapchainFramebuffer(const FramebufferDescription& desc, DX12GraphicsDevice* device, Window* targetWindow)
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
		LOG("DX12SwapchainFramebuffer", "Created swapchain");
		/*
		* Get factory
		*/
		DXPTR<IDXGIFactory4> factory = device->get_dx12_factory();

		/*
		* Get command queue
		*/
		DXPTR<ID3D12CommandQueue> commandQueue = device->get_dx12_command_queue();

		/*
		* Get device
		*/
		DXPTR<ID3D12Device> dx12Device = device->get_dx12_device();

		/*
		* Create swapchain buffer desc
		*/
		DXGI_MODE_DESC bufferDesc = {};
		bufferDesc.Width = window->get_width();
		bufferDesc.Height = window->get_height();
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		/*
		* Create sample desc
		*/
		DXGI_SAMPLE_DESC sampleDesc = {};
		sampleDesc.Count = 1;

		/*
		* Create swapchain desc
		*/
		DXGI_SWAP_CHAIN_DESC swapchainDesc = {  };
		ZeroMemory(&swapchainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		swapchainDesc.BufferCount = 3; // tripple buffering
		swapchainDesc.BufferDesc = bufferDesc;
		swapchainDesc.Windowed = true;
		swapchainDesc.SampleDesc = sampleDesc;
		swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapchainDesc.OutputWindow = window->get_win32_window_handle();

		/*
		* Create temp swapchain
		*/
		HRESULT tempSwapchainCreateHR = factory->CreateSwapChain(commandQueue.Get(), &swapchainDesc, (IDXGISwapChain**)Swapchain.GetAddressOf());

		/*
		* Validate temp swapchain creation
		*/
		ASSERT(SUCCEEDED(tempSwapchainCreateHR), "DX12GraphicsDevice", "Temp swapchain creation failed!!");

		/*
		* Make window association
		*/
		factory->MakeWindowAssociation(window->get_win32_window_handle(), DXGI_MWA_NO_ALT_ENTER);

		/*
		* Get backbuffer index
		*/
		const unsigned int bacbufferIndex = Swapchain->GetCurrentBackBufferIndex();

		/*
		* Create render target view heap descriptors
		*/
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {  };
		rtvHeapDesc.NumDescriptors = 3;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		HRESULT createRtvDescriptorHeapHR = dx12Device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(RtvHeap.GetAddressOf()));
		
		/*
		* Validate rtv descriptior heap creation
		*/
		ASSERT(SUCCEEDED(createRtvDescriptorHeapHR), "DX12GraphicsDevice", "Rtv descriptor creation failed!");

		/*
		* Collect descriptor size in rtv heap descriptor
		*/
		const unsigned int rtvDescriptorSize = dx12Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		/*
		* Get handle of the first descriptor
		*/
		D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle = RtvHeap->GetCPUDescriptorHandleForHeapStart();

		/*
		* ITerate and create rtv for each buffer
		*/
		for (unsigned int i = 0; i < 3; i++)
		{
			/*
			* Get swapchain buffer
			*/
			DXPTR<ID3D12Resource> rtv;
			HRESULT rtvGetHR = Swapchain->GetBuffer(i, IID_PPV_ARGS(rtv.GetAddressOf()));

			/*
			* Validate get
			*/
			ASSERT(SUCCEEDED(rtvGetHR), "DX12GraphicsDevice", "Get swapchain buffer failed!");

			/*
			* Create render target view
			*/
			dx12Device->CreateRenderTargetView(rtv.Get(), nullptr, rtvStartHandle);

			/*
			* Increment rtv offset
			*/
			rtvStartHandle.ptr += rtvDescriptorSize;

			/*
			* Register
			*/
			RenderTargetViews.add(rtv);
		}
    }

}