#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported render pass types
	/// </summary>
	enum class DOPE_ENGINE_API RenderPassType
	{
		Graphics = 0,
		Compute = 1
	};
}