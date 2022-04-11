#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported texture types
	/// </summary>
	enum class DOPE_ENGINE_API TextureType
	{
		Texture1D = 0,
		Texture2D = 1,
		Texture3D = 2,
		CubeTexture = 3
	};
}