#pragma once

#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported(or will be) graphics api types
	/// </summary>
	enum class DOPE_ENGINE_API GraphicsAPIType
	{
		Undefined = 0,
		OpenGL = 1,
		Directx11 = 2,
		Directx12 = 3,
		Vulkan = 4
	};
}