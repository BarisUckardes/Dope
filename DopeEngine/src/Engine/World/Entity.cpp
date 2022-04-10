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
		/*
		* Try find index of the component
		*/
		const int index = Components.find_index(other);

		/*
		* Validate index and delete
		*/
		if (index != 0)
		{
			/*
			* Get component
			*/
			Component* component = Components[index];

			/*
			* Delete the component
			*/
			destory_component(component);

			/*
			* Remove it from the list
			*/
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
		/*
		* Initialize
		*/
		Name = name;
		OwnerWorld = ownerWorld;

		/*
		* Create default spatial
		*/
		create_default_spatial();
	}
	Entity::~Entity()
	{
		OwnerWorld = nullptr;
	}
	void Entity::destory_component(Component* component)
	{
		/*
		* Call finalize impl of the component
		*/
		component->finalize();

		/*
		* Free heap memory(???)
		*/
		delete component;
	}
	void Entity::create_default_spatial()
	{
		EntitySpatial = create_component<Spatial>();

	}
	void Entity::_on_destroy()
	{
		/*
		* Iterate and destroy components
		*/
		for (unsigned int i = 0; i < Components.get_cursor(); i++)
		{
			destory_component(Components[i]);
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