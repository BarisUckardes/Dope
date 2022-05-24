#include "DX11CommandBuffer.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Device/DX11DeviceObjects.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Math/Vector2f.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	DX11CommandBuffer::DX11CommandBuffer(DX11GraphicsDevice* device)
	{
		Device = device;
	}
	DX11CommandBuffer::~DX11CommandBuffer()
	{

	}

	void DX11CommandBuffer::lock_impl()
	{

	}
	
	void DX11CommandBuffer::unlock_impl()
	{

	}
	void DX11CommandBuffer::clear_cached_state_impl()
	{
		CurrentDepthTarget = nullptr;
	}
	void DX11CommandBuffer::set_vertex_buffer_impl(const VertexBuffer* vertexBuffer)
	{
		const DX11VertexBuffer* dx11Buffer = (const DX11VertexBuffer*)vertexBuffer;

		DXPTR<ID3D11Buffer> dx11VertexBuffer = dx11Buffer->get_dx11_buffer();
		ID3D11Buffer* buffer = dx11VertexBuffer.Get();

		const unsigned int stride = dx11Buffer->get_per_vertex_size();
		const unsigned int offset = 0;

		Device->get_dx11_immediate_context()->IASetVertexBuffers(0, 1, &buffer,&stride, &offset);
	}
	void DX11CommandBuffer::set_index_buffer_impl(const IndexBuffer* indexBuffer)
	{
		const DX11IndexBuffer* dx11Buffer = (const DX11IndexBuffer*)indexBuffer;
		Device->get_dx11_immediate_context()->IASetIndexBuffer(dx11Buffer->get_dx11_buffer().Get(), DXGI_FORMAT_R32_UINT, 0);
	}
	void DX11CommandBuffer::set_uniform_buffer_impl(const UniformBuffer* buffer)
	{
		const DX11ConstantBuffer* dx11Buffer = (const DX11ConstantBuffer*)buffer;
	}
	void DX11CommandBuffer::set_render_pass_impl(const RenderPass* renderPass)
	{
		const DX11RenderPass* dx11RenderPass = (const DX11RenderPass*)renderPass;

		Device->get_dx11_immediate_context()->RSSetState(dx11RenderPass->get_dx11_rasterizer_state().Get());

		Device->get_dx11_immediate_context()->OMSetDepthStencilState(dx11RenderPass->get_dx11_depth_stencil_state().Get(), 0);
	
		//Device->get_dx11_immediate_context()->OMSetBlendState(dx11Pipeline->get_dx1_get_blend_state().Get(), nullptr, 0);

		Device->get_dx11_immediate_context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Device->get_dx11_immediate_context()->IASetInputLayout(dx11RenderPass->get_dx11_input_layout().Get());

		const Array<Shader*> shaders = dx11RenderPass->get_shader_set();
		for (unsigned int i = 0; i < shaders.get_cursor(); i++)
		{

			const DX11Shader* shader = (const DX11Shader*)shaders[i];
			const ShaderStage type = shader->get_type();
			switch (type)
			{
				case DopeEngine::ShaderStage::Vertex:
					Device->get_dx11_immediate_context()->VSSetShader(shader->get_dx11_vertex_shader().Get(), nullptr, 0);
					break;
				case DopeEngine::ShaderStage::Fragment:
					Device->get_dx11_immediate_context()->PSSetShader(shader->get_dx11_fragment_shader().Get(), nullptr, 0);
					break;
				case DopeEngine::ShaderStage::Geometry:
					break;
				case DopeEngine::ShaderStage::TesellationEval:
					break;
				case DopeEngine::ShaderStage::TesellationControl:
					break;
				case DopeEngine::ShaderStage::Compute:
					break;
				default:
					break;
			}
		}

		const Framebuffer* targetFramebuffer = dx11RenderPass->get_target_framebuffer();
		if (targetFramebuffer->is_swapchain_framebuffer())
		{
			const DX11SwapchainFramebuffer* dx11SFarmebuffer = (const DX11SwapchainFramebuffer*)targetFramebuffer;

			DXPTR<ID3D11RenderTargetView> rtv = dx11SFarmebuffer->get_dx11_swapchain_rtv();
			Device->get_dx11_immediate_context()->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);

			//CurrentColorTargets.add(rtv);
			CurrentDepthTarget = nullptr;
		}
		else
		{
			const DX11Framebuffer* dx11Framebuffer = (const DX11Framebuffer*)targetFramebuffer;

			const Array<DXPTR<ID3D11RenderTargetView>> colorRenderTargets = dx11Framebuffer->get_dx11_rtvs_slow();
			DXPTR<ID3D11DepthStencilView> depthStencilTarget = dx11Framebuffer->get_dx11_depth_rtv();

			//ASSERT(colorRenderTargets.get_cursor() > 0, "DX11CommandBuffer", "You have set a Dx11Framebuffer with no render target views!");
			//Device->get_dx11_immediate_context()->OMSetRenderTargets(colorRenderTargets.get_cursor(), colorRenderTargets.get_data(), depthStencilTarget);

			CurrentDepthTarget = depthStencilTarget;
		}
	}
	void DX11CommandBuffer::set_viewport_desc_impl(const ViewportDesc& desc)
	{
		D3D11_VIEWPORT viewport = { 0 };
		viewport.Width = desc.Width;
		viewport.Height = desc.Height;
		viewport.MinDepth = desc.MinDepth;
		viewport.MaxDepth = desc.MaxDepth;
		viewport.TopLeftX = desc.OffsetX;
		viewport.TopLeftY = desc.OffsetY;
		CurrentDX11Viewport = viewport;

		Device->get_dx11_immediate_context()->RSSetViewports(1, &CurrentDX11Viewport);
	}
	void DX11CommandBuffer::set_scissors_desc_impl(const ScissorsDesc& desc)
	{

	}
	void DX11CommandBuffer::clear_color_impl(const ColorRgbaByte& color)
	{
		const Framebuffer* framebuffer = get_bound_render_pass()->get_target_framebuffer();
		if (framebuffer->is_swapchain_framebuffer() == true)
		{
			const DX11SwapchainFramebuffer* dx11SwapchainFramebuffer = (const DX11SwapchainFramebuffer*)framebuffer;

			const FLOAT dxColor[] = { (Byte)color.Red,(Byte)color.Green,(Byte)color.Blue,(Byte)color.Alpha };
			Device->get_dx11_immediate_context()->ClearRenderTargetView(dx11SwapchainFramebuffer->get_dx11_swapchain_rtv().Get(), dxColor);
		}
		else
		{
			const DX11Framebuffer* dx11Framebuffer = (const DX11Framebuffer*)framebuffer;
		}
		
	}
	void DX11CommandBuffer::clear_depth_impl(const float depth)
	{
		Device->get_dx11_immediate_context()->ClearDepthStencilView(CurrentDepthTarget.Get(), 0, depth, 0);
	}
	void DX11CommandBuffer::commit_resource_impl(const unsigned int slot, const GraphicsResource* resource)
	{
		const GraphicsResourceSlotDesc resourceSlotDesc = get_bound_render_pass()->get_resource_slots()[slot];
		const GraphicsResourceType resourceType = resourceSlotDesc.Type;
		const ShaderStage shaderStage = resourceSlotDesc.ShaderStage;
		switch (resourceType)
		{
			case GraphicsResourceType::UniformBuffer:
				set_constant_buffer((const GraphicsBuffer*)resource->get_resource(), shaderStage);
				break;
			case GraphicsResourceType::Texture:
				set_shader_resource(resource, shaderStage);
				break;
			default:
				break;
		}
		
	}
	void DX11CommandBuffer::indexed_draw_call_impl(const unsigned int count)
	{
		Device->get_dx11_immediate_context()->DrawIndexed(count, 0, 0);
	}
	
	void DX11CommandBuffer::set_constant_buffer(const GraphicsBuffer* buffer, ShaderStage stage)
	{
		switch (stage)
		{
			case DopeEngine::ShaderStage::Vertex:
				Device->get_dx11_immediate_context()->VSSetConstantBuffers(0, 1, ((const DX11ConstantBuffer*)buffer)->get_dx11_buffer().GetAddressOf());
				break;
			case DopeEngine::ShaderStage::Fragment:
				Device->get_dx11_immediate_context()->PSSetConstantBuffers(0, 1, ((const DX11ConstantBuffer*)buffer)->get_dx11_buffer().GetAddressOf());
				break;
			case DopeEngine::ShaderStage::Geometry:
				Device->get_dx11_immediate_context()->GSSetConstantBuffers(0, 1, ((const DX11ConstantBuffer*)buffer)->get_dx11_buffer().GetAddressOf());
				break;
			case DopeEngine::ShaderStage::TesellationEval:
				break;
			case DopeEngine::ShaderStage::TesellationControl:
				break;
			case DopeEngine::ShaderStage::Compute:
				break;
			default:
				break;
		}
	}
	
	void DX11CommandBuffer::set_shader_resource(const GraphicsResource* resource, const ShaderStage stage)
	{
		switch (stage)
		{
			case DopeEngine::ShaderStage::Vertex:
				Device->get_dx11_immediate_context()->VSSetShaderResources(0, 1, ((const DX11ResourceView*)resource)->get_dx11_srv().GetAddressOf());
				break;
			case DopeEngine::ShaderStage::Fragment:
				Device->get_dx11_immediate_context()->PSSetShaderResources(0, 1, ((const DX11ResourceView*)resource)->get_dx11_srv().GetAddressOf());
				break;
			case DopeEngine::ShaderStage::Geometry:
				Device->get_dx11_immediate_context()->GSSetShaderResources(0, 1, ((const DX11ResourceView*)resource)->get_dx11_srv().GetAddressOf());
				break;
			case DopeEngine::ShaderStage::TesellationEval:
				break;
			case DopeEngine::ShaderStage::TesellationControl:
				break;
			case DopeEngine::ShaderStage::Compute:
				break;
			default:
				break;
		}
		
	}
	
}