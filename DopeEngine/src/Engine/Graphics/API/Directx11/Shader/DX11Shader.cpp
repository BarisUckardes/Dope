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
		Device = device;

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
		const String source = get_source();

		ID3DBlob* errorBlob = nullptr;
		D3DCompile(*source,
			source.get_cursor(),
			nullptr, nullptr, nullptr,
			"main",*DX11ShaderUtils::get_shader_target_string(get_type(),4,0), // will be changed
			D3DCOMPILE_ENABLE_STRICTNESS,
			0,
			&ShaderBlob,
			&errorBlob);
		ASSERT(ShaderBlob, "DX11Shader", "Shader compilation error with logs: %s",errorBlob->GetBufferPointer());

		const ShaderStage ShaderStage = get_type();
		switch (ShaderStage)
		{
			case DopeEngine::ShaderStage::Vertex:
				Device->get_dx11_device()->CreateVertexShader(
					ShaderBlob->GetBufferPointer(),
					ShaderBlob->GetBufferSize(),
					nullptr,
					&VertexShader);
				break;
			case DopeEngine::ShaderStage::Fragment:
				Device->get_dx11_device()->CreatePixelShader(ShaderBlob->GetBufferPointer(),
					ShaderBlob->GetBufferSize(),
					nullptr,
					&FragmentShader);
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
}