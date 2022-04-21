#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported shader types
	/// </summary>
	enum class DOPE_ENGINE_API ShaderType
	{
		Vertex = 0,
		Fragment = 1,
		Geometry = 2,
		TesellationEval = 3,
		TesellationControl = 4,
		Compute = 5,
		Undefined = 6
	};
}