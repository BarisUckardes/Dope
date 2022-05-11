#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Graphics/Shader/Compiler/ShaderCompilationResult.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API IShaderCompiler
	{
	public:
		virtual ShaderCompilerType get_type() const = 0;
		virtual void compile(const ShaderType stage,const String& source,const String& entryPoint,const unsigned int majorVersion,const unsigned int minorVersion, ShaderCompilationResult& result) = 0;
	protected:
		IShaderCompiler() = default;
		~IShaderCompiler() = default;
	};


}