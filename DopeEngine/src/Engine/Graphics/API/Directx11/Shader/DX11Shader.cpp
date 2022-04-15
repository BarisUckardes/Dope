#include "DX11Shader.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

namespace DopeEngine
{
	DX11Shader::DX11Shader(const ShaderDescription& description, DX11GraphicsDevice* device) : Shader(description)
	{
		/*
		* Initialize
		*/
		Device = device;

		/*
		* Compile
		*/
		compile();
	}
	DX11Shader::~DX11Shader()
	{

	}
	
	ID3D11VertexShader* DX11Shader::get_dx11_vertex_shader() const
	{
		return VertexShader;
	}

	ID3D11PixelShader* DX11Shader::get_dx11_fragment_shader() const
	{
		return FragmentShader;
	}

	ID3DBlob* DX11Shader::get_dx11_blob() const
	{
		return ShaderBlob;
	}
	void DX11Shader::compile()
	{
		/*
		* Get source
		*/
		const String source = get_source();

		/*
		* Create and compile shader blob
		*/
		D3DCompile(*source,
			source.get_cursor(),
			nullptr, nullptr, nullptr,
			"main", "ps_4_0",
			D3DCOMPILE_ENABLE_STRICTNESS,
			0,
			&ShaderBlob,
			nullptr);

		/*
		* Create shader
		*/
		const ShaderType shaderType = get_type();
		switch (shaderType)
		{
			case DopeEngine::ShaderType::Vertex:
				Device->get_dx11_device()->CreateVertexShader(
					ShaderBlob->GetBufferPointer(),
					ShaderBlob->GetBufferSize(),
					nullptr,
					&VertexShader);
				break;
			case DopeEngine::ShaderType::Fragment:
				Device->get_dx11_device()->CreatePixelShader(ShaderBlob->GetBufferPointer(),
					ShaderBlob->GetBufferSize(),
					nullptr,
					&FragmentShader);
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