#include "ResourceTypeUtils.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	DeviceObjectType ResourceTypeUtils::get_device_object_type(const ResourceType type)
	{
		switch (type)
		{
			case DopeEngine::ResourceType::UniformBuffer:
				return DeviceObjectType::Buffer;
				break;
			case DopeEngine::ResourceType::Texture:
				return DeviceObjectType::Texture;
				break;
			default:
				ASSERT(false, "ResourceTypeUtils", "Invalid ResourceType input!");
				break;
		}

	}
}