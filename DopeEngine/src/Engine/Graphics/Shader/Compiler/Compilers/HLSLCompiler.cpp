#include "HLSLCompiler.h"
#include <d3dcompiler.h>
#include <Engine/Graphics/API/Directx11/Shader/DX11ShaderUtils.h>

namespace DopeEngine
{
	ShaderCompilerType HLSLCompiler::get_type() const
	{
		return ShaderCompilerType::HLSL;
	}

	void HLSLCompiler::compile(const ShaderType stage,const String& source, const String& entryPoint, const unsigned int majorVersion, const unsigned int minorVersion, ShaderCompilationResult& result)
	{
		ID3DBlob* errorBlob = nullptr;
		ID3DBlob* shaderBlob = nullptr;

		/*
		* Try compile
		*/
		D3DCompile(*source,
			source.get_cursor(),
			nullptr, nullptr, nullptr,
			*entryPoint, *DX11ShaderUtils::get_shader_target_string(stage,majorVersion,minorVersion),
			D3DCOMPILE_ENABLE_STRICTNESS,
			0,
			&shaderBlob,
			&errorBlob);
	}
}