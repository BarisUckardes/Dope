#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported texture usage types
	/// </summary>
	enum class DOPE_ENGINE_API TextureUsage
	{
		ReadOnly = 1 << 0,
		ReadWrite = 1 << 1,
		FramebufferAttachment = 1 << 2,
	};
}