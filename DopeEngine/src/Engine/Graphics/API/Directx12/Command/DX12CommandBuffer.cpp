#include "DX12CommandBuffer.h"
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Device/DX12DeviceObjects.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Directx12/Helper/DX12Helper.h>
namespace DopeEngine
{
	DX12CommandBuffer::DX12CommandBuffer(DX12GraphicsDevice* device)
	{
		/*
		* Get allocator
		*/
		Allocator = device->get_dx12_command_allocator();

		/*
		* Create command list
		*/
		HRESULT createCommandListHR = device->get_dx12_device()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, Allocator.Get(), NULL, IID_PPV_ARGS(&CommandList));

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
	DXPTR<ID3D12GraphicsCommandList> DX12CommandBuffer::get_dx12_command_list() const
	{
		return CommandList;
	}
	void DX12CommandBuffer::unlock_impl()
	{
		CommandList->Close();
	}
	void DX12CommandBuffer::lock_impl()
	{
		CommandList->Reset(Allocator.Get(), nullptr);
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

		/*
		* Validate if there was a alread ybound framebuffer
		*/
	/*	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_renderTargets[m_frameIndex].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
		m_commandList->ResourceBarrier(1, &barrier);*/
		
		/*
		* Validate if this framebuffer is a swapchain framebuffer
		*/
		D3D12_RESOURCE_BARRIER barrier = {};
		if (framebuffer.is_swapchain_framebuffer())
		{
			/*
			* Get dx12 framebuffer
			*/
			const DX12SwapchainFramebuffer& swapFramebuffer = (const DX12SwapchainFramebuffer&)framebuffer;

			/*
			* Initialize barrier
			*/
			barrier.Transition.pResource = swapFramebuffer.get_dx12_current_rtv().Get();
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
			* Set targets
			*/
		/*	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = {};
			DX12Helper::offset_rtv_handle(0,1,rtvHandle);
			CommandList->OMSetRenderTargets(1, &rtvHandle, false, nullptr);*/
		}
		
	}
	void DX12CommandBuffer::set_pipeline_impl(const Pipeline& pipeline)
	{
		/*
		* Get dx12 pipeline
		*/
		const DX12Pipeline& dxPipeline = (const DX12Pipeline&)pipeline;

		/*
		* Set signature
		*/
		CommandList->SetGraphicsRootSignature(dxPipeline.get_dx12_root_signature().Get());

		/*
		* Set pso
		*/
		CommandList->SetPipelineState(dxPipeline.get_dx12_pso().Get());

		/*
		* Set viewport
		*/
		//CommandList->RSSetViewports(1,&dxPipeline.get_dx12_viewport());
	}
	void DX12CommandBuffer::clear_color_impl(const ColorRgbaByte& color)
	{
		const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };

		/*
		* Create cpu descriptor handle
		*/
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = {};

		/*
		* Offset the handle
		*/
		DX12Helper::offset_rtv_handle(0, 1, rtvHandle);

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

	}
}