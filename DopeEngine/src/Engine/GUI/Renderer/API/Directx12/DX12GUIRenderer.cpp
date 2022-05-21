#include "DX12GUIRenderer.h"
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Command/DX12CommandBuffer.h>
#include <IMGUI/imgui_impl_dx12.h>

namespace DopeEngine
{
	DX12GUIRenderer::DX12GUIRenderer(const GUIRendererBackendFlags backendFlags, const GUIRendererConfigFlags configFlags,const GraphicsDevice* device) : GUIRenderer(backendFlags,configFlags)
	{
		/*
		* Get dx12 device
		*/
		const DX12GraphicsDevice* dx12Device = (const DX12GraphicsDevice*)device;

		/*
		* Init
		*/
		ImGui_ImplDX12_Init(dx12Device->get_dx12_device().Get(), 1, DXGI_FORMAT_420_OPAQUE, nullptr, {}, {}); // will be changed
	}

	GraphicsAPIType DX12GUIRenderer::get_api_type() const
	{
		return GraphicsAPIType::Directx12;
	}

	void DX12GUIRenderer::begin_rendering_impl()
	{
		ImGui_ImplDX12_NewFrame();
	}

	void DX12GUIRenderer::render_impl(GraphicsCommandBuffer* cmdBuffer)
	{
		/*
		* Get dx12 command buffer
		*/
		DX12CommandBuffer* dx12CmdBuffer = (DX12CommandBuffer*)cmdBuffer;

		/*
		* Render
		*/
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(),dx12CmdBuffer->get_dx12_command_list().Get());
	}

}