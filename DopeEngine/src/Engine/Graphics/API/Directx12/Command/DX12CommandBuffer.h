#pragma once
#include <Engine/Graphics/API/Directx12/Core/DX12Core.h>
#include <Engine/Graphics/Command/CommandBuffer.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API DX12CommandBuffer : public CommandBuffer
	{
	public:
		DX12CommandBuffer(DX12GraphicsDevice* device);
		virtual ~DX12CommandBuffer() final override;

	protected:
		// Inherited via CommandBuffer
		virtual void unlock_impl() override;
		virtual void clear_cached_state_impl() override;
		virtual void set_vertex_buffer_impl(const VertexBuffer& vertexBuffer) override;
		virtual void set_index_buffer_impl(const IndexBuffer& indexBuffer) override;
		virtual void set_uniform_buffer_impl(const UniformBuffer& buffer) override;
		virtual void set_framebuffer_impl(const Framebuffer& framebuffer) override;
		virtual void set_pipeline_impl(const Pipeline& pipeline) override;
		virtual void clear_color_impl(const ColorRgbaByte& color) override;
		virtual void clear_depth_impl(const float depth) override;
		virtual void set_resource_view_impl(const unsigned int slot, const ResourceView* view) override;
		virtual void indexed_draw_call_impl(const unsigned int count) override;
		virtual void lock_impl();
	private:
		ID3D12GraphicsCommandList* CommandList;
	};


}