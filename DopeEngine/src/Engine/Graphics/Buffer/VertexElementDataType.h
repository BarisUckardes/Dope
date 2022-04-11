#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported vertex element data types
	/// </summary>
	enum class DOPE_ENGINE_API VertexElementDataType
	{
        Byte = 5120,
        UnsignedByte = 5121,
        Short = 5122,
        UnsignedShort = 5123,
        Int = 5124,
        UnsignedInt = 5125,
        Float = 5126,
        Double = 5130,
        HalfFloat = 5131,
        Fixed = 5132,
	};
}