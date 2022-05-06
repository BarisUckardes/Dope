#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported buffer types
	/// </summary>
	enum class DOPE_ENGINE_API BufferType
	{
		VertexBuffer = 0,
		IndexBuffer = 1,
		UniformBuffer = 2,
	};
}