#pragma once
#include <Engine/Graphics/Command/GraphicsCommandBuffer.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>
#include <Engine/Graphics/Vertex/VertexLayoutDescription.h>
namespace DopeEngine
{
	class OpenGLVertexLayout;
	class DOPE_ENGINE_API OpenGLCommandBuffer final : public GraphicsCommandBuffer
	{
	public:
		OpenGLCommandBuffer() = default;
		virtual ~OpenGLCommandBuffer() final = default;

		
		virtual void lock_impl() override;
		virtual void unlock_impl() override;
	protected:
		virtual void clear_cached_state_impl() override final;
		virtual void set_vertex_buffer_impl(const VertexBuffer* vertexBuffer) override final;
		virtual void set_index_buffer_impl(const IndexBuffer* indexBuffer) override final;
		virtual void set_uniform_buffer_impl(const UniformBuffer* buffer) override final;
		virtual void start_render_pass_impl(const RenderPass* renderPass) override final;
		virtual void set_viewport_desc_impl(const ViewportDesc& desc) override final;
		virtual void set_scissors_desc_impl(const ScissorsDesc& desc) override final;
		virtual void clear_color_impl(const ColorRgbaByte& color) override final;
		virtual void clear_depth_impl(const float depth) override final;
		virtual void commit_resource_impl(const unsigned int slot, const GraphicsResource* resource) override final;
		virtual void indexed_draw_call_impl(const unsigned int count) override final;
	private:
		PRIMITIVE CurrentPrimitive;
		PROGRAM_HANDLE CurrentProgramHandle;
		VERTEX_LAYOUT_HANDLE CurrentVertexLayoutHandle;
		VERTEX_BUFFER_HANDLE CurrentVertexBufferHandle;
		INDEX_BUFFER_HANDLE CurrentIndexBufferHandle;
		VertexLayoutDescription CurrentVertexLayoutDescription;
	};


}