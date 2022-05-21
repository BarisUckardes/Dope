#include "GraphicsResource.h"

namespace DopeEngine
{
	GraphicsResource::GraphicsResource(const GraphicsResourceDesc& description) : GraphicsDeviceObject(GraphicsDeviceObjectType::ResourceView)
	{
		Resource = description.Resource;
	}

	GraphicsDeviceObject* GraphicsResource::get_resource() const
	{
		return Resource;
	}

}