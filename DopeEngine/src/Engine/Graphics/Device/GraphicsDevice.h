#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Device/GraphicsAPIType.h>
#include <Engine/Structures/String.h>
#include <Engine/Application/Window/Window.h>
#include <Engine/Graphics/Device/GraphicsDeviceProperties.h>


namespace DopeEngine
{
	class Buffer;
	class VertexBuffer;
	class Texture;
	class Framebuffer;
	
	class Shader;
	class ShaderSet;
	class VertexLayout;
	class DeviceObject;
	class CommandBuffer;
	class ResourceView;
	class ResourceLayout;
	class RenderPass;
	struct RenderPassDesc;

	class SwapchainFramebuffer;
	struct SwapchainFramebufferDesc;
	struct BufferDescription;
	struct FramebufferDescription;
	struct ShaderDescription;
	struct TextureDescription;
	struct VertexLayoutDescription;
	struct ResourceDescription;
	struct ResourceViewDescription;
	class GraphicsDeviceFeatures;

	/// <summary>
	/// Graphics device abstraction class
	/// </summary>
	class DOPE_ENGINE_API GraphicsDevice
	{
	public:
		/// <summary>
		/// Creates new graphics device with the specified api type
		/// </summary>
		/// <param name="api"></param>
		/// <param name="ownerWindow"></param>
		/// <returns></returns>
		static GraphicsDevice* create(const GraphicsDeviceFeatures* requestedFeatures,GraphicsAPIType api,Window* ownerWindow = nullptr,const SwapchainFramebufferDesc* swapchainDesc = nullptr);


		/// <summary>
		/// Returns whether this device is the current device
		/// </summary>
		/// <returns></returns>
		bool is_current() const;

		/// <summary>
		/// Returns whether this graphics device has a target window or not
		/// </summary>
		/// <returns></returns>
		bool is_offscreen_device() const;

		/// <summary>
		/// Returns the owner window of this device (if any)
		/// </summary>
		/// <returns></returns>
		const Window* get_owner_window() const;

		/// <summary>
		/// Returns the swapchain framebuffer
		/// </summary>
		/// <returns></returns>
		SwapchainFramebuffer* get_swapchain_framebuffer() const;

		/// <summary>
		/// Returns the graphics device supported features for this device
		/// </summary>
		/// <returns></returns>
		const GraphicsDeviceFeatures* get_supported_features() const;

		/// <summary>
		/// Returns the graphics device properties
		/// </summary>
		/// <returns></returns>
		GraphicsDeviceProperties get_properties() const;

		/// <summary>
		/// Makes this device current for this process
		/// </summary>
		void make_current();

		/// <summary>
		/// Deletes the target device object
		/// </summary>
		/// <param name="object"></param>
		void delete_device_object(DeviceObject* object);

		/// <summary>
		/// Creates a buffer
		/// </summary>
		/// <param name="description"></param>
		/// <returns></returns>
		Buffer* create_buffer(const BufferDescription& description);

		/// <summary>
		/// Creates a framebuffer
		/// </summary>
		/// <param name="description"></param>
		/// <returns></returns>
		Framebuffer* create_framebuffer(const FramebufferDescription& description);

		/// <summary>
		/// Creates a pipeline
		/// </summary>
		/// <param name="description"></param>
		/// <returns></returns>
		RenderPass* create_render_pass(const RenderPassDesc& desc);

		/// <summary>
		/// Creates a shader
		/// </summary>
		/// <param name="description"></param>
		/// <returns></returns>
		Shader* create_shader(const ShaderDescription& description);

		/// <summary>
		/// Creates a texture
		/// </summary>
		/// <param name="description"></param>
		/// <returns></returns>
		Texture* create_texture(const TextureDescription& description);

		/// <summary>
		/// Creates anew command buffer
		/// </summary>
		/// <returns></returns>
		CommandBuffer* create_command_buffer();

		/// <summary>
		/// Creates anew resource layout device object
		/// </summary>
		/// <param name="description"></param>
		/// <returns></returns>
		ResourceLayout* create_resource_layout(const ResourceDescription& description);

		/// <summary>
		/// Creates anew resource view device object
		/// </summary>
		/// <param name="description"></param>
		/// <returns></returns>
		ResourceView* create_resource_view(const ResourceViewDescription& description);

		/// <summary>
		/// Submits a command buffer for rendering.<para>Each API has a different submit impls</para>
		/// </summary>
		void submit_command_buffer(CommandBuffer* commandBuffer);

		/// <summary>
		/// Updates the texture
		/// </summary>
		/// <param name="texture"></param>
		/// <param name="data"></param>
		void update_texture(Texture* texture,const Byte* data);

		/// <summary>
		/// Updates the buffer
		/// </summary>
		/// <param name="buffer"></param>
		/// <param name="data"></param>
		void update_buffer(Buffer* buffer, const Byte* data);

		/// <summary>
		/// Swaps the buffers of the swapchain
		/// </summary>
		void swap_swapchain_buffers(const SwapchainFramebuffer* framebuffer);

		/// <summary>
		/// Awaits the graphics device commands to finish
		/// </summary>
		void wait_for_finish();

		/// <summary>
		/// Returns the graphics api type
		/// </summary>
		/// <returns></returns>
		virtual GraphicsAPIType get_api_type() const = 0;

		/// <summary>
		/// Returns the graphics api version string
		/// </summary>
		/// <returns></returns>
		virtual String get_version() const = 0;

		/// <summary>
		/// Returns whether this graphics device supports the target features
		/// </summary>
		/// <param name="features"></param>
		/// <returns></returns>
		virtual bool does_support_features(const GraphicsDeviceFeatures* features,Array<String>& messages);
	protected:
		GraphicsDevice(Window* window);
		virtual ~GraphicsDevice() = default;

		void set_properties(const GraphicsDeviceProperties& properties);
		void set_features(const GraphicsDeviceFeatures* features);

		virtual void make_current_impl() = 0;
		virtual void delete_device_object_impl(DeviceObject* object) = 0;
		virtual Buffer* create_buffer_impl(const BufferDescription& description) = 0;
		virtual Framebuffer* create_framebuffer_impl(const FramebufferDescription& description) = 0;
		virtual Framebuffer* create_window_swapchain_framebuffer_impl(const SwapchainFramebufferDesc * desc) const = 0;
		virtual RenderPass* create_render_pass_impl(const RenderPassDesc& desc) = 0;
		virtual Shader* create_shader_impl(const ShaderDescription& description) = 0;
		virtual Texture* create_texture_impl(const TextureDescription& description) = 0;
		virtual CommandBuffer* create_command_buffer_impl() = 0;
		virtual ResourceLayout* create_resource_layout_impl(const ResourceDescription& description) = 0;
		virtual ResourceView* create_resource_view_impl(const ResourceViewDescription & description) = 0;
		virtual void submit_command_buffer_impl(CommandBuffer * commandBuffer) = 0;
		virtual void update_buffer_impl(Buffer * buffer, const Byte * data) = 0;
		virtual void update_texture_impl(Texture * texture, const Byte * data) = 0;
		virtual void swap_swapchain_buffers_impl(const SwapchainFramebuffer * framebuffer) = 0;
		virtual void wait_for_finish_impl() = 0;
	private:
		void create_swapchain_framebuffer(const SwapchainFramebufferDesc* desc);
		void register_device_object(DeviceObject* object);
		void remove_device_object(DeviceObject* object);
	private:
		Array<DeviceObject*> ChildObjects;
		Window* OwnerWindow;
		SwapchainFramebuffer* SWCHNFramebuffer;
		GraphicsDeviceFeatures* Features;
		GraphicsDeviceProperties Properties;
		bool Current;
		bool OffscreenGraphicsDevice;
	};


}