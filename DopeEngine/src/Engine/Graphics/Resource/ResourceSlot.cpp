#include "ResourceLayout.h"

namespace DopeEngine
{
	ResourceLayout::ResourceLayout(const ResourceDescription& description) : DeviceObject(DeviceObjectType::ResourceLayout)
	{
		Description = description;
	}

	const ResourceDescription& ResourceLayout::get_description() const
	{
		return Description;
	}
}