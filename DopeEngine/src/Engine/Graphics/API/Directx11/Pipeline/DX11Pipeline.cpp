#include "DX11Pipeline.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Vertex/DX11VertexUtils.h>
#include <Engine/Graphics/API/Directx11/Shader/DX11Shader.h>
#include <Engine/Graphics/Shader/ShaderSet.h>
namespace DopeEngine
{
	DX11Pipeline::DX11Pipeline(const PipelineDescription& desc, DX11GraphicsDevice* device) : Pipeline(desc)
	{
		create(desc,device);
	}
	DX11Pipeline::~DX11Pipeline()
	{

	}
	ID3D11InputLayout* DX11Pipeline::get_dx11_input_layout() const
	{
		return InputLayout;
	}
	ID3D11RasterizerState* DX11Pipeline::get_dx11_rasterizer_state() const
	{
		return RasterizerState;
	}
	ID3D11DepthStencilState* DX11Pipeline::get_dx11_depth_stencil_state() const
	{
		return DepthStencilState;
	}
	ID3D11BlendState* DX11Pipeline::get_dx1_get_blend_state() const
	{
		return BlendState;
	}
	void DX11Pipeline::create(const PipelineDescription& desc, DX11GraphicsDevice* device)
	{
		/*
		* Create input layout
		*/
		const VertexLayoutDescription vertexLayoutDescription = desc.LayoutDescription;
		const Array<VertexElementDescription> vertexElements = vertexLayoutDescription.get_elements_slow();
		Array<D3D11_INPUT_ELEMENT_DESC> inputElements;
		inputElements.reserve(vertexElements.get_cursor());
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
			D3D11_INPUT_ELEMENT_DESC inputElementDesc;
			inputElementDesc.SemanticName = *elementDesc.Name;
			inputElementDesc.Format = DX11VertexUtils::get_format(elementDesc.DataType);
			inputElementDesc.SemanticIndex = i;
			inputElementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			inputElementDesc.InstanceDataStepRate = 0;
			inputElementDesc.AlignedByteOffset = offset;
			offset += elementDesc.ElementSizeInBytes;
			
			/*
			* Register input element
			*/
			inputElements[i] = inputElementDesc;
		}
		
		/*
		* Get vertex shader
		*/
		const DX11Shader* dx11Shader = (const DX11Shader*)desc.ShaderSet->get_shaders_fast()[0];
		const ID3D11VertexShader* vertexShader =  dx11Shader->get_dx11_vertex_shader();
		ID3DBlob* vertexShaderBlob = dx11Shader->get_dx11_blob();

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
		rasterizerDesc.DepthClipEnable = desc.DepthClip;
		rasterizerDesc.FrontCounterClockwise = desc.FrontFace == FrontFaceMode::CounterClockwise ? true : false;
		rasterizerDesc.ScissorEnable = desc.ScissorTest;
		device->get_dx11_device()->CreateRasterizerState(&rasterizerDesc,&RasterizerState);

		/*
		* Create depth stencil state
		*/
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		depthStencilDesc.DepthEnable = desc.DepthTest;
		device->get_dx11_device()->CreateDepthStencilState(&depthStencilDesc, &DepthStencilState);

		/*
		* Create blend state
		*/
		D3D11_BLEND_DESC blendDesc;
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		device->get_dx11_device()->CreateBlendState(&blendDesc, &BlendState);
	}
}