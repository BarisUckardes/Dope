#include "Entity.h"
#include <Engine/World/World.h>
namespace DopeEngine
{
    const Array<Component*>& Entity::get_components_fast() const 
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

	bool Entity::delete_component(Component* other)
	{
		const int index = Components.find_index(other);
		if (index != 0)
		{
			Component* component = Components[index];

			destroy_component(component);

			Components.remove_index(index);

			return true;
		}
		return false;
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
	void Entity::destroy_component(Component* component)
	{
		component->finalize();

		delete component;
	}

	void Entity::_on_destroy()
	{
		for (unsigned int i = 0; i < Components.get_cursor(); i++)
		{
			destroy_component(Components[i]);
		}

		Components.clear();

		OwnerWorld = nullptr;
	}
}