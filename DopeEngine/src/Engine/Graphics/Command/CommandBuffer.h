#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Math/ColorRgbaByte.h>
#include <Engine/Graphics/Device/DeviceObject.h>
namespace DopeEngine
{
	class Buffer;
	class VertexBuffer;
	class IndexBuffer;
	class UniformBuffer;
	class Texture;
	class Framebuffer;
	class RenderPass;
	class Shader;
	class ShaderSet;
	class VertexLayout;
	class DeviceObject;
	class ResourceLayout;
	class ResourceView;
	struct ColorRgbaByte;

	/// <summary>
	/// Graphics api agnostic commandbuffer abstraction class
	/// </summary>
	class DOPE_ENGINE_API CommandBuffer : public DeviceObject
	{
	public:
		/// <summary>
		/// Locks the commandbuffer sumbit
		/// </summary>
		void lock();

		/// <summary>
		/// Unlocks the command submit
		/// </summary>
		void unlock();

		/// <summary>
		/// Sets the target vertex buffer
		/// </summary>
		/// <param name="vertexBuffer"></param>
		void set_vertex_buffer(const VertexBuffer* vertexBuffer);

		/// <summary>
		/// Sets the target index buffer
		/// </summary>
		/// <param name="indexBuffer"></param>
		void set_index_buffer(const IndexBuffer* indexBuffer);

		/// <summary>
		/// Sets a uniform buffer
		/// </summary>
		/// <param name="buffer"></param>
		void set_uniform_buffer(const UniformBuffer* buffer);

		/// <summary>
		/// Sets the target pipeline
		/// </summary>
		/// <param name="pipeline"></param>
		void set_render_pass(const RenderPass* renderPass);

		/// <summary>
		/// Clears the color
		/// </summary>
		/// <param name="color"></param>
		void clear_color(const ColorRgbaByte& color);

		/// <summary>
		/// Clears the depth
		/// </summary>
		/// <param name="depth"></param>
		void clear_depth(const float depth);

		/// <summary>
		/// Sets a resource view
		/// </summary>
		/// <param name="slot"></param>
		/// <param name="view"></param>
		void set_resource_view(const unsigned int slot, const ResourceView* view);

		/// <summary>
		/// Draw call
		/// </summary>
		void indexed_draw_call(const unsigned int count);
	protected:
		CommandBuffer() : DeviceObject(DeviceObjectType::CommandBuffer), CurrentBoundTextures(0),CurrentBoundRenderPass(nullptr),CurrentBoundUniformBuffers(0) {}
		virtual ~CommandBuffer() = 0 {}


		unsigned int get_bound_texture_count() const;
		const RenderPass* get_bound_render_pass() const;
		unsigned int get_bound_uniformbuffer_count() const;
		void increment_texture_bound_count();
		void increment_uniformbuffer_bound_count();

		virtual void lock_impl() = 0;
		virtual void unlock_impl() = 0;
		virtual void clear_cached_state_impl() = 0;

		/// <summary>
		/// Sets the target vertex buffer
		/// </summary>
		/// <param name="vertexBuffer"></param>
		virtual void set_vertex_buffer_impl(const VertexBuffer* vertexBuffer) = 0;

		/// <summary>
		/// Sets the target index buffer
		/// </summary>
		/// <param name="indexBuffer"></param>
		virtual void set_index_buffer_impl(const IndexBuffer* indexBuffer) = 0;

		/// <summary>
		/// Sets a uniform buffer
		/// </summary>
		/// <param name="buffer"></param>
		virtual void set_uniform_buffer_impl(const UniformBuffer* buffer) = 0;

		/// <summary>
		/// Sets the target pipeline
		/// </summary>
		/// <param name="pipeline"></param>
		virtual void set_render_pass_impl(const RenderPass* renderPass) = 0;

		/// <summary>
		/// Clears the color
		/// </summary>
		/// <param name="color"></param>
		virtual void clear_color_impl(const ColorRgbaByte& color) = 0;

		/// <summary>
		/// Clears the depth
		/// </summary>
		/// <param name="depth"></param>
		virtual void clear_depth_impl(const float depth) = 0;

		/// <summary>
		/// Set resource view api impl
		/// </summary>
		/// <param name="slot"></param>
		/// <param name="view"></param>
		virtual void set_resource_view_impl(const unsigned int slot, const ResourceView* view) = 0;

		/// <summary>
		/// Draw call
		/// </summary>
		virtual void indexed_draw_call_impl(const unsigned int count) = 0;
	private:
		void clear_cached_state();
	private:
		const RenderPass* CurrentBoundRenderPass;
		unsigned int CurrentBoundTextures;
		unsigned int CurrentBoundUniformBuffers;
	};


}