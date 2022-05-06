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
	ResourceType ResourceTypeUtils::get_resource_type(const DeviceObjectType type)
	{
		switch (type)
		{
			case DopeEngine::DeviceObjectType::Texture:
				break;
			case DopeEngine::DeviceObjectType::Buffer:
				break;
			case DopeEngine::DeviceObjectType::Shader:
				break;
			case DopeEngine::DeviceObjectType::Framebuffer:
				break;
			case DopeEngine::DeviceObjectType::ResourceLayout:
				break;
			case DopeEngine::DeviceObjectType::ResourceView:
				break;
			case DopeEngine::DeviceObjectType::CommandBuffer:
				break;
			case DopeEngine::DeviceObjectType::Pipeline:
				break;
			default:
				break;
		}
		return ResourceType::Texture;
	}
}