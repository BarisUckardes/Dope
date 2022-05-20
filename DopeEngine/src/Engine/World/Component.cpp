#include "Component.h"
#include <Engine/World/Entity.h>
#include <Engine/World/World.h>
#include <Engine/World/Functions/IterativeLogicWorldFunction.h>

namespace DopeEngine
{
	Spatial* Component::get_spatial() const
	{
		return OwnerEntity->get_spatial();
	}
	Entity* Component::get_owner_entity() const
	{
		return OwnerEntity;
	}
	void Component::destroy()
	{
		OwnerEntity->delete_component(this);
	}
	void Component::initialize()
	{
		/*
		* Validate if this component should tick
		*/
		if (should_tick())
		{
			/*
			* Get resolver
			*/
			IterativeLogicWorldFunction* function = OwnerEntity->get_owner_world()->get_function<IterativeLogicWorldFunction>();

			/*
			* Validate and register
			*/
			if (function != nullptr)
				function->register_component(this);
		}
	}
	void Component::finalize()
	{
		/*
		* Validate if this component should tick
		*/
		if (should_tick())
		{
			/*
			* Get function
			*/
			IterativeLogicWorldFunction* function = OwnerEntity->get_owner_world()->get_function<IterativeLogicWorldFunction>();

			/*
			* Validate and register
			*/
			if (function != nullptr)
				function->remove_component(this);
		}
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