#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported face cull modes
	/// </summary>
	enum class DOPE_ENGINE_API FaceCullMode
	{
		Front = 0,
		Back = 1,
		FrontAndBack = 2
	};
}