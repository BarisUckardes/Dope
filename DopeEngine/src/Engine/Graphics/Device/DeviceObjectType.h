#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported device object types
	/// </summary>
	enum class DOPE_ENGINE_API DeviceObjectType
	{
		Texture = 0,
		Buffer = 1,
		Shader = 2,
		ShaderSet = 3,
		Framebuffer = 4,
		ResourceLayout = 5,
		ResourceView = 6,
		CommandBuffer = 7,
		Pipeline = 8
	};
}