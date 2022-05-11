#include "ResourceTypeUtils.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	GraphicsDeviceObjectType ResourceTypeUtils::get_device_object_type(const ResourceType type)
	{
		switch (type)
		{
			case DopeEngine::ResourceType::UniformBuffer:
				return GraphicsDeviceObjectType::Buffer;
				break;
			case DopeEngine::ResourceType::Texture:
				return GraphicsDeviceObjectType::Texture;
				break;
			default:
				ASSERT(false, "ResourceTypeUtils", "Invalid ResourceType input!");
				break;
		}

	}
	ResourceType ResourceTypeUtils::get_resource_type(const GraphicsDeviceObjectType type)
	{
		switch (type)
		{
			case DopeEngine::GraphicsDeviceObjectType::Texture:
				break;
			case DopeEngine::GraphicsDeviceObjectType::Buffer:
				break;
			case DopeEngine::GraphicsDeviceObjectType::Shader:
				break;
			case DopeEngine::GraphicsDeviceObjectType::Framebuffer:
				break;
			case DopeEngine::GraphicsDeviceObjectType::ResourceLayout:
				break;
			case DopeEngine::GraphicsDeviceObjectType::ResourceView:
				break;
			case DopeEngine::GraphicsDeviceObjectType::CommandBuffer:
				break;
			case DopeEngine::GraphicsDeviceObjectType::RenderPass:
				break;
			default:
				break;
		}
		return ResourceType::Texture;
	}
}