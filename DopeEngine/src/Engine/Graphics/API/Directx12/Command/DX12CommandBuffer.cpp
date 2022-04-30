#include "DX12CommandBuffer.h"
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Device/DX12DeviceObjects.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Directx12/Helper/DX12Helper.h>
#include <Engine/Graphics/API/Directx12/Pipeline/DX12PipelineUtils.h>
namespace DopeEngine
{

	DX12CommandBuffer::DX12CommandBuffer(DX12GraphicsDevice* device)
	{
		/*
		* Get allocator
		*/
		Allocator = device->get_dx12_command_allocator();

		/*
		* Get rtv descriptor size
		*/
		RtvDescriptorSize = device->get_dx12_device()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		/*
		* Get command list
		*/
		CommandList = device->get_dx12_available_graphics_command_list();
	}
	DX12CommandBuffer::~DX12CommandBuffer()
	{

	}
	DXPTR<ID3D12GraphicsCommandList> DX12CommandBuffer::get_dx12_command_list() const
	{
		return CommandList;
	}
	void DX12CommandBuffer::unlock_impl()
	{
		/*
		* Validate if there is a framebuffer bound
		*/
		if (CurrentFramebuffer != nullptr)
		{
			/*
			* Validate if the framebuffer is a swapchain framebuffer
			*/
			if (CurrentFramebuffer->is_swapchain_framebuffer())
			{
				/*
				* Unlock the barrier
				*/
				D3D12_RESOURCE_BARRIER barrier = {};
				barrier.Transition.pResource = ((const DX12SwapchainFramebuffer*)CurrentFramebuffer)->get_dx12_current_rtv().Get();
				barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
				barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
				barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
				barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
				barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

				/*
				* Set barrier
				*/
				CommandList->ResourceBarrier(1, &barrier);
			}
		}
		
		/*
		* Close command list
		*/
		CommandList->Close();
	}
	void DX12CommandBuffer::lock_impl()
	{
		/*
		* Reset
		*/
		HRESULT resetCmdListHR = CommandList->Reset(Allocator.Get(), nullptr);

		/*
		* Validate reset
		*/
		ASSERT(SUCCEEDED(resetCmdListHR), "DX12CommandBuffer", "Cannot reset the command list");
	}
	void DX12CommandBuffer::clear_cached_state_impl()
	{
		CurrentFramebuffer = nullptr;
	}
	void DX12CommandBuffer::set_vertex_buffer_impl(const VertexBuffer* vertexBuffer)
	{
		CommandList->IASetVertexBuffers(0,1,&((const DX12VertexBuffer*)vertexBuffer)->get_dx12_vertex_buffer_view());
	}
	void DX12CommandBuffer::set_index_buffer_impl(const IndexBuffer* indexBuffer)
	{
		CommandList->IASetIndexBuffer(&((const DX12IndexBuffer*)indexBuffer)->get_dx12_index_buffer_view());
	}
	void DX12CommandBuffer::set_uniform_buffer_impl(const UniformBuffer* buffer)
	{

	}
	void DX12CommandBuffer::set_framebuffer_impl(const Framebuffer* framebuffer)
	{
		/*
		* Validate if this framebuffer is a swapchain framebuffer
		*/
		D3D12_RESOURCE_BARRIER barrier = {};
		if (framebuffer->is_swapchain_framebuffer())
		{
			/*
			* Get dx12 framebuffer
			*/
			const DX12SwapchainFramebuffer* swapFramebuffer = (const DX12SwapchainFramebuffer*)framebuffer;

			/*
			* Initialize barrier
			*/
			barrier.Transition.pResource = swapFramebuffer->get_dx12_current_rtv().Get();
			barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
			barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
			barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
			barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;

			/*
			* Set resource barrier
			*/
			CommandList->ResourceBarrier(1, &barrier);

			/*
			* Get heap descriptor
			*/
			D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = swapFramebuffer->get_dx12_rtv_heap()->GetCPUDescriptorHandleForHeapStart();

			/*
			* Get rtv handle
			*/
			rtvHandle.ptr += swapFramebuffer->get_dx12_swapchain_current_rtv_index() * RtvDescriptorSize;

			/*
			* Set targets
			*/
			CommandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);
		}
		
		/*
		* Set as current framebuffer
		*/
		CurrentFramebuffer = framebuffer;
	}
	void DX12CommandBuffer::set_pipeline_impl(const Pipeline* pipeline)
	{
		/*
		* Get dx12 pipeline
		*/
		const DX12Pipeline* dxPipeline = (const DX12Pipeline*)pipeline;

		/*
		* Set signature
		*/
		CommandList->SetGraphicsRootSignature(dxPipeline->get_dx12_root_signature().Get());

		/*
		* Set pso
		*/
		CommandList->SetPipelineState(dxPipeline->get_dx12_pso().Get());

		/*
		* Set viewport
		*/
		D3D12_VIEWPORT vp = dxPipeline->get_dx12_viewport();
		CommandList->RSSetViewports(1,&vp);
		
		/*
		* Set scissors
		*/
		D3D12_RECT scissors = dxPipeline->get_dx12_scissors();
		CommandList->RSSetScissorRects(1,&scissors);

		/*
		* Set primitive topology
		*/
		CommandList->IASetPrimitiveTopology(DX12PipelineUtils::get_dx12_primitives(dxPipeline->get_primitives()));
	}

	void DX12CommandBuffer::clear_color_impl(const ColorRgbaByte& color)
	{
		/*
		* Construct color
		*/
		const float clearColor[] = { color.Red,color.Green,color.Blue,color.Alpha };

		/*
		* Get dx12 framebuffer
		*/
		const DX12SwapchainFramebuffer* swapFramebuffer = (const DX12SwapchainFramebuffer*)CurrentFramebuffer;

		/*
		* Create cpu descriptor handle
		*/
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = swapFramebuffer->get_dx12_rtv_heap()->GetCPUDescriptorHandleForHeapStart();

		/*
		* Offset the handle
		*/
		rtvHandle.ptr += swapFramebuffer->get_dx12_swapchain_current_rtv_index() * RtvDescriptorSize;

		/*
		* Clear target view
		*/
		CommandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
	}

	void DX12CommandBuffer::clear_depth_impl(const float depth)
	{

	}

	void DX12CommandBuffer::set_resource_view_impl(const unsigned int slot, const ResourceView* view)
	{

	}

	void DX12CommandBuffer::indexed_draw_call_impl(const unsigned int count)
	{
		CommandList->DrawInstanced(3, 1, 0, 0);
	}
}