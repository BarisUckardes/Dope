#include "DX11CommandBuffer.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Device/DX11DeviceObjects.h>
#include <Engine/Graphics/Shader/ShaderSet.h>
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
		CurrentColorTargets.clear();
		CurrentDepthTarget = nullptr;
	}
	void DX11CommandBuffer::set_vertex_buffer_impl(const VertexBuffer& vertexBuffer)
	{
		/*
		* Get dx11 buffer
		*/
		const DX11VertexBuffer& dx11Buffer = (const DX11VertexBuffer&)vertexBuffer;

		/*
		* Set buffer
		*/
		DXPTR<ID3D11Buffer> dx11VertexBuffer = dx11Buffer.get_dx11_buffer();
		ID3D11Buffer* buffer = dx11VertexBuffer.Get();
		const unsigned int stride = dx11Buffer.get_per_vertex_size();
		const unsigned int offset = 0;
		Device->get_dx11_immediate_context()->IASetVertexBuffers(0, 1, &buffer,&stride, &offset);
	}
	void DX11CommandBuffer::set_index_buffer_impl(const IndexBuffer& indexBuffer)
	{
		/*
		* Get dx11 buffer
		*/
		const DX11IndexBuffer& dx11Buffer = (const DX11IndexBuffer&)indexBuffer;

		/*
		* Set buffer
		*/
		ID3D11Buffer* buffer = dx11Buffer.get_dx11_buffer().Get();
		Device->get_dx11_immediate_context()->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
	}
	void DX11CommandBuffer::set_uniform_buffer_impl(const UniformBuffer& buffer)
	{
		/*
		* Get dx11 buffer
		*/
		const DX11ConstantBuffer& dx11Buffer = (const DX11ConstantBuffer&)buffer;

	}
	void DX11CommandBuffer::set_framebuffer_impl(const Framebuffer& framebuffer)
	{
		/*
		* Validate if this is a swapchain buffer
		*/
		if (framebuffer.is_swapchain_framebuffer())
		{
			/*
			* Get dx11 swapchain framebuffer
			*/
			const DX11SwapchainFramebuffer& dx11SFarmebuffer = (const DX11SwapchainFramebuffer&)framebuffer;

			/*
			* Get render target
			*/
			DXPTR<ID3D11RenderTargetView> rtv = dx11SFarmebuffer.get_dx11_swapchain_rtv();

			/*
			* Set rtv
			*/
			Device->get_dx11_immediate_context()->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);

			CurrentColorTargets.add(rtv);
			CurrentDepthTarget = nullptr;
		}
		else
		{
			/*
			* Get dx11 framebuffer
			*/
			const DX11Framebuffer& dx11Framebuffer = (const DX11Framebuffer&)framebuffer;

			/*
			* Get render targets
			*/
			const Array<DXPTR<ID3D11RenderTargetView>> colorRenderTargets = dx11Framebuffer.get_dx11_rtvs_slow();
			DXPTR<ID3D11DepthStencilView> depthStencilTarget = dx11Framebuffer.get_dx11_depth_rtv();

			/*
			* Set targets
			*/
			//ASSERT(colorRenderTargets.get_cursor() > 0, "DX11CommandBuffer", "You have set a Dx11Framebuffer with no render target views!");
			//Device->get_dx11_immediate_context()->OMSetRenderTargets(colorRenderTargets.get_cursor(), colorRenderTargets.get_data(), depthStencilTarget);


			/*
			* Set currents
			*/
			CurrentColorTargets = colorRenderTargets;
			CurrentDepthTarget = depthStencilTarget;
		}


	}
	void DX11CommandBuffer::set_pipeline_impl(const Pipeline& pipeline)
	{
		/*
		* Get dx11 pipeline
		*/
		const DX11Pipeline* dx11Pipeline = (const DX11Pipeline*)&pipeline;

		/*
		* Set rasterizer state
		*/
		Device->get_dx11_immediate_context()->RSSetState(dx11Pipeline->get_dx11_rasterizer_state().Get());

		/*
		* Set depth-stencil state
		*/
		Device->get_dx11_immediate_context()->OMSetDepthStencilState(dx11Pipeline->get_dx11_depth_stencil_state().Get(), 0);

		/*
		* Set blending state
		*/
		//Device->get_dx11_immediate_context()->OMSetBlendState(dx11Pipeline->get_dx1_get_blend_state().Get(), nullptr, 0);

		/*
		* Set primitive topology
		*/
		Device->get_dx11_immediate_context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		/*
		* Set input assembler
		*/
		Device->get_dx11_immediate_context()->IASetInputLayout(dx11Pipeline->get_dx11_input_layout().Get());

		/*
		* Set viewports
		*/
		D3D11_VIEWPORT dx11Viewport = dx11Pipeline->get_dx11_viewport();
		Device->get_dx11_immediate_context()->RSSetViewports(1, &dx11Viewport);

		/*
		* Set shaders
		*/
		const Array<Shader*> shaders = pipeline.get_shader_set()->get_shaders_slow();
		for (unsigned int i = 0; i < shaders.get_cursor(); i++)
		{
			/*
			* Get shader
			*/
			const DX11Shader* shader = (const DX11Shader*)shaders[i];

			/*
			* Set shader
			*/
			const ShaderType type = shader->get_type();
			switch (type)
			{
				case DopeEngine::ShaderType::Vertex:
					Device->get_dx11_immediate_context()->VSSetShader(shader->get_dx11_vertex_shader().Get(), nullptr, 0);
					break;
				case DopeEngine::ShaderType::Fragment:
					Device->get_dx11_immediate_context()->PSSetShader(shader->get_dx11_fragment_shader().Get(), nullptr, 0);
					break;
				case DopeEngine::ShaderType::Geometry:
					break;
				case DopeEngine::ShaderType::TesellationEval:
					break;
				case DopeEngine::ShaderType::TesellationControl:
					break;
				case DopeEngine::ShaderType::Compute:
					break;
				default:
					break;
			}
		}

	}
	void DX11CommandBuffer::clear_color_impl(const ColorRgbaByte& color)
	{
		for (unsigned int i = 0; i < CurrentColorTargets.get_cursor(); i++)
		{
			/*
			* Get color target
			*/
			ID3D11RenderTargetView* rtv = CurrentColorTargets[i].Get();

			/*
			* Clear color
			*/
			const FLOAT dxColor[] = { color.Red,color.Green,color.Blue,color.Alpha };
			Device->get_dx11_immediate_context()->ClearRenderTargetView(rtv,dxColor);
		}
	}
	void DX11CommandBuffer::clear_depth_impl(const float depth)
	{
		Device->get_dx11_immediate_context()->ClearDepthStencilView(CurrentDepthTarget.Get(), 0, depth, 0);
	}
	void DX11CommandBuffer::set_resource_view_impl(const unsigned int slot, const ResourceView* view)
	{
		/*
		* Get slot resource layout
		*/
		const ResourceLayout* layout = get_bound_pipeline()->get_resource_layouts_fast()[slot];

		/*
		* Catch resource type
		*/
		const ResourceType resourceType = layout->get_description().Type;
		const ShaderType shaderStage = layout->get_description().ShaderStage;
		switch (resourceType)
		{
			case DopeEngine::ResourceType::UniformBuffer:
				set_constant_buffer((const Buffer*)view->get_resource(), shaderStage);
				break;
			case DopeEngine::ResourceType::Texture:
				set_shader_resource(view, shaderStage);
				break;
			default:
				break;
		}
		
	}
	void DX11CommandBuffer::indexed_draw_call_impl(const unsigned int count)
	{
		Device->get_dx11_immediate_context()->DrawIndexed(count, 0, 0);
	}
	
	void DX11CommandBuffer::set_constant_buffer(const Buffer* buffer, ShaderType stage)
	{
		switch (stage)
		{
			case DopeEngine::ShaderType::Vertex:
				Device->get_dx11_immediate_context()->VSSetConstantBuffers(0, 1, ((const DX11ConstantBuffer*)buffer)->get_dx11_buffer().GetAddressOf());
				break;
			case DopeEngine::ShaderType::Fragment:
				Device->get_dx11_immediate_context()->PSSetConstantBuffers(0, 1, ((const DX11ConstantBuffer*)buffer)->get_dx11_buffer().GetAddressOf());
				break;
			case DopeEngine::ShaderType::Geometry:
				Device->get_dx11_immediate_context()->GSSetConstantBuffers(0, 1, ((const DX11ConstantBuffer*)buffer)->get_dx11_buffer().GetAddressOf());
				break;
			case DopeEngine::ShaderType::TesellationEval:
				break;
			case DopeEngine::ShaderType::TesellationControl:
				break;
			case DopeEngine::ShaderType::Compute:
				break;
			default:
				break;
		}
	}
	
	void DX11CommandBuffer::set_shader_resource(const ResourceView* view, const ShaderType stage)
	{
		switch (stage)
		{
			case DopeEngine::ShaderType::Vertex:
				Device->get_dx11_immediate_context()->VSSetShaderResources(0, 1, ((const DX11ResourceView*)view)->get_dx11_srv().GetAddressOf());
				break;
			case DopeEngine::ShaderType::Fragment:
				Device->get_dx11_immediate_context()->PSSetShaderResources(0, 1, ((const DX11ResourceView*)view)->get_dx11_srv().GetAddressOf());
				break;
			case DopeEngine::ShaderType::Geometry:
				Device->get_dx11_immediate_context()->GSSetShaderResources(0, 1, ((const DX11ResourceView*)view)->get_dx11_srv().GetAddressOf());
				break;
			case DopeEngine::ShaderType::TesellationEval:
				break;
			case DopeEngine::ShaderType::TesellationControl:
				break;
			case DopeEngine::ShaderType::Compute:
				break;
			default:
				break;
		}
		
	}
	
}