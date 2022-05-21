#pragma once
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
namespace DopeEngine
{
	class DX12SwapchainFramebuffer;
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
		/// Returns the defaul command queue
		/// </summary>
		/// <returns></returns>
		DXPTR<ID3D12CommandQueue> get_dx12_command_queue() const;

		/// <summary>
		/// Returns an avaiable command list
		/// </summary>
		/// <returns></returns>
		DXPTR<ID3D12GraphicsCommandList> get_dx12_available_graphics_command_list() const;

		/// <summary>
		/// Returns the dx12 factory
		/// </summary>
		/// <returns></returns>
		DXPTR<IDXGIFactory4> get_dx12_factory() const;

		// Inherited via GraphicsDevice
		virtual GraphicsAPIType get_api_type() const override;
		virtual String get_version() const override;
	protected:
		virtual void make_current_impl() override;
		virtual void delete_device_object_impl(GraphicsDeviceObject* object) override;
		virtual GraphicsBuffer* create_buffer_impl(const BufferDescription& description) override;
		virtual Framebuffer* create_framebuffer_impl(const FramebufferDescription& description) override;
		virtual RenderPass* create_render_pass_impl(const RenderPassDesc& desc) override;
		virtual Shader* create_shader_impl(const ShaderDescription& description) override;
		virtual Texture* create_texture_impl(const TextureDescription& description) override;
		virtual void submit_command_buffer_impl(CommandBuffer* commandBuffer) override;
		virtual CommandBuffer* create_command_buffer_impl() override;
		// Inherited via GraphicsDevice
		virtual Framebuffer* create_window_swapchain_framebuffer_impl(const SwapchainFramebufferDesc* desc) const override;
		virtual GraphicsResource* create_resource_impl(const GraphicsResourceDesc& desc) override;
		virtual void update_buffer_impl(GraphicsBuffer* buffer, const Byte* data) override;
		virtual void update_texture_impl(Texture* texture, const Byte* data) override;
		virtual void swap_swapchain_buffers_impl(const SwapchainFramebuffer* framebuffer) override;
		virtual void wait_for_finish_impl() override;
	private:
		void _create_directx12_device();
		void _create_win32_directx12_device();
	private:
		DXPTR<IDXGIFactory4> Factory;
		DXPTR<ID3D12Device> Device;
		DXPTR<ID3D12CommandQueue> CommandQueue;
		DXPTR<ID3D12CommandAllocator> CommandAllocator;
		DXPTR<ID3D12GraphicsCommandList> GraphicsCommandList;
		DXPTR<ID3D12Fence> Fence;
		HANDLE FenceEvent;
		unsigned int FenceValue;

		// Inherited via GraphicsDevice
		virtual bool does_support_features(const GraphicsDeviceFeatures* features, Array<String>& messages) override;
	};


}