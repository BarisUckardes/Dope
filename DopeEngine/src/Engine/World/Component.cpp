#include "Component.h"
#include <Engine/World/Entity.h>
#include <Engine/World/World.h>
#include <Engine/World/Resolvers/IterativeLogicResolver.h>

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
			IterativeLogicResolver* resolver = OwnerEntity->get_owner_world()->get_resolver<IterativeLogicResolver>();

			/*
			* Validate and register
			*/
			if (resolver != nullptr)
				resolver->register_component(this);
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
			* Get resolver
			*/
			IterativeLogicResolver* resolver = OwnerEntity->get_owner_world()->get_resolver<IterativeLogicResolver>();

			/*
			* Validate and register
			*/
			if (resolver != nullptr)
				resolver->remove_component(this);
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