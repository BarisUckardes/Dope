#pragma once
#include <Engine/Graphics/Command/CommandBuffer.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>
#include <Engine/Graphics/Vertex/VertexLayoutDescription.h>
namespace DopeEngine
{
	class OpenGLVertexLayout;
	class DOPE_ENGINE_API OpenGLCommandBuffer final : public CommandBuffer
	{
	public:
		OpenGLCommandBuffer() = default;
		virtual ~OpenGLCommandBuffer() final = default;

		
		virtual void lock_impl() override;
		virtual void unlock_impl() override;
	protected:
		virtual void clear_cached_state_impl() override final;
		virtual void set_vertex_buffer_impl(const VertexBuffer& vertexBuffer) override final;
		virtual void set_index_buffer_impl(const IndexBuffer& indexBuffer) override final;
		virtual void set_uniform_buffer_impl(const UniformBuffer& buffer) override final;
		virtual void set_framebuffer_impl(const Framebuffer& framebuffer) override final;
		virtual void set_pipeline_impl(const Pipeline& pipeline) override final;
		virtual void clear_color_impl(const ColorRgbaByte& color) override final;
		virtual void clear_depth_impl(const float depth) override final;
		virtual void set_resource_view_impl(const unsigned int slot, const ResourceView* view) override final;
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