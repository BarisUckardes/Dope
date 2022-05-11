#include "DX11Shader.h"
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Shader/DX11ShaderUtils.h>
#include <d3dcompiler.h>
#include <Engine/Core/Assert.h>
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
	
	DXPTR<ID3D11VertexShader> DX11Shader::get_dx11_vertex_shader() const
	{
		return VertexShader;
	}

	DXPTR<ID3D11PixelShader> DX11Shader::get_dx11_fragment_shader() const
	{
		return FragmentShader;
	}

	DXPTR<ID3DBlob> DX11Shader::get_dx11_blob() const
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
		ID3DBlob* errorBlob = nullptr;
		D3DCompile(*source,
			source.get_cursor(),
			nullptr, nullptr, nullptr,
			"main",*DX11ShaderUtils::get_shader_target_string(get_type(),4,0), // will be changed
			D3DCOMPILE_ENABLE_STRICTNESS,
			0,
			&ShaderBlob,
			&errorBlob);

		/*
		* Validate shader
		*/
		ASSERT(ShaderBlob, "DX11Shader", "Shader compilation error with logs: %s",errorBlob->GetBufferPointer());

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