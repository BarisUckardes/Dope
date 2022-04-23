#pragma once
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX12GraphicsDevice : public GraphicsDevice
	{
	public:
		DX12GraphicsDevice(Window* ownerWindow);
		~DX12GraphicsDevice();

		/// <summary>
		/// Returns the native dx12 device
		/// </summary>
		/// <returns></returns>
		DXPTR<ID3D12Device> get_dx12_device() const;

		/// <summary>
		/// Returns the command allocators
		/// </summary>
		/// <returns></returns>
		DXPTR<ID3D12CommandAllocator> get_dx12_command_allocator() const;

		/// <summary>
		/// Returns this device's swachain (if any)
		/// </summary>
		/// <returns></returns>
		DXPTR<IDXGISwapChain3> get_dx12_swapchain() const;

		/// <summary>
		/// Returns the swapchain backbuffer render target views
		/// </summary>
		/// <returns></returns>
		Array<DXPTR<ID3D12Resource>> get_dx12_swapchain_rtvs() const;

		// Inherited via GraphicsDevice
		virtual GraphicsAPIType get_api_type() const override;
		virtual String get_version() const override;
	protected:
		virtual void make_current_impl() override;
		virtual void delete_device_object_impl(DeviceObject* object) override;
		virtual Buffer* create_buffer_impl(const BufferDescription& description) override;
		virtual Framebuffer* create_framebuffer_impl(const FramebufferDescription& description) override;
		virtual Pipeline* create_pipeline_impl(const PipelineDescription& description) override;
		virtual Shader* create_shader_impl(const ShaderDescription& description) override;
		virtual ShaderSet* create_shader_set_impl(const Array<Shader*>& shaders) override;
		virtual Texture* create_texture_impl(const TextureDescription& description) override;
		virtual void submit_command_buffer_impl(CommandBuffer* commandBuffer) override;
		virtual CommandBuffer* create_command_buffer_impl() override;
		// Inherited via GraphicsDevice
		virtual Framebuffer* create_window_swapchain_framebuffer_impl(const unsigned int width, const unsigned int height) const override;
		virtual ResourceLayout* create_resource_layout_impl(const ResourceDescription& description) override;
		virtual ResourceView* create_resource_view_impl(const ResourceViewDescription& description) override;
		virtual void update_buffer_impl(Buffer* buffer, const Byte* data) override;
		virtual void update_texture_impl(Texture* texture, const Byte* data) override;
		virtual void swap_swapchain_buffers_impl() override;
	private:
		void _create_directx12_device();
		void _create_win32_directx12_device();
	private:
		DXPTR<IDXGISwapChain3> Swapchain;
		DXPTR<ID3D12Device> Device;
		DXPTR<ID3D12DescriptorHeap> RtvHeapDescriptor;
		DXPTR<ID3D12CommandQueue> CommandQueue;
		DXPTR<ID3D12CommandAllocator> CommandAlocator;
		Array<DXPTR<ID3D12Resource>> RenderTargets;
		


	};


}