#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported renderable primitive types
	/// </summary>
	enum class DOPE_ENGINE_API PrimitiveTopology
	{
		Points = 0,
		Lines = 1,
		Triangles = 2,
		Patches = 3
	};
}