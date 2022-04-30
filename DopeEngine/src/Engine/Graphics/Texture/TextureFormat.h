#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported texture formats
	/// </summary>
	enum class DOPE_ENGINE_API TextureFormat
	{
		R8unorm = 0,
		RGB8f = 1,
		RGB16f = 2,
		RGB32f = 3,
		RGBA8f = 4,
		RGBA8unorm = 5,
		RGBA16f = 6,
		RGBA32F = 7
	};
}