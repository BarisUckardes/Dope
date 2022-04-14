#include "ResourceLayout.h"

namespace DopeEngine
{
	ResourceLayout::ResourceLayout(const ResourceLayoutDescription& description) : DeviceObject(DeviceObjectType::ResourceLayout)
	{
		Description = description;
	}

	ResourceLayoutDescription ResourceLayout::get_description() const
	{
		return Description;
	}
}