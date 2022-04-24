#include "DX12GraphicsDevice.h"
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Directx12/Device/DX12DeviceObjects.h>
#include <Engine/Platform/Windows/Structures/WindowString.h>
#include <Engine/Graphics/API/Directx12/Helper/DX12Helper.h>
#include <iostream>

namespace DopeEngine
{
	DX12GraphicsDevice::DX12GraphicsDevice(Window* ownerWindow) : GraphicsDevice(ownerWindow)
	{
		_create_directx12_device();
	}
	DX12GraphicsDevice::~DX12GraphicsDevice()
	{

	}
	void DX12GraphicsDevice::_create_directx12_device()
	{
#ifdef DOPE_OS_WINDOWS
		_create_win32_directx12_device();
#else
		ASSERT(false, "DX12GraphicsDevice", "Directx12 cannot be initialized with non-windows operating system");
#endif
	}
	void DX12GraphicsDevice::_create_win32_directx12_device()
	{
		/*
		* Enable debug layer if its wanted
		*/
		unsigned int factoryFlags = 0;
#ifdef _DEBUG
		ID3D12Debug* dx12Debug;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&dx12Debug))))
		{
			/*
			* Enable debug layer
			*/
			dx12Debug->EnableDebugLayer();

			/*
			* Add debug flag
			*/
			factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		}
#endif
		/*
		* Create dxgi factory for enumarating existing gpus
		*/
		IDXGIFactory4* dxgiFactory;
		CreateDXGIFactory2(factoryFlags,IID_PPV_ARGS(&dxgiFactory));

		/*
		* Iterate existing gpus
		*/
		IDXGIAdapter1* adapter;
		int adapterIndex = 0;
		bool adapterFound = false;
		while (dxgiFactory->EnumAdapters1(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND)
		{
			/*
			* Get adapter desc
			*/
			DXGI_ADAPTER_DESC1 desc = {};
			adapter->GetDesc1(&desc);

			/*
			* Validate if it's an software device
			*/
			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				adapterIndex++;
				continue;
			}

			/*
			* Try create dx12 device
			*/
			HRESULT deviceCreateHR = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), (void**)&Device);
			if (SUCCEEDED(deviceCreateHR))
			{
				adapterFound = true;
				break;
			}

			/*
			* Increment adapter index for iteration
			*/
			adapterIndex++;
		}

		/*
		* Validate dx12 device
		*/
		ASSERT(adapterFound, "DX12GraphicsDevice", "DX12 capable graphics device not found!");

		/*
		* Get win32 window
		*/
		const Window* window = get_owner_window();

		/*
		* Create command queue
		*/
		D3D12_COMMAND_QUEUE_DESC cqDesc = {};
		HRESULT cqCreateHR = Device->CreateCommandQueue(&cqDesc,IID_PPV_ARGS(&CommandQueue));

		/*
		* Validate cq create
		*/
		ASSERT(SUCCEEDED(cqCreateHR), "DX12GraphicsDevice", "Creating command queue for swapchain creation failed!");

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
		ZeroMemory(&swapchainDesc,sizeof(DXGI_SWAP_CHAIN_DESC));
		swapchainDesc.BufferCount = 3; // tripple buffering
		swapchainDesc.BufferDesc = bufferDesc;
		swapchainDesc.Windowed = true;
		swapchainDesc.SampleDesc = sampleDesc;
		swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapchainDesc.OutputWindow = get_owner_window()->get_win32_window_handle();

		/*
		* Create temp swapchain
		*/
		HRESULT tempSwapchainCreateHR = dxgiFactory->CreateSwapChain(CommandQueue.Get(), &swapchainDesc, (IDXGISwapChain**)Swapchain.GetAddressOf());

		/*
		* Validate temp swapchain creation
		*/
		ASSERT(SUCCEEDED(tempSwapchainCreateHR), "DX12GraphicsDevice", "Temp swapchain creation failed!!");

		/*
		* Make window association
		*/
		dxgiFactory->MakeWindowAssociation(window->get_win32_window_handle(), DXGI_MWA_NO_ALT_ENTER);

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
		HRESULT createRtvDescriptorHeapHR = Device->CreateDescriptorHeap(&rtvHeapDesc,IID_PPV_ARGS(RtvHeapDescriptor.GetAddressOf()));

		/*
		* Validate rtv descriptior heap creation
		*/
		ASSERT(SUCCEEDED(createRtvDescriptorHeapHR), "DX12GraphicsDevice", "Rtv descriptor creation failed!");

		/*
		* Collect descriptor size in rtv heap descriptor
		*/
		const unsigned int rtvDescriptorSize = Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		/*
		* Get handle of the first descriptor
		*/
		D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle = RtvHeapDescriptor->GetCPUDescriptorHandleForHeapStart();

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
			Device->CreateRenderTargetView(rtv.Get(), nullptr, rtvStartHandle);

			/*
			* Increment rtv offset
			*/
			rtvStartHandle.ptr += rtvDescriptorSize;

			/*
			* Register
			*/
			RenderTargets.add(rtv);
		}

		/*
		* Create command allocator
		*/
		HRESULT createCommandAllocatedHR = Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(CommandAllocator.GetAddressOf()));

		/*
		* Validate creation of the command allocator
		*/
		ASSERT(SUCCEEDED(createCommandAllocatedHR), "DX12GraphicsDevice", "Command allocator creation failed!");

		/*
		* Create command list
		*/
		HRESULT createCommandListHR = Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, CommandAllocator.Get(), NULL, IID_PPV_ARGS(GraphicsCommandList.ReleaseAndGetAddressOf()));

		/*
		* Validate command list creation
		*/
		ASSERT(SUCCEEDED(createCommandListHR), "DX12GraphicsDevice","Command list creation failed!");

		/*
		* Close command list because the default state is the recording state
		*/
		HRESULT commandListCloseHR = GraphicsCommandList->Close();

		/*
		* Validate close
		*/
		ASSERT(SUCCEEDED(commandListCloseHR), "DX12CommandBuffer", "Command list couldnt be closed");

		/*
		* Create graphics device fence
		*/
		Device->CreateFence(1, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(Fence.GetAddressOf()));

		/*
		* Creat fence event
		*/
		FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	}
	void DX12GraphicsDevice::wait_for_finish_impl()
	{
		/*
		* Signal command queue about the fence
		*/
		const unsigned int fValue = FenceValue;
		CommandQueue->Signal(Fence.Get(), fValue);

		/*
		* Increment the fende
		*/
		FenceValue++;

		/*
		* Wait until the command queue is finished
		*/
		if (Fence->GetCompletedValue() < fValue)
		{
			/*
			* Set fence event
			*/
			Fence->SetEventOnCompletion(fValue, FenceEvent);

			/*
			* Wait until the fence event finishes
			*/
			WaitForSingleObject(FenceEvent, INFINITE);
		}
		
		/*
		* Resets the allocator
		*/
		CommandAllocator->Reset();
	}

	void DX12GraphicsDevice::swap_swapchain_buffers_impl()
	{
		/*
		* Present backbuffer
		*/
		HRESULT presentHR = Swapchain->Present(1, 0);

		/*
		* Validate presentation
		*/
		ASSERT(SUCCEEDED(presentHR), "DX12GraphicsDevice", "Failed to present");
	}
	Framebuffer* DX12GraphicsDevice::create_window_swapchain_framebuffer_impl(const unsigned int width, const unsigned int height) const
	{
		return new DX12SwapchainFramebuffer(width, height, (DX12GraphicsDevice*)this, (Window*)get_owner_window());
	}
	ResourceLayout* DX12GraphicsDevice::create_resource_layout_impl(const ResourceDescription& description)
	{
		/*
		* Create directx12 resource layout
		*/
		DX12ResourceLayout* layout = new DX12ResourceLayout(description,this);

		return layout;
	}
	ResourceView* DX12GraphicsDevice::create_resource_view_impl(const ResourceViewDescription& description)
	{
		/*
		* Create directx12 resource view
		*/
		DX12ResourceView* view = new DX12ResourceView(description, this);

		return view;
	}
	void DX12GraphicsDevice::update_buffer_impl(Buffer* buffer, const Byte* data)
	{

	}
	void DX12GraphicsDevice::update_texture_impl(Texture* texture, const Byte* data)
	{

	}

	CommandBuffer* DX12GraphicsDevice::create_command_buffer_impl()
	{
		/*
		* Create directx12 command buffer
		*/
		DX12CommandBuffer* commandBuffer = new DX12CommandBuffer(this);

		return commandBuffer;
	}
	void DX12GraphicsDevice::submit_command_buffer_impl(CommandBuffer* commandBuffer)
	{
		/*
		* Get dx command buffer
		*/
		DX12CommandBuffer* dxCommandBuffer = (DX12CommandBuffer*)commandBuffer;
		DXPTR<ID3D12CommandList> cmdList = dxCommandBuffer->get_dx12_command_list();
		CommandQueue->ExecuteCommandLists(1, cmdList.GetAddressOf());
		//LOG("DX12GraphicsDevice", "Execute");
	}

	void DX12GraphicsDevice::delete_device_object_impl(DeviceObject* object)
	{

	}

	Buffer* DX12GraphicsDevice::create_buffer_impl(const BufferDescription& description)
	{
		/*
		* Catch buffer type
		*/
		BufferType bufferType = description.Type;
		Buffer* buffer = nullptr;
		switch (bufferType)
		{
			case DopeEngine::BufferType::VertexBuffer:
				buffer = new DX12VertexBuffer(description.AllocatedSize, description.PerItemSize, this);
				break;
			case DopeEngine::BufferType::IndexBuffer:
				buffer = new DX12IndexBuffer(4,description.AllocatedSize,this);
				break;
			case DopeEngine::BufferType::UniformBuffer:
				buffer = new DX12ConstantBuffer(description,this);
				break;
			case DopeEngine::BufferType::Undefined:
				ASSERT(false, "DX12GraphicsDevice", "Invalid BufferType, cannot create a buffer!");
				break;
			default:
				break;
		}

		return buffer;
	}

	Framebuffer* DX12GraphicsDevice::create_framebuffer_impl(const FramebufferDescription& description)
	{
		/*
		* Create directx12 framebuffer
		*/
		DX12Framebuffer* framebuffer = new DX12Framebuffer(description, this);

		return framebuffer;
	}

	Pipeline* DX12GraphicsDevice::create_pipeline_impl(const PipelineDescription& description)
	{
		/*
		* Create directx 12 pipeline
		*/
		DX12Pipeline* pipeline = new DX12Pipeline(description, this);

		return pipeline;
	}

	Shader* DX12GraphicsDevice::create_shader_impl(const ShaderDescription& description)
	{
		/*
		* Create directx12 shader
		*/
		DX12Shader* shader = new DX12Shader(description, this);

		return shader;
	}

	ShaderSet* DX12GraphicsDevice::create_shader_set_impl(const Array<Shader*>& shaders)
	{
		/*
		* Create directx12 shader set
		*/
		DX12ShaderSet* shaderSet = new DX12ShaderSet(shaders,this);

		return shaderSet;
	}

	Texture* DX12GraphicsDevice::create_texture_impl(const TextureDescription& description)
	{
		/*
		* Create directx12 texture
		*/
		DX12Texture* texture = new DX12Texture(description, this);

		return texture;
	}

	DXPTR<ID3D12Device> DX12GraphicsDevice::get_dx12_device() const
	{
		return Device;
	}

	DXPTR<ID3D12CommandAllocator> DX12GraphicsDevice::get_dx12_command_allocator() const
	{
		return CommandAllocator;
	}
	DXPTR<IDXGISwapChain3> DX12GraphicsDevice::get_dx12_swapchain() const
	{
		return Swapchain;
	}

	Array<DXPTR<ID3D12Resource>> DX12GraphicsDevice::get_dx12_swapchain_rtvs() const
	{
		return RenderTargets;
	}

	DXPTR<ID3D12DescriptorHeap> DX12GraphicsDevice::get_dx12_rtv_heap_descriptor() const
	{
		return RtvHeapDescriptor;
	}

	DXPTR<ID3D12GraphicsCommandList> DX12GraphicsDevice::get_dx12_available_graphics_command_list() const
	{
		return GraphicsCommandList;
	}

	GraphicsAPIType DX12GraphicsDevice::get_api_type() const
	{
		return GraphicsAPIType::Directx12;
	}

	String DX12GraphicsDevice::get_version() const
	{
		return String();
	}

	void DX12GraphicsDevice::make_current_impl()
	{

	}
}
