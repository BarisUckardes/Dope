#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported audio api types
	/// </summary>
	enum class AudioAPIType
	{
		Undefined = 0,
		OpenAL = 1,
		X2Audio = 2
	};
}