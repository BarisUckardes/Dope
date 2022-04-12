#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported depth comparision function
	/// </summary>
	enum class DOPE_ENGINE_API DepthComparisionKind
	{
		Never = 0,
		Less = 1,
		Equal = 2,
		LessEqual = 3,
		Greater = 4,
		NotEqual = 5,
		GreaterOrEqual = 6,
		Always = 7
	};
}