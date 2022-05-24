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
	Spatial* Entity::get_spatial() const
	{
		return EntitySpatial;
	}

	bool Entity::delete_component(Component* other)
	{
		const int index = Components.find_index(other);
		if (index != 0)
		{
			Component* component = Components[index];

			destory_component(component);

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

		create_default_spatial();
	}
	Entity::~Entity()
	{
		OwnerWorld = nullptr;
	}
	void Entity::destory_component(Component* component)
	{
		component->finalize();

		delete component;
	}
	void Entity::create_default_spatial()
	{
		EntitySpatial = create_component<Spatial>();
	}
	void Entity::_on_destroy()
	{
		for (unsigned int i = 0; i < Components.get_cursor(); i++)
		{
			destory_component(Components[i]);
		}

		Components.clear();

		OwnerWorld = nullptr;
	}
}