#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported asset types
	/// </summary>
	enum class DOPE_ENGINE_API AssetType
	{
		Undefined = 0,
		Prefab = 1,
		World = 2,
		Texture1D = 3,
		Texture2D = 4,
		Texture3D = 5,
		CubeTexture = 6,
		Material = 7,
		Shader = 8,
		ShaderProgram = 9,
		Mesh = 10,
		Framebuffer = 11
	};
}