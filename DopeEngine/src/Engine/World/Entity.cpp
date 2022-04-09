#include "Entity.h"
#include <Engine/World/World.h>
namespace DopeEngine
{
	Array<Component*>& Entity::get_components_fast()
	{
		return Components;
	}
	Array<Component*> Entity::get_components_slow() const
	{
		return Components;
	}
	String Entity::get_name() const
	{
		return Name;
	}
	World* Entity::get_owner_world() const
	{
		return OwnerWorld;
	}
	void Entity::destroy()
	{
		OwnerWorld->delete_entity(this);
	}
	Entity::Entity(const String& name,World* ownerWorld)
	{
		Name = name;
		OwnerWorld = ownerWorld;
	}
	Entity::~Entity()
	{
		OwnerWorld = nullptr;
	}
	void Entity::_on_destroy()
	{
		/*
		* Iterate and destroy components
		*/
		for (unsigned int i = 0; i < Components.get_cursor(); i++)
		{
			Components[i]->finalize();
		}

		/*
		* Clear the component list
		*/
		Components.clear();

		/*
		* Detach owner world
		*/
		OwnerWorld = nullptr;
	}
}