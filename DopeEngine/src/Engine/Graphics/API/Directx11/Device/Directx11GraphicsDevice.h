#pragma once
#include <Engine/Graphics/Device/GraphicsDevice.h>

//namespace DopeEngine
//{
//	class DOPE_ENGINE_API Directx11GraphicsDevice : public GraphicsDevice
//	{
//	public:
//		Directx11GraphicsDevice(Window* ownerWindow);
//		~Directx11GraphicsDevice() = default;
//
//		// Inherited via GraphicsDevice
//		virtual GraphicsAPIType get_api_type() const override;
//		virtual String get_version() const override;
//	protected:
//		virtual void make_current_impl() override;
//		virtual void delete_device_object_impl(DeviceObject* object) override;
//		virtual Buffer* create_buffer_impl(const BufferDescription& description) override;
//		virtual Framebuffer* create_framebuffer_impl(const FramebufferDescription& description) override;
//		virtual Framebuffer* create_window_swapchain_framebuffer_impl() const override;
//		virtual Pipeline* create_pipeline_impl(const PipelineDescription& description) override;
//		virtual Shader* create_shader_impl(const ShaderDescription& description) override;
//		virtual ShaderSet* create_shader_set_impl(const Array<Shader*>& shaders) override;
//		virtual Texture* create_texture_impl(const TextureDescription& description) override;
//		virtual void submit_command_buffer_impl(CommandBuffer* commandBuffer) override;
//		virtual CommandBuffer* create_command_buffer_impl() override;
//	private:
//		void _create_directx11_device();
//		void _create_win32_directx11_device();
//
//	};
//
//
//}