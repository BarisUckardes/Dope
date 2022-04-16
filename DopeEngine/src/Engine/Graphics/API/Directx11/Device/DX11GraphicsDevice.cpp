#include "DX11GraphicsDevice.h"
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Directx11/Device/DX11DeviceObjects.h>

namespace DopeEngine
{
	DX11GraphicsDevice::DX11GraphicsDevice(Window* ownerWindow) : GraphicsDevice(ownerWindow)
	{
		_create_directx11_device();
	}

	ComPtr<ID3D11Device> DX11GraphicsDevice::get_dx11_device() const
	{
		return Device;
	}

	ComPtr<ID3D11DeviceContext> DX11GraphicsDevice::get_dx11_immediate_context() const
	{
		return ImmediateContext;
	}

	ComPtr<ID3D11RenderTargetView> DX11GraphicsDevice::get_swawpchain_rtv() const
	{
		return SwapchainRenderTargetView;
	}

	void DX11GraphicsDevice::_create_directx11_device()
	{
#ifdef DOPE_OS_WINDOWS
		_create_win32_directx11_device();
#else
		ASSERT(false,"Directx11GraphicsDevice", "Directx11 cannot be initialized with non-windows operating system");
#endif
	}

	void DX11GraphicsDevice::_create_win32_directx11_device()
	{
		/*
		* Get window
		*/
		const Window* ownerWindow = get_owner_window();

		/*
		* Create swapbuffer buffer desc
		*/
		DXGI_MODE_DESC bufferDesc = { 0 };
		bufferDesc.Width = ownerWindow->get_width();
		bufferDesc.Height = ownerWindow->get_height();
		bufferDesc.RefreshRate.Numerator = 60;
		bufferDesc.RefreshRate.Denominator = 1;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		/*
		* Create swapchain desc
		*/
		DXGI_SWAP_CHAIN_DESC swapchainDesc = { 0 };
		swapchainDesc.BufferDesc = bufferDesc;
		swapchainDesc.SampleDesc.Count = 1;
		swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapchainDesc.BufferCount = 1;
		swapchainDesc.OutputWindow = ownerWindow->get_win32_window_handle();
		swapchainDesc.Windowed = TRUE;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		/*
		* Create swapchain,device and immediate context
		*/
#ifdef _DEBUG
		D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, NULL, NULL,
			D3D11_SDK_VERSION, &swapchainDesc, &SwapChain, &Device, NULL, &ImmediateContext);
#else
		D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
			D3D11_SDK_VERSION, &swapchainDesc, &SwapChain, &Device, NULL, &ImmediateContext);
#endif


		/*
		* Create deferred context
		*/
		Device->CreateDeferredContext(0, &DeferredContext);

		/*
		* Create backbuffer
		*/
		ID3D11Texture2D* backBuffer;
		SwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(void**)&backBuffer);

		/*
		* Create render target
		*/
		Device->CreateRenderTargetView(backBuffer, nullptr, &SwapchainRenderTargetView);

		/*
		* Release backbuffer
		*/
		backBuffer->Release();
	}

	void DX11GraphicsDevice::swap_swapchain_buffers_impl()
	{
		SwapChain->Present(1u, 0);
	}

	Framebuffer* DX11GraphicsDevice::create_window_swapchain_framebuffer_impl(const unsigned int width, const unsigned int height) const
	{
		return new DX11SwapchainFramebuffer(width,height,(DX11GraphicsDevice*)this,(Window*)get_owner_window());
	}

	ResourceLayout* DX11GraphicsDevice::create_resource_layout_impl(const ResourceDescription& description)
	{
		return nullptr;
	}

	ResourceView* DX11GraphicsDevice::create_resource_view_impl(const ResourceViewDescription& description)
	{
		return nullptr;
	}

	void DX11GraphicsDevice::update_buffer_impl(Buffer* buffer, const Byte* data)
	{
		/*
		* Get dx11 buffer
		*/
		BufferType type = buffer->get_buffer_type();
		ID3D11Resource* bufferResource = nullptr;
		switch (type)
		{
			case DopeEngine::BufferType::VertexBuffer:
				bufferResource = ((DX11VertexBuffer*)buffer)->get_dx11_buffer().Get();
				break;
			case DopeEngine::BufferType::IndexBuffer:
				bufferResource = ((DX11IndexBuffer*)buffer)->get_dx11_buffer().Get();
				break;
			case DopeEngine::BufferType::UniformBuffer:
				bufferResource = ((DX11ConstantBuffer*)buffer)->get_dx11_buffer().Get();
				break;
			default:
				ASSERT(false, "DX11GraphicsDevice", "Invalid BufferType, cannot update the ID3D11Resource!");
				break;
		}

		/*
		* Map/UnMap and update resource
		*/
		LOG("DX11GraphicsDevice", "Updating %d bytes to buffer %s", buffer->get_allocated_size(),*buffer->get_debug_name());
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		ImmediateContext->Map(bufferResource,0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy(mappedResource.pData, data, buffer->get_allocated_size());
		ImmediateContext->Unmap(bufferResource, 0);
	}

	void DX11GraphicsDevice::update_texture_impl(Texture* texture, const Byte* data)
	{
		/*
		* Get dx11 texture
		*/
		const DX11Texture* dx11Texture = (const DX11Texture*)texture;

		/*
		* Update resource
		*/
		//ImmediateContext->UpdateSubresource(dx11Texture->get(), 0, nullptr, data, 0, 0);
	}

	CommandBuffer* DX11GraphicsDevice::create_command_buffer_impl()
	{
		return new DX11CommandBuffer(this);
	}

	void DX11GraphicsDevice::submit_command_buffer_impl(CommandBuffer* commandBuffer)
	{

	}

	void DX11GraphicsDevice::delete_device_object_impl(DeviceObject* object)
	{

	}

	Buffer* DX11GraphicsDevice::create_buffer_impl(const BufferDescription& description)
	{
		const BufferType type = description.Type;
		switch (type)
		{
			case DopeEngine::BufferType::VertexBuffer:
				return new DX11VertexBuffer(this, description.AllocatedSize, description.PerItemSize);
				break;
			case DopeEngine::BufferType::IndexBuffer:
				return new DX11IndexBuffer(1, description.PerItemSize, description.AllocatedSize, this);
				break;
			case DopeEngine::BufferType::UniformBuffer:
				return new DX11ConstantBuffer(description, this);
				break;
			default:
				ASSERT(false, "DX11GraphicsDevice", "Invalid buffer type, cannot create buffer with the given description!");
				break;
		}
	}

	Framebuffer* DX11GraphicsDevice::create_framebuffer_impl(const FramebufferDescription& description)
	{
		return new DX11Framebuffer(description,this);
	}

	Pipeline* DX11GraphicsDevice::create_pipeline_impl(const PipelineDescription& description)
	{
		return new DX11Pipeline(description,this);
	}

	Shader* DX11GraphicsDevice::create_shader_impl(const ShaderDescription& description)
	{
		return new DX11Shader(description,this);
	}

	ShaderSet* DX11GraphicsDevice::create_shader_set_impl(const Array<Shader*>& shaders)
	{
		return new DX11ShaderSet(shaders);
	}

	Texture* DX11GraphicsDevice::create_texture_impl(const TextureDescription& description)
	{
		return new DX11Texture(description,this);
	}

	GraphicsAPIType DX11GraphicsDevice::get_api_type() const
	{
		return GraphicsAPIType::Directx11;
	}

	String DX11GraphicsDevice::get_version() const
	{
		return "Not implemented yet";
	}

	void DX11GraphicsDevice::make_current_impl()
	{

	}
}