#include "DX12CommandBuffer.h"
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Device/DX12DeviceObjects.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Directx12/Helper/DX12Helper.h>
#include <Engine/Graphics/API/Directx12/RenderPass/DX12RenderPassUtils.h>
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
		//CommandList->SetResource
	}
	void DX12CommandBuffer::start_render_pass_impl(const RenderPass* renderPass)
	{
		/*
		* Get dx12 render pass
		*/
		const DX12RenderPass* dx12RenderPass = (const DX12RenderPass*)renderPass;

		/*
		* Set signature
		*/
		CommandList->SetGraphicsRootSignature(dx12RenderPass->get_dx12_root_signature().Get());

		/*
		* Set pso
		*/
		CommandList->SetPipelineState(dx12RenderPass->get_dx12_pso().Get());

		/*
		* Set primitive topology
		*/
		CommandList->IASetPrimitiveTopology(DX12RenderPassUtils::get_dx12_primitives(dx12RenderPass->get_primitives()));

		/*
		* Validate if this framebuffer is a swapchain framebuffer
		*/
		const Framebuffer* targetFramebuffer = renderPass->get_target_framebuffer();
		D3D12_RESOURCE_BARRIER barrier = {};
		if (targetFramebuffer->is_swapchain_framebuffer())
		{
			/*
			* Get dx12 framebuffer
			*/
			const DX12SwapchainFramebuffer* swapFramebuffer = (const DX12SwapchainFramebuffer*)targetFramebuffer;

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
		CurrentFramebuffer = targetFramebuffer;
	}

	void DX12CommandBuffer::set_viewport_desc_impl(const ViewportDesc& desc)
	{
		/*
		 * Create viewport
		 */
		D3D12_VIEWPORT viewport = {};
		viewport.Width = desc.Width;
		viewport.Height = desc.Height;
		viewport.TopLeftX = desc.OffsetX;
		viewport.TopLeftY = desc.OffsetY;
		viewport.MinDepth = desc.MinDepth;
		viewport.MaxDepth = desc.Height;

		/*
		* Set viewport as current
		*/
		CurrentDX12Viewport = viewport;

		/*
		* Set viewport
		*/
		CommandList->RSSetViewports(1, &CurrentDX12Viewport);
	}

	void DX12CommandBuffer::set_scissors_desc_impl(const ScissorsDesc& desc)
	{
		/*
		* Create scissors
		*/
		D3D12_RECT scissorsRect = {};
		scissorsRect.left = desc.OffsetX;
		scissorsRect.right = desc.Width;
		scissorsRect.bottom = desc.Height;
		scissorsRect.top = desc.OffsetY;

		/*
		* Set scissors as current
		*/
		CurrentDX12Scissors = scissorsRect;

		/*
		* Set scissors
		*/
		CommandList->RSSetScissorRects(1, &CurrentDX12Scissors);
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

	void DX12CommandBuffer::commit_resource_impl(const unsigned int slot, const GraphicsResource* resource)
	{

	}

	void DX12CommandBuffer::indexed_draw_call_impl(const unsigned int count)
	{
		CommandList->DrawInstanced(3, 1, 0, 0);
	}
}