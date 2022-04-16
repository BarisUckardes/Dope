#include "ResourceLayout.h"

namespace DopeEngine
{
	ResourceLayout::ResourceLayout(const ResourceDescription& description) : DeviceObject(DeviceObjectType::ResourceLayout)
	{
		Description = description;
	}

	ResourceDescription ResourceLayout::get_description() const
	{
		return Description;
	}
}