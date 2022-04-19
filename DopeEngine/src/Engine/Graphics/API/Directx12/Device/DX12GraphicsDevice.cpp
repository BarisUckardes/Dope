#include "DX12GraphicsDevice.h"
#include <Engine/Core/Assert.h>
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
		_create_directx12_device();
#else
		ASSERT(false, "DX12GraphicsDevice", "Directx12 cannot be initialized with non-windows operating system");
#endif
	}
	void DX12GraphicsDevice::_create_win32_directx12_device()
	{
		/*
		* Create dxgi factory for enumarating existing gpus
		*/
		IDXGIFactory4* dxgiFactory;
		CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));

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
			DXGI_ADAPTER_DESC1 desc;
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
			* Increment adepter index for iteration
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
		swapchainDesc.BufferCount = 1;
		swapchainDesc.BufferDesc = bufferDesc;
		swapchainDesc.Windowed = true;
		swapchainDesc.SampleDesc = sampleDesc;
		swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapchainDesc.OutputWindow = get_owner_window()->get_win32_window_handle();

		/*
		* Create command queue just for swapchain
		*/
		D3D12_COMMAND_QUEUE_DESC cqDesc = {};
		ID3D12CommandQueue* commandQueue = nullptr;
		HRESULT cqCreateHR = Device->CreateCommandQueue(&cqDesc, __uuidof(**(&commandQueue)), (void**)&commandQueue);

		/*
		* Validate cq create
		*/
		ASSERT(SUCCEEDED(cqCreateHR), "DX12GraphicsDevice", "Creating command queue for swapchain creation failed!");

		/*
		* Create temp swapchain
		*/
		IDXGISwapChain* tempSwapchain;
		dxgiFactory->CreateSwapChain(commandQueue, &swapchainDesc, &tempSwapchain);

	}
	Framebuffer* DX12GraphicsDevice::create_window_swapchain_framebuffer_impl(const unsigned int width, const unsigned int height) const
	{
		return nullptr;
	}
	ResourceLayout* DX12GraphicsDevice::create_resource_layout_impl(const ResourceDescription& description)
	{
		return nullptr;
	}
	ResourceView* DX12GraphicsDevice::create_resource_view_impl(const ResourceViewDescription& description)
	{
		return nullptr;
	}
	void DX12GraphicsDevice::update_buffer_impl(Buffer* buffer, const Byte* data)
	{
	}
	void DX12GraphicsDevice::update_texture_impl(Texture* texture, const Byte* data)
	{
	}
	void DX12GraphicsDevice::swap_swapchain_buffers_impl()
	{
	}
	CommandBuffer* DX12GraphicsDevice::create_command_buffer_impl()
	{
		return nullptr;
	}
	void DX12GraphicsDevice::submit_command_buffer_impl(CommandBuffer* commandBuffer)
	{
	}
	void DX12GraphicsDevice::delete_device_object_impl(DeviceObject* object)
	{
	}
	Buffer* DX12GraphicsDevice::create_buffer_impl(const BufferDescription& description)
	{
		return nullptr;
	}
	Framebuffer* DX12GraphicsDevice::create_framebuffer_impl(const FramebufferDescription& description)
	{
		return nullptr;
	}
	Pipeline* DX12GraphicsDevice::create_pipeline_impl(const PipelineDescription& description)
	{
		return nullptr;
	}
	Shader* DX12GraphicsDevice::create_shader_impl(const ShaderDescription& description)
	{
		return nullptr;
	}
	ShaderSet* DX12GraphicsDevice::create_shader_set_impl(const Array<Shader*>& shaders)
	{
		return nullptr;
	}
	Texture* DX12GraphicsDevice::create_texture_impl(const TextureDescription& description)
	{
		return nullptr;
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
