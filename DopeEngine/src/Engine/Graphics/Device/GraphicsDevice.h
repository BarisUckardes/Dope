#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Device/GraphicsAPIType.h>
#include <Engine/Structures/String.h>
#include <Engine/Application/Window/Window.h>
#include <Engine/Graphics/Buffer/BufferDescription.h>
#include <Engine/Graphics/Framebuffer/FramebufferDescription.h>
#include <Engine/Graphics/Pipeline/PipelineDescription.h>
#include <Engine/Graphics/Shader/ShaderDescription.h>
#include <Engine/Graphics/Texture/TextureDescription.h>
#include <Engine/Graphics/Vertex/VertexLayoutDescription.h>
#include <Engine/Graphics/Resource/ResourceLayout.h>
#include <Engine/Graphics/Resource/ResourceView.h>

namespace DopeEngine
{
	class Buffer;
	class VertexBuffer;
	class Texture;
	class Framebuffer;
	class Pipeline;
	class Shader;
	class ShaderSet;
	class VertexLayout;
	class DeviceObject;
	class CommandBuffer;
	class ResourceView;
	class ResourceLayout;
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
		static GraphicsDevice* create(GraphicsAPIType api,Window* ownerWindow);

		/// <summary>
		/// Returns whether this device is the current device
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_current() const;

		/// <summary>
		/// Returns the owner window of this device (if any)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Window* get_owner_window() const;

		/// <summary>
		/// Returns the swapchain framebuffer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Framebuffer* get_swapchain_framebuffer() const;

		/// <summary>
		/// Makes this device current for this process
		/// </summary>
		FORCEINLINE void make_current();

		/// <summary>
		/// Deletes the target device object
		/// </summary>
		/// <param name="object"></param>
		void delete_device_object(DeviceObject* object);

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
		Pipeline* create_pipeline(const PipelineDescription& description);

		/// <summary>
		/// Creates a shader
		/// </summary>
		/// <param name="description"></param>
		/// <returns></returns>
		Shader* create_shader(const ShaderDescription& description);

		/// <summary>
		/// Creates a shader set
		/// </summary>
		/// <param name="shaders"></param>
		/// <returns></returns>
		ShaderSet* create_shader_set(const Array<Shader*>& shaders);

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
		ResourceLayout* create_resource_layout(const ResourceLayoutDescription& description);

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

	protected:
		GraphicsDevice(Window* window);
		virtual ~GraphicsDevice() = default;

		virtual void make_current_impl() = 0;
		virtual void delete_device_object_impl(DeviceObject* object) = 0;
		virtual Buffer* create_buffer_impl(const BufferDescription& description) = 0;
		virtual Framebuffer* create_framebuffer_impl(const FramebufferDescription& description) = 0;
		virtual Framebuffer* create_window_swapchain_framebuffer_impl(const unsigned int width, const unsigned int height) const = 0;
		virtual Pipeline* create_pipeline_impl(const PipelineDescription& description) = 0;
		virtual Shader* create_shader_impl(const ShaderDescription& description) = 0;
		virtual ShaderSet* create_shader_set_impl(const Array<Shader*>& shaders) = 0;
		virtual Texture* create_texture_impl(const TextureDescription& description) = 0;
		virtual CommandBuffer* create_command_buffer_impl() = 0;
		virtual ResourceLayout* create_resource_layout_impl(const ResourceLayoutDescription & description) = 0;
		virtual ResourceView* create_resource_view_impl(const ResourceViewDescription & description) = 0;
		virtual void submit_command_buffer_impl(CommandBuffer * commandBuffer) = 0;

	private:
		void create_swapchain_framebuffer();
		FORCEINLINE void register_device_object(DeviceObject* object);
		FORCEINLINE void remove_device_object(DeviceObject* object);
	private:
		Array<DeviceObject*> ChildObjects;
		Window* OwnerWindow;
		Framebuffer* SwapchainFramebuffer;
		bool Current;
	};


}