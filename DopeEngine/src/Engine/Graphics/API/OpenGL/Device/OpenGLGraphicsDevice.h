#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>

#ifdef DOPE_OS_WINDOWS
#include <Windows.h>
#endif

namespace DopeEngine
{
	/// <summary>
	/// Graphics device OpenGL implementation
	/// </summary>
	class OpenGLGraphicsDevice : public GraphicsDevice
	{
	public:
		OpenGLGraphicsDevice(Window* ownerWindow);
		virtual ~OpenGLGraphicsDevice() override;

		// Inherited via GraphicsDevice
		virtual GraphicsAPIType get_api_type() const override;
		virtual String get_version() const override;
	protected:
		virtual void make_current_impl() override;
		virtual void delete_device_object_impl(DeviceObject* object) override;
		virtual Buffer* create_buffer_impl(const BufferDescription& description) override;
		virtual Framebuffer* create_framebuffer_impl(const FramebufferDescription& description) override;
		virtual Framebuffer* create_window_swapchain_framebuffer_impl(const SwapchainFramebufferDesc* desc) const override;
		virtual Pipeline* create_pipeline_impl(const PipelineDescription& description) override;
		virtual Shader* create_shader_impl(const ShaderDescription& description) override;
		virtual ShaderSet* create_shader_set_impl(const Array<Shader*>& shaders) override;
		virtual Texture* create_texture_impl(const TextureDescription& description) override;
		virtual ResourceLayout* create_resource_layout_impl(const ResourceDescription& description) override;
		virtual ResourceView* create_resource_view_impl(const ResourceViewDescription& description) override;
		virtual CommandBuffer* create_command_buffer_impl() override;
		virtual void submit_command_buffer_impl(CommandBuffer* commandBuffer) override;
	private:
		void _create_opengl_device();
		void _create_opengl_win32_device();

	private:
#ifdef DOPE_OS_WINDOWS
		HGLRC WindowOpenGLContext;
		HDC WindowDeviceContext;
#endif

		// Inherited via GraphicsDevice
		virtual void update_buffer_impl(Buffer* buffer, const Byte* data) override;
		virtual void update_texture_impl(Texture* texture, const Byte* data) override;

		// Inherited via GraphicsDevice
		virtual void swap_swapchain_buffers_impl(const SwapchainFramebuffer* framebuffer) override;

		// Inherited via GraphicsDevice
		virtual void wait_for_finish_impl() override;

		// Inherited via GraphicsDevice
		virtual bool does_support_features(const GraphicsDeviceFeatures* features, Array<String>& messages) override;
	};
}