#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported vertex element data types
	/// </summary>
	enum class DOPE_ENGINE_API VertexElementDataType
	{
        Float = 0,
        Float2 = 1,
        Float3 = 2,
        Float4 = 3,
        Mat3 = 4,
        Mat4 = 5
	};
}