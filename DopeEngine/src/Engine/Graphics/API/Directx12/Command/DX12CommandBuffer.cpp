#include "DX12CommandBuffer.h"
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	DX12CommandBuffer::DX12CommandBuffer(DX12GraphicsDevice* device)
	{
		/*
		* Create command list
		*/
		HRESULT createCommandListHR = device->get_dx12_device()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, device->get_dx12_command_allocators()[0], NULL, IID_PPV_ARGS(&CommandList));
		
		/*
		* Validate command list creation
		*/
		ASSERT(SUCCEEDED(createCommandListHR), "DX12CommandBuffer", "Command list creation failed");

		/*
		* Close command list because the default state is the recording state
		*/
		CommandList->Close();
	}
	DX12CommandBuffer::~DX12CommandBuffer()
	{

	}
	void DX12CommandBuffer::unlock_impl()
	{

	}
	void DX12CommandBuffer::lock_impl()
	{

	}
	void DX12CommandBuffer::clear_cached_state_impl()
	{

	}
	void DX12CommandBuffer::set_vertex_buffer_impl(const VertexBuffer& vertexBuffer)
	{

	}
	void DX12CommandBuffer::set_index_buffer_impl(const IndexBuffer& indexBuffer)
	{

	}
	void DX12CommandBuffer::set_uniform_buffer_impl(const UniformBuffer& buffer)
	{

	}
	void DX12CommandBuffer::set_framebuffer_impl(const Framebuffer& framebuffer)
	{

	}
	void DX12CommandBuffer::set_pipeline_impl(const Pipeline& pipeline)
	{

	}
	void DX12CommandBuffer::clear_color_impl(const ColorRgbaByte& color)
	{

	}
	void DX12CommandBuffer::clear_depth_impl(const float depth)
	{

	}
	void DX12CommandBuffer::set_resource_view_impl(const unsigned int slot, const ResourceView* view)
	{

	}
	void DX12CommandBuffer::indexed_draw_call_impl(const unsigned int count)
	{

	}
	
}