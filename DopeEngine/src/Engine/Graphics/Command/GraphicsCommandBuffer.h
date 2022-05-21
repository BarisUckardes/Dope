#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Math/ColorRgbaByte.h>
#include <Engine/Graphics/Device/GraphicsDeviceObject.h>
#include <Engine/Graphics/RenderPass/RenderPassDesc.h>
namespace DopeEngine
{

	class GraphicsBuffer;
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
	class GraphicsResource;
	struct ColorRgbaByte;

	/// <summary>
	/// Graphics api agnostic GraphicsCommandBuffer abstraction class
	/// </summary>
	class DOPE_ENGINE_API GraphicsCommandBuffer : public GraphicsDeviceObject
	{
	public:
		/// <summary>
		/// Locks the GraphicsCommandBuffer sumbit
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
		void start_render_pass(const RenderPass* renderPass);

		/// <summary>
		/// Sets the viewport desc for the current command buffer
		/// </summary>
		/// <param name="desc"></param>
		void set_viewport_desc(const ViewportDesc& desc);

		/// <summary>
		/// Sets the scissors desc for the current command buffer
		/// </summary>
		/// <param name="desc"></param>
		void set_scissors_desc(const ScissorsDesc& desc);

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
		void commit_resource(const unsigned int slot, const GraphicsResource* resource);

		/// <summary>
		/// Draw call
		/// </summary>
		void indexed_draw_call(const unsigned int count);
	protected:
		GraphicsCommandBuffer() : GraphicsDeviceObject(GraphicsDeviceObjectType::GraphicsCommandBuffer), CurrentBoundTextures(0),CurrentBoundRenderPass(nullptr),CurrentBoundUniformBuffers(0) {}
		virtual ~GraphicsCommandBuffer() = 0 {}

		/// <summary>
		/// Returns the total number of bound textures
		/// </summary>
		unsigned int get_bound_texture_count() const;

		/// <summary>
		/// Returns the bound render pass
		/// </summary>
		/// <returns></returns>
		const RenderPass* get_bound_render_pass() const;

		/// <summary>
		/// Returns the bound viewport description
		/// </summary>
		/// <returns></returns>
		ViewportDesc get_bound_viewport_desc() const;

		/// <summary>
		/// Returns the bound scissors description
		/// </summary>
		/// <returns></returns>
		ScissorsDesc get_bound_scissors_desc() const;

		/// <summary>
		/// Returns the total number of bound uniform buffers
		/// </summary>
		/// <returns></returns>
		unsigned int get_bound_uniformbuffer_count() const;

		/// <summary>
		/// Increments the total number of bound textures
		/// </summary>
		void increment_texture_bound_count();

		/// <summary>
		/// Increments the total number of bound uniformbuffers
		/// </summary>
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
		virtual void start_render_pass_impl(const RenderPass* renderPass) = 0;

		/// <summary>
		/// Set viewport desc impl
		/// </summary>
		/// <param name="desc"></param>
		virtual void set_viewport_desc_impl(const ViewportDesc& desc) = 0;

		/// <summary>
		/// Set scissors desc impl
		/// </summary>
		/// <param name="desc"></param>
		virtual void set_scissors_desc_impl(const ScissorsDesc& desc) = 0;

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
		virtual void commit_resource_impl(const unsigned int slot, const GraphicsResource* view) = 0;

		/// <summary>
		/// Draw call
		/// </summary>
		virtual void indexed_draw_call_impl(const unsigned int count) = 0;
	private:
		void clear_cached_state();
	private:
		const RenderPass* CurrentBoundRenderPass;
		ViewportDesc CurrentBoundViewportDesc;
		ScissorsDesc CurrentBoundScissorsDesc;
		unsigned int CurrentBoundTextures;
		unsigned int CurrentBoundUniformBuffers;
	};


}