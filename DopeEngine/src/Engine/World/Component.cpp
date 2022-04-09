#include "Component.h"

namespace DopeEngine
{
	String Component::get_component_class_name() const
	{
		return "Component";
	}
	Component::~Component()
	{
		OwnerEntity = nullptr;
	}
	void Component::_set_owner_entity(Entity* ownerEntity)
	{
		OwnerEntity = ownerEntity;
	}
}