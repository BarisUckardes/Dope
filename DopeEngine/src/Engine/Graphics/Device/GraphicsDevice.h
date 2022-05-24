#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/API/GraphicsAPIType.h>
#include <Engine/Structures/String.h>
#include <Engine/Application/Window/Window.h>
#include <Engine/Graphics/Device/GraphicsDeviceProperties.h>
#include <Engine/Graphics/Device/GraphicsDeviceFeatures.h>


namespace DopeEngine
{
	class GraphicsBuffer;
	class VertexBuffer;
	class Texture;
	class Framebuffer;
	
	class Shader;
	class ShaderSet;
	class VertexLayout;
	class GraphicsDeviceObject;
	class GraphicsCommandBuffer;
	class GraphicsResource;
	class RenderPass;
	struct RenderPassDesc;

	class SwapchainFramebuffer;
	struct SwapchainFramebufferDesc;
	struct BufferDescription;
	struct FramebufferDescription;
	struct ShaderDescription;
	struct TextureDescription;
	struct VertexLayoutDescription;
	struct GraphicsResourceSlotDesc;
	struct GraphicsResourceDesc;
	class GraphicsDeviceFeatures;

	/// <summary>
	/// Graphics device abstraction class
	/// </summary>
	class DOPE_ENGINE_API GraphicsDevice
	{
	public:
		static GraphicsDevice* create(const GraphicsDeviceFeatures* requestedFeatures,GraphicsAPIType api,Window* ownerWindow = nullptr,const SwapchainFramebufferDesc* swapchainDesc = nullptr);


		bool is_current() const;
		bool is_offscreen_device() const;
		const Window* get_owner_window() const;
		SwapchainFramebuffer* get_swapchain_framebuffer() const;
		const GraphicsDeviceFeatures* get_supported_features() const;
		GraphicsDeviceProperties get_properties() const;
		GraphicsBuffer* create_buffer(const BufferDescription& description);
		Framebuffer* create_framebuffer(const FramebufferDescription& description);
		RenderPass* create_render_pass(const RenderPassDesc& desc);
		Shader* create_shader(const ShaderDescription& description);
		Texture* create_texture(const TextureDescription& description);
		GraphicsCommandBuffer* create_command_buffer();
		GraphicsResource* create_resource(const GraphicsResourceDesc& desc);

		void make_current();
		void delete_device_object(GraphicsDeviceObject* object);
		void submit_command_buffer(GraphicsCommandBuffer* GraphicsCommandBuffer);
		void update_texture(Texture* texture,const Byte* data);
		void update_buffer(GraphicsBuffer* buffer, const Byte* data);
		void swap_swapchain_buffers(const SwapchainFramebuffer* framebuffer);
		void wait_for_finish();

		virtual GraphicsAPIType get_api_type() const = 0;
		virtual String get_version() const = 0;
		virtual bool does_support_features(const GraphicsDeviceFeatures* features,Array<String>& messages);
	protected:
		GraphicsDevice(Window* window);
		virtual ~GraphicsDevice() = default;

		void set_properties(const GraphicsDeviceProperties& properties);
		void set_features(const GraphicsDeviceFeatures* features);

		virtual void make_current_impl() = 0;
		virtual void delete_device_object_impl(GraphicsDeviceObject * object) = 0;
		virtual GraphicsBuffer* create_buffer_impl(const BufferDescription& description) = 0;
		virtual Framebuffer* create_framebuffer_impl(const FramebufferDescription& description) = 0;
		virtual Framebuffer* create_window_swapchain_framebuffer_impl(const SwapchainFramebufferDesc * desc) const = 0;
		virtual RenderPass* create_render_pass_impl(const RenderPassDesc& desc) = 0;
		virtual Shader* create_shader_impl(const ShaderDescription& description) = 0;
		virtual Texture* create_texture_impl(const TextureDescription& description) = 0;
		virtual GraphicsCommandBuffer* create_command_buffer_impl() = 0;
		virtual GraphicsResource* create_resource_impl(const GraphicsResourceDesc& desc) = 0;
		virtual void submit_command_buffer_impl(GraphicsCommandBuffer * GraphicsCommandBuffer) = 0;
		virtual void update_buffer_impl(GraphicsBuffer * buffer, const Byte * data) = 0;
		virtual void update_texture_impl(Texture * texture, const Byte * data) = 0;
		virtual void swap_swapchain_buffers_impl(const SwapchainFramebuffer * framebuffer) = 0;
		virtual void wait_for_finish_impl() = 0;
	private:
		void create_swapchain_framebuffer(const SwapchainFramebufferDesc* desc);
		void register_device_object(GraphicsDeviceObject * object);
		void remove_device_object(GraphicsDeviceObject * object);
	private:
		Array<GraphicsDeviceObject*> ChildObjects;
		Window* OwnerWindow;
		SwapchainFramebuffer* SWCHNFramebuffer;
		GraphicsDeviceFeatures* Features;
		GraphicsDeviceProperties Properties;
		bool Current;
		bool OffscreenGraphicsDevice;
	};


}