#pragma once

#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	enum class DOPE_ENGINE_API GraphicsAPIType
	{
		Undefined = 0,
		OpenGL = 1,
		Directx11 = 2,
		Directx12 = 3,
		Vulkna = 4
	};
}