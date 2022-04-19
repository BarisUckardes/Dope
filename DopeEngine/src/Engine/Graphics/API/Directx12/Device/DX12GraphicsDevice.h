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
		IDXGISwapChain3* Swapchain;
		ID3D12Device* Device;

	};


}