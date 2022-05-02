#pragma once
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API VKGraphicsDevice : public GraphicsDevice
	{
	public:
		VKGraphicsDevice(Window* ownerWindow);
		~VKGraphicsDevice() = default;

		FORCEINLINE VkInstance get_vk_instance() const;
		FORCEINLINE VkPhysicalDevice get_vk_physicalDevice() const;
		FORCEINLINE VkDevice get_vk_logical_device() const;
	protected:
		// Inherited via GraphicsDevice
		virtual GraphicsAPIType get_api_type() const override;
		virtual String get_version() const override;
		virtual void make_current_impl() override;
		virtual void delete_device_object_impl(DeviceObject* object) override;
		virtual Buffer* create_buffer_impl(const BufferDescription& description) override;
		virtual Framebuffer* create_framebuffer_impl(const FramebufferDescription& description) override;
		virtual Framebuffer* create_window_swapchain_framebuffer_impl(const unsigned int width, const unsigned int height) const override;
		virtual Pipeline* create_pipeline_impl(const PipelineDescription& description) override;
		virtual Shader* create_shader_impl(const ShaderDescription& description) override;
		virtual ShaderSet* create_shader_set_impl(const Array<Shader*>& shaders) override;
		virtual Texture* create_texture_impl(const TextureDescription& description) override;
		virtual CommandBuffer* create_command_buffer_impl() override;
		virtual ResourceLayout* create_resource_layout_impl(const ResourceDescription& description) override;
		virtual ResourceView* create_resource_view_impl(const ResourceViewDescription& description) override;
		virtual void submit_command_buffer_impl(CommandBuffer* commandBuffer) override;
		virtual void update_buffer_impl(Buffer* buffer, const Byte* data) override;
		virtual void update_texture_impl(Texture* texture, const Byte* data) override;
		virtual void swap_swapchain_buffers_impl(const SwapchainFramebuffer* framebuffer) override;
		virtual void wait_for_finish_impl() override;
	private:
		void _create_vulkan_device();
		void _create_win32_vulkan_device();
	private:
		Array<VkQueue> Queues;
		VkInstance Instance;
		VkPhysicalDevice PhysicalDevice;
		VkDevice LogicalDevice;

		// Inherited via GraphicsDevice
		virtual bool does_support_features(const GraphicsDeviceFeatures* features, Array<String>& messages) override;
	};


}