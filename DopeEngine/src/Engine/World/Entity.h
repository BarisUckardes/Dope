#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Structures/Array.h>
#include <Engine/World/Components/Spatial.h>
namespace DopeEngine
{
	class World;
	/// <summary>
	/// A single entity object which acts as a component container in a world
	/// </summary>
	class DOPE_ENGINE_API Entity final
	{
		friend class World;
	public:
		const Array<Component*>& get_components_fast() const;
		Array<Component*> get_components_slow() const;
		String get_name() const;
		World* get_owner_world() const;
		Spatial* get_spatial() const;


		template<typename TComponent>
		bool has_component() const;
		template<typename TComponent,typename ...TParameters>
		TComponent* create_component(TParameters... parameters);
		template<typename TComponent>
		bool delete_component();

		bool delete_component(Component* other);
		void destroy();
	private:
		Entity(const String& name,World* ownerWorld);
		~Entity();

		 void destory_component(Component* component);

		void create_default_spatial();
		void _on_destroy();
	private:
		Array<Component*> Components;
		World* OwnerWorld;
		Spatial* EntitySpatial;
		String Name;
	};


	template<typename TComponent>
	inline bool Entity::has_component() const
	{
		/*
		* Get component class name
		*/
		const String className = TComponent::get_component_class_name_static();

		/*
		* Iterate and look for a match
		*/
		for (unsigned int i = 0; i < Components.get_cursor(); i++)
		{
			if (className == Components[i]->get_component_class_name())
				return true;
		}
		return false;
	}

	template<typename TComponent, typename ...TParameters>
	 TComponent* Entity::create_component(TParameters ...parameters)
	{
		/*
		* Create component
		*/
		TComponent* component = new TComponent(parameters...);

		/*
		* Set owner entity
		*/
		component->_set_owner_entity(this);

		/*
		* Register component
		*/
		Components.add(component);

		/*
		* Call initialize implementation
		*/
		component->initialize();

		return component;
	}

	template<typename TComponent>
	inline bool Entity::delete_component()
	{
		/*
		* Get component class name
		*/
		const String className = TComponent::get_component_class_name_static();

		/*
		* Iterate and find a match
		*/
		for (unsigned int i = 0; i < Components.get_cursor(); i++)
		{
			/*
			* Get component
			*/
			Component* component = Components[i];

			/*
			* Validate a match
			*/
			if (className == component->get_component_class_name())
			{
				destory_component(component);
				Components.remove_index(i);
				i--;
				return true;
			}
		}
		return false;
	}

}