#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Graphics/Shader/Compiler/ShaderCompilerType.h>
#include <Engine/Graphics/Shader/ShaderType.h>
namespace DopeEngine
{
	struct DOPE_ENGINE_API ShaderCompilationResult
	{
		ShaderCompilationResult() : CompiledBytes(Array<Byte>()),ErrorMessages("None"),CompilerType(ShaderCompilerType::Undefined),UserData(nullptr),ShaderStage(ShaderType::Undefined) {}
		~ShaderCompilationResult() = default;

		Array<Byte> CompiledBytes;
		String ErrorMessages;
		ShaderType ShaderStage;
		ShaderCompilerType CompilerType;
		void* UserData;
	};
}