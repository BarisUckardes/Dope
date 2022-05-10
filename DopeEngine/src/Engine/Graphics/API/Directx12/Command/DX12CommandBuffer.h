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

		DXPTR<ID3D12GraphicsCommandList> get_dx12_command_list() const;
	protected:
		// Inherited via CommandBuffer
		virtual void unlock_impl() override;
		virtual void clear_cached_state_impl() override;
		virtual void set_vertex_buffer_impl(const VertexBuffer* vertexBuffer) override;
		virtual void set_index_buffer_impl(const IndexBuffer* indexBuffer) override;
		virtual void set_uniform_buffer_impl(const UniformBuffer* buffer) override;
		virtual void start_render_pass_impl(const RenderPass* renderPass) override;
		virtual void set_viewport_desc_impl(const ViewportDesc& desc) override final;
		virtual void set_scissors_desc_impl(const ScissorsDesc& desc) override final;
		virtual void clear_color_impl(const ColorRgbaByte& color) override;
		virtual void clear_depth_impl(const float depth) override;
		virtual void set_resource_view_impl(const unsigned int slot, const ResourceView* view) override;
		virtual void indexed_draw_call_impl(const unsigned int count) override;
		virtual void lock_impl();
	private:
		DXPTR<ID3D12CommandAllocator> Allocator;
		DXPTR<ID3D12GraphicsCommandList> CommandList;
		DXPTR<ID3D12DescriptorHeap> RtvHeap;
		D3D12_VIEWPORT CurrentDX12Viewport;
		D3D12_RECT CurrentDX12Scissors;
		const Framebuffer* CurrentFramebuffer;
		unsigned int RtvDescriptorSize;
	};


}