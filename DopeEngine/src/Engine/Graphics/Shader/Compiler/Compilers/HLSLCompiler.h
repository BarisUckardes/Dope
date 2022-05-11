#pragma once
#include <Engine/Graphics/Shader/Compiler/IShaderCompiler.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API HLSLCompiler : public IShaderCompiler
	{
	public:
		HLSLCompiler() = default;
		~HLSLCompiler() = default;



		// Inherited via IShaderCompiler
		virtual ShaderCompilerType get_type() const override;
		virtual void compile(const ShaderType stage,const String& source, const String& entryPoint, const unsigned int majorVersion, const unsigned int minorVersion, ShaderCompilationResult& result) override;

	};


}