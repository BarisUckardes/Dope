#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported texture usage types
	/// </summary>
	enum class DOPE_ENGINE_API TextureUsage : int
	{
		ReadOnly = 1 << 0,
		ReadWrite = 1 << 1,
		FramebufferAttachment = 1 << 2,
		DepthStencil = 1 << 3
	};

	static TextureUsage operator |(const TextureUsage a, const TextureUsage b)
	{
		return (TextureUsage)((int)a | (int)b);
	}
	static TextureUsage operator &(const TextureUsage a, const TextureUsage b)
	{
		return (TextureUsage)((int)a & (int)b);
	}
}