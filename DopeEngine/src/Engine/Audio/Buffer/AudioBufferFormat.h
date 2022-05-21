#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported audio buffer formats
	/// </summary>
	enum class DOPE_ENGINE_API AudioBufferFormat
	{
		Undefined = 0,
		Mono8Bit = 1,
		Mono16Bit = 2,
		Stereo8Bit = 3,
		Stereo16Bit = 4

	};
}