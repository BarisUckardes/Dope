#pragma once
#include <Engine/Graphics/Command/CommandBuffer.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLCommandBuffer final : public CommandBuffer
	{
	public:
		OpenGLCommandBuffer() = default;
		virtual ~OpenGLCommandBuffer() final = default;

		// Inherited via CommandBuffer
		virtual void set_vertex_buffer(const VertexBuffer& vertexBuffer) override;
		virtual void set_index_buffer(const IndexBuffer& indexBuffer) override;
		virtual void set_framebuffer(const Framebuffer& framebuffer) override;
		virtual void set_pipeline(const Pipeline& pipeline) override;
		virtual void set_shader_set(const ShaderSet& shaderSet) override;
		virtual void set_vertex_layout(const VertexLayout& layout) override;
		virtual void clear_color(const ColorRgbaByte& color) override;
		virtual void clear_depth(const float depth) override;
		virtual void lock_impl() override;
		virtual void unlock_impl() override;
	};


}