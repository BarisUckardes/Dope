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
		Allocator = device->get_dx12_command_allocator();
		RtvDescriptorSize = device->get_dx12_device()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
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
		if (CurrentFramebuffer != nullptr)
		{
			if (CurrentFramebuffer->is_swapchain_framebuffer())
			{
				D3D12_RESOURCE_BARRIER barrier = {};
				barrier.Transition.pResource = ((const DX12SwapchainFramebuffer*)CurrentFramebuffer)->get_dx12_current_rtv().Get();
				barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
				barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
				barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
				barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
				barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
				CommandList->ResourceBarrier(1, &barrier);
			}
		}
		
		CommandList->Close();
	}
	void DX12CommandBuffer::lock_impl()
	{
		HRESULT resetCmdListHR = CommandList->Reset(Allocator.Get(), nullptr);
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
		const DX12RenderPass* dx12RenderPass = (const DX12RenderPass*)renderPass;

		CommandList->SetGraphicsRootSignature(dx12RenderPass->get_dx12_root_signature().Get());

		CommandList->SetPipelineState(dx12RenderPass->get_dx12_pso().Get());

		CommandList->IASetPrimitiveTopology(DX12RenderPassUtils::get_dx12_primitives(dx12RenderPass->get_primitives()));

		const Framebuffer* targetFramebuffer = renderPass->get_target_framebuffer();
		D3D12_RESOURCE_BARRIER barrier = {};
		if (targetFramebuffer->is_swapchain_framebuffer())
		{
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
			CommandList->ResourceBarrier(1, &barrier);

			D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = swapFramebuffer->get_dx12_rtv_heap()->GetCPUDescriptorHandleForHeapStart();
			rtvHandle.ptr += swapFramebuffer->get_dx12_swapchain_current_rtv_index() * RtvDescriptorSize;

			CommandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);
		}

		CurrentFramebuffer = targetFramebuffer;
	}

	void DX12CommandBuffer::set_viewport_desc_impl(const ViewportDesc& desc)
	{
		D3D12_VIEWPORT viewport = {};
		viewport.Width = desc.Width;
		viewport.Height = desc.Height;
		viewport.TopLeftX = desc.OffsetX;
		viewport.TopLeftY = desc.OffsetY;
		viewport.MinDepth = desc.MinDepth;
		viewport.MaxDepth = desc.Height;
		CurrentDX12Viewport = viewport;

		CommandList->RSSetViewports(1, &CurrentDX12Viewport);
	}

	void DX12CommandBuffer::set_scissors_desc_impl(const ScissorsDesc& desc)
	{
		D3D12_RECT scissorsRect = {};
		scissorsRect.left = desc.OffsetX;
		scissorsRect.right = desc.Width;
		scissorsRect.bottom = desc.Height;
		scissorsRect.top = desc.OffsetY;
		CurrentDX12Scissors = scissorsRect;

		CommandList->RSSetScissorRects(1, &CurrentDX12Scissors);
	}

	void DX12CommandBuffer::clear_color_impl(const ColorRgbaByte& color)
	{
		const float clearColor[] = { color.Red,color.Green,color.Blue,color.Alpha };

		const DX12SwapchainFramebuffer* swapFramebuffer = (const DX12SwapchainFramebuffer*)CurrentFramebuffer;

		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = swapFramebuffer->get_dx12_rtv_heap()->GetCPUDescriptorHandleForHeapStart();
		rtvHandle.ptr += swapFramebuffer->get_dx12_swapchain_current_rtv_index() * RtvDescriptorSize;

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