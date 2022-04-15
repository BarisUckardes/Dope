#include "DX11CommandBuffer.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Device/DX11DeviceObjects.h>
#include <Engine/Graphics/Shader/ShaderSet.h>
namespace DopeEngine
{
	DX11CommandBuffer::DX11CommandBuffer(DX11GraphicsDevice* device)
	{
		Device = device;
		CommandList = nullptr;
	}
	DX11CommandBuffer::~DX11CommandBuffer()
	{

	}
	ID3D11CommandList* DX11CommandBuffer::get_dx11_commandlist() const
	{
		return CommandList;
	}
	void DX11CommandBuffer::lock_impl()
	{
		Device->get_dx11_deferred_context()->FinishCommandList(0, &CommandList);
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
		ID3D11Buffer* buffer = dx11Buffer.get_dx11_buffer();
		Device->get_dx11_immediate_context()->IASetVertexBuffers(0, 1, &buffer, 0, 0);
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
		ID3D11Buffer* buffer = dx11Buffer.get_dx11_buffer();
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
		* Get dx11 framebuffer
		*/
		const DX11Framebuffer& dx11Framebuffer = (const DX11Framebuffer&)framebuffer;

		/*
		* Get render targets
		*/
		const Array<ID3D11RenderTargetView*> colorRenderTargets = dx11Framebuffer.get_dx11_rtvs_slow();
		ID3D11DepthStencilView* depthStencilTarget = dx11Framebuffer.get_dx11_depth_rtv();

		/*
		* Set targets
		*/
		Device->get_dx11_immediate_context()->OMSetRenderTargets(colorRenderTargets.get_cursor(), colorRenderTargets.get_data(), depthStencilTarget);

		/*
		* Set currents
		*/
		CurrentColorTargets = colorRenderTargets;
		CurrentDepthTarget = depthStencilTarget;
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
		Device->get_dx11_immediate_context()->RSSetState(dx11Pipeline->get_dx11_rasterizer_state());

		/*
		* Set depth-stencil state
		*/
		Device->get_dx11_immediate_context()->OMSetDepthStencilState(dx11Pipeline->get_dx11_depth_stencil_state(), 0);

		/*
		* Set blending state
		*/
		Device->get_dx11_immediate_context()->OMSetBlendState(dx11Pipeline->get_dx1_get_blend_state(), nullptr, 0);

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
					Device->get_dx11_immediate_context()->VSSetShader(shader->get_dx11_vertex_shader(), nullptr, 0);
					break;
				case DopeEngine::ShaderType::Fragment:
					Device->get_dx11_immediate_context()->PSSetShader(shader->get_dx11_fragment_shader(), nullptr, 0);
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
			ID3D11RenderTargetView* rtv = CurrentColorTargets[i];

			/*
			* Clear color
			*/
			Device->get_dx11_immediate_context()->ClearRenderTargetView(rtv, nullptr);
		}
	}
	void DX11CommandBuffer::clear_depth_impl(const float depth)
	{
		Device->get_dx11_immediate_context()->ClearDepthStencilView(CurrentDepthTarget, 0, depth, 0);
	}
	void DX11CommandBuffer::set_resource_view_impl(const unsigned int slot, const ResourceView* view)
	{

	}
	void DX11CommandBuffer::indexed_draw_call_impl(const unsigned int count)
	{
		Device->get_dx11_immediate_context()->DrawIndexed(count, 0, 0);
	}
	
}