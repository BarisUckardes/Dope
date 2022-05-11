#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported shader compiler types
	/// </summary>
	enum class DOPE_ENGINE_API ShaderCompilerType
	{
		Undefined = 0,
		GLSL = 1,
		HLSL = 2,
		SPIRV = 3
	};
}