#include "ResourceView.h"

namespace DopeEngine
{
	ResourceView::ResourceView(const ResourceViewDescription& description) : DeviceObject(DeviceObjectType::ResourceView)
	{
		ResourceCount = description.Resources.get_cursor();
		Resources = description.Resources;
	}

	const Array<DeviceObject*>& ResourceView::get_resources_fast() const
	{
		return Resources;
	}
	Array<DeviceObject*> ResourceView::get_resources_slow() const
	{
		return Resources;
	}

	unsigned int ResourceView::get_resource_count() const
	{
		return ResourceCount;
	}

}