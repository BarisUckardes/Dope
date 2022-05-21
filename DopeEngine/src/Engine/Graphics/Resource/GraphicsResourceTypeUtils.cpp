#include "GraphicsResourceTypeUtils.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	GraphicsDeviceObjectType GraphicsResourceTypeUtils::get_device_object_type(const GraphicsResourceType type)
	{
		switch (type)
		{
			case GraphicsResourceType::UniformBuffer:
				return GraphicsDeviceObjectType::Buffer;
				break;
			case GraphicsResourceType::Texture:
				return GraphicsDeviceObjectType::Texture;
				break;
			default:
				ASSERT(false, "ResourceTypeUtils", "Invalid ResourceType input!");
				break;
		}

	}
	GraphicsResourceType GraphicsResourceTypeUtils::get_resource_type(const GraphicsDeviceObjectType type)
	{
		switch (type)
		{
			case GraphicsDeviceObjectType::Texture:
				break;
			case GraphicsDeviceObjectType::Buffer:
				break;
			case GraphicsDeviceObjectType::Shader:
				break;
			case GraphicsDeviceObjectType::Framebuffer:
				break;
			case GraphicsDeviceObjectType::ResourceLayout:
				break;
			case GraphicsDeviceObjectType::ResourceView:
				break;
			case GraphicsDeviceObjectType::GraphicsCommandBuffer:
				break;
			case GraphicsDeviceObjectType::RenderPass:
				break;
			default:
				break;
		}
		return GraphicsResourceType::Texture;
	}
}