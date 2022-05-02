#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	struct DOPE_ENGINE_API VKGraphicsDeviceFeaturesDesc
	{
		VKGraphicsDeviceFeaturesDesc() = default;
		~VKGraphicsDeviceFeaturesDesc() = default;

		Array<VkQueueFlags> Queues;
	};
}