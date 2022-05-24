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
		void lock();
		void unlock();
		void set_vertex_buffer(const VertexBuffer* vertexBuffer);
		void set_index_buffer(const IndexBuffer* indexBuffer);
		void set_uniform_buffer(const UniformBuffer* buffer);
		void set_render_pass(const RenderPass* renderPass);
		void set_viewport_desc(const ViewportDesc& desc);
		void set_scissors_desc(const ScissorsDesc& desc);
		void clear_color(const ColorRgbaByte& color);
		void clear_depth(const float depth);
		void commit_resource(const unsigned int slot, const GraphicsResource* resource);
		void indexed_draw_call(const unsigned int count);
	protected:
		GraphicsCommandBuffer() : GraphicsDeviceObject(GraphicsDeviceObjectType::GraphicsCommandBuffer), CurrentBoundTextures(0),CurrentBoundRenderPass(nullptr),CurrentBoundUniformBuffers(0) {}
		virtual ~GraphicsCommandBuffer() = 0 {}


		unsigned int get_bound_texture_count() const;
		const RenderPass* get_bound_render_pass() const;
		ViewportDesc get_bound_viewport_desc() const;
		ScissorsDesc get_bound_scissors_desc() const;
		unsigned int get_bound_uniformbuffer_count() const;
		void increment_texture_bound_count();
		void increment_uniformbuffer_bound_count();

		virtual void lock_impl() = 0;
		virtual void unlock_impl() = 0;
		virtual void clear_cached_state_impl() = 0;


		virtual void set_vertex_buffer_impl(const VertexBuffer* vertexBuffer) = 0;
		virtual void set_index_buffer_impl(const IndexBuffer* indexBuffer) = 0;
		virtual void set_uniform_buffer_impl(const UniformBuffer* buffer) = 0;
		virtual void set_render_pass_impl(const RenderPass* renderPass) = 0;
		virtual void set_viewport_desc_impl(const ViewportDesc& desc) = 0;
		virtual void set_scissors_desc_impl(const ScissorsDesc& desc) = 0;
		virtual void clear_color_impl(const ColorRgbaByte& color) = 0;
		virtual void clear_depth_impl(const float depth) = 0;
		virtual void commit_resource_impl(const unsigned int slot, const GraphicsResource* view) = 0;
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