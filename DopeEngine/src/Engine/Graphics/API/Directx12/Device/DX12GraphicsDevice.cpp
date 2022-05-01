#include "DX12GraphicsDevice.h"
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Directx12/Device/DX12DeviceObjects.h>
#include <Engine/Platform/Windows/Structures/WindowString.h>
#include <Engine/Graphics/API/Directx12/Helper/DX12Helper.h>
#include <Engine/Memory/Memory.h>
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
		CreateDXGIFactory2(factoryFlags,IID_PPV_ARGS(Factory.GetAddressOf()));

		/*
		* Iterate existing gpus
		*/
		IDXGIAdapter1* adapter;
		int adapterIndex = 0;
		bool adapterFound = false;
		while (Factory->EnumAdapters1(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND)
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
	bool DX12GraphicsDevice::does_support_features(const GraphicsDeviceFeatures* features, Array<String>& messages)
	{
		return true;
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

	void DX12GraphicsDevice::swap_swapchain_buffers_impl(const SwapchainFramebuffer* framebuffer)
	{
		/*
		* Get dx12 swapchainframebuffer
		*/
		const DX12SwapchainFramebuffer* swapchainFramebuffer = (const DX12SwapchainFramebuffer*)framebuffer;

		/*
		* Present backbuffer
		*/
		HRESULT presentHR = swapchainFramebuffer->get_dx12_swapchain()->Present(1, 0);

		/*
		* Validate presentation
		*/
		ASSERT(SUCCEEDED(presentHR), "DX12GraphicsDevice", "Failed to present");
	}
	Framebuffer* DX12GraphicsDevice::create_window_swapchain_framebuffer_impl(const unsigned int width, const unsigned int height) const
	{


		return new DX12SwapchainFramebuffer(SwapchainFramebufferDesc(width, height, 3, TextureFormat::RGBA8unorm, TextureFormat::R8unorm, false),
			(DX12GraphicsDevice*)this,
			(Window*)get_owner_window());
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
		/*
		* Get buffer type
		*/
		BufferType bufferType = buffer->get_buffer_type();

		/*
		* Catch buffer
		*/
		DXPTR<ID3D12Resource> bufferResource;
		switch (bufferType)
		{
			case DopeEngine::BufferType::VertexBuffer:
				bufferResource = ((DX12VertexBuffer*)buffer)->get_dx12_vertex_buffer();
				break;
			case DopeEngine::BufferType::IndexBuffer:
				bufferResource = ((DX12IndexBuffer*)buffer)->get_dx12_index_buffer();
				break;
			case DopeEngine::BufferType::UniformBuffer:
				bufferResource = ((DX12ConstantBuffer*)buffer)->get_dx12_constant_buffer();
				break;
			case DopeEngine::BufferType::Undefined:
				ASSERT(false, "DX12GraphicsDevice", "Undefined buffer type, cannot update the buffer data");
				break;
			default:
				break;
		}

		/*
		* Create read range data
		*/
		D3D12_RANGE readRange = {};
		readRange.Begin = 0;
		readRange.End = buffer->get_allocated_size();

		/*
		* Update buffer data
		*/
		void* dataPtr;
		bufferResource->Map(0, &readRange, &dataPtr);
		Memory::memory_copy(dataPtr,data,buffer->get_allocated_size());
		bufferResource->Unmap(0, nullptr);
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

	DXPTR<ID3D12CommandQueue> DX12GraphicsDevice::get_dx12_command_queue() const
	{
		return CommandQueue;
	}
	
	DXPTR<ID3D12GraphicsCommandList> DX12GraphicsDevice::get_dx12_available_graphics_command_list() const
	{
		return GraphicsCommandList;
	}

	DXPTR<IDXGIFactory4> DX12GraphicsDevice::get_dx12_factory() const
	{
		return Factory;
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
