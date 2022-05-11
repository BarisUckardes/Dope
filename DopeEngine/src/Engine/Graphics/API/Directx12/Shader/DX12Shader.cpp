#include "DX12Shader.h"
#include <d3dcompiler.h>
#include <Engine/Graphics/API/Directx11/Shader/DX11ShaderUtils.h>
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	DX12Shader::DX12Shader(const ShaderDescription& desc, DX12GraphicsDevice* device) : Shader(desc)
	{
		/*
		* Compile
		*/
		_create_shader(desc,device);
	}

	DX12Shader::~DX12Shader()
	{

	}

	ID3DBlob* DX12Shader::get_dx12_shader_blob() const
	{
		return ShaderBlob;
	}

	void DX12Shader::compile()
	{

	}

	void DX12Shader::_create_shader(const ShaderDescription& desc, DX12GraphicsDevice* device)
	{
		/*
		* Compile shader
		*/
		HRESULT compileHR = D3DCompile(
			*desc.Source,desc.Source.get_cursor(),
			nullptr,nullptr,nullptr,
			"main",*DX11ShaderUtils::get_shader_target_string(get_type(),4,0),
			D3DCOMPILE_ENABLE_STRICTNESS,
			0,
			&ShaderBlob,&ErrorBlob);

		/*
		* Validate shader compilation
		*/
		ASSERT(SUCCEEDED(compileHR),"DX12Shader", "Shader compilation error with logs: %s", ErrorBlob->GetBufferPointer());
	}

}

