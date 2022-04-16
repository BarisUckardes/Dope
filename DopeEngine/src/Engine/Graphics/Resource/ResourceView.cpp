#include "ResourceView.h"

namespace DopeEngine
{
	ResourceView::ResourceView(const ResourceViewDescription& description) : DeviceObject(DeviceObjectType::ResourceView)
	{
		Resource = description.Resource;
	}

	DeviceObject* ResourceView::get_resource() const
	{
		return Resource;
	}

}