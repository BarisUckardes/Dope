#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/API/Vulkan/Device/VKQueueFamilyProperties.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	struct DOPE_ENGINE_API VKGraphicsDeviceFeaturesDesc
	{
		VKGraphicsDeviceFeaturesDesc() = default;
		~VKGraphicsDeviceFeaturesDesc() = default;

		Array<VKQueueFamilyProperties> QueueFamilies;
	};
}