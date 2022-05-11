#include "ResourceView.h"

namespace DopeEngine
{
	ResourceView::ResourceView(const ResourceViewDescription& description) : GraphicsDeviceObject(GraphicsDeviceObjectType::ResourceView)
	{
		Resource = description.Resource;
	}

	GraphicsDeviceObject* ResourceView::get_resource() const
	{
		return Resource;
	}

}