#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Supported device object types
	/// </summary>
	enum class DOPE_ENGINE_API GraphicsDeviceObjectType
	{
		Texture = 0,
		Buffer = 1,
		Shader = 2,
		Framebuffer = 3,
		ResourceLayout = 4,
		ResourceView = 5,
		CommandBuffer = 6,
		RenderPass = 7
	};
}