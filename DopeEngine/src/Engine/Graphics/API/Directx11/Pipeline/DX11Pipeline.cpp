#include "DX11Pipeline.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Vertex/DX11VertexUtils.h>
#include <Engine/Graphics/API/Directx11/Shader/DX11Shader.h>
#include <Engine/Graphics/API/Directx11/Pipeline/DX11PipelineUtils.h>
#include <Engine/Graphics/Shader/ShaderSet.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Graphics/Vertex/VertexUtils.h>
namespace DopeEngine
{
	DX11Pipeline::DX11Pipeline(const PipelineDescription& desc, DX11GraphicsDevice* device) : Pipeline(desc)
	{
		create(desc,device);
	}
	DX11Pipeline::~DX11Pipeline()
	{

	}
	DXPTR<ID3D11InputLayout> DX11Pipeline::get_dx11_input_layout() const
	{
		return InputLayout;
	}
	DXPTR<ID3D11RasterizerState> DX11Pipeline::get_dx11_rasterizer_state() const
	{
		return RasterizerState;
	}
	DXPTR<ID3D11DepthStencilState> DX11Pipeline::get_dx11_depth_stencil_state() const
	{
		return DepthStencilState;
	}
	DXPTR<ID3D11BlendState> DX11Pipeline::get_dx1_get_blend_state() const
	{
		return BlendState;
	}
	D3D11_VIEWPORT DX11Pipeline::get_dx11_viewport() const
	{
		return Viewport;
	}
	void DX11Pipeline::create(const PipelineDescription& desc, DX11GraphicsDevice* device)
	{
		/*
		* Create input layout
		*/
		const VertexLayoutDescription vertexLayoutDescription = desc.LayoutDescription;
		const Array<VertexElementDescription> vertexElements = vertexLayoutDescription.get_elements_slow();
		Array<D3D11_INPUT_ELEMENT_DESC> inputElements;
		unsigned int offset = 0;
		for (unsigned int i = 0; i < vertexElements.get_cursor(); i++)
		{
			
			/*
			* Get element desc
			*/
			const VertexElementDescription& elementDesc = vertexElements[i];

			/*
			* Create input element desc
			*/
			D3D11_INPUT_ELEMENT_DESC inputElementDesc = { *elementDesc.Name, i, DX11VertexUtils::get_format(elementDesc.DataType), 0, offset, D3D11_INPUT_PER_VERTEX_DATA, 0};
			
			/*
			* Register input element
			*/
			inputElements.add(inputElementDesc);

			/*
			* Increment offset
			*/
			offset += VertexUtils::get_data_type_size(elementDesc.DataType);
		}

		/*
		* Get vertex shader
		*/
		const DX11Shader* dx11Shader = (const DX11Shader*)desc.ShaderSet->get_shaders_fast()[0];
		const ID3D11VertexShader* vertexShader =  dx11Shader->get_dx11_vertex_shader().Get();
		ID3DBlob* vertexShaderBlob = dx11Shader->get_dx11_blob().Get();

		/*
		* Create input layout
		*/
		device->get_dx11_device()->CreateInputLayout(
			inputElements.get_data(),
			inputElements.get_cursor(),
			vertexShaderBlob->GetBufferPointer(),
			vertexShaderBlob->GetBufferSize()
			, &InputLayout);

		/*
		* Create rasterizer state
		*/
		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.DepthClipEnable = desc.DepthClip;
		rasterizerDesc.FrontCounterClockwise = desc.FrontFace == FrontFaceMode::CounterClockwise ? true : false;
		rasterizerDesc.ScissorEnable = desc.ScissorTest;
		rasterizerDesc.FillMode = DX11PipelineUtils::get_fill_mode(desc.FillMode);
		rasterizerDesc.CullMode = DX11PipelineUtils::get_cull_mode(desc.CullFace);
		rasterizerDesc.FrontCounterClockwise = desc.FrontFace == FrontFaceMode::CounterClockwise ? true : false;
		rasterizerDesc.DepthBias = 0;
		rasterizerDesc.DepthBiasClamp = 0;
		device->get_dx11_device()->CreateRasterizerState(&rasterizerDesc,&RasterizerState);

		/*
		* Create depth stencil state
		*/
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		depthStencilDesc.DepthEnable = desc.DepthTest;
		depthStencilDesc.DepthWriteMask = desc.DepthWrite == true ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
		depthStencilDesc.StencilEnable = false;
		depthStencilDesc.StencilReadMask = 0xFF;
		depthStencilDesc.StencilWriteMask = 0xFF;
		depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		device->get_dx11_device()->CreateDepthStencilState(&depthStencilDesc, &DepthStencilState);

		/*
		* Create blend state
		*/
		D3D11_BLEND_DESC blendDesc;
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget->BlendEnable = true;
		blendDesc.RenderTarget->BlendOp = D3D11_BLEND_OP_ADD;
		device->get_dx11_device()->CreateBlendState(&blendDesc, &BlendState);

		/*
		* Create viewport
		*/
		D3D11_VIEWPORT viewport = { 0 };
		viewport.Width = (unsigned int)desc.OutputDesc.Width;
		viewport.Height = (unsigned int)desc.OutputDesc.Height;
		viewport.MinDepth = 0;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = desc.OutputDesc.OffsetX;
		viewport.TopLeftY = desc.OutputDesc.OffsetY;
		Viewport = viewport;
	}
}