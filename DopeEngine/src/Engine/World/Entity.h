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
		/// <summary>
		/// Returns a reference to the components list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Array<Component*>& get_components_fast() const;

		/// <summary>
		/// Returns a copy of the component list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Component*> get_components_slow() const;

		/// <summary>
		/// Returns the name of this entity
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String get_name() const;

		/// <summary>
		/// Returns the world which owns this entity
		/// </summary>
		/// <returns></returns>
		FORCEINLINE World* get_owner_world() const;

		/// <summary>
		/// Returns the spatial of this entity
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Spatial* get_spatial() const;

		/// <summary>
		/// Returns whether the target component exists or not
		/// </summary>
		/// <returns></returns>
		template<typename TComponent>
		FORCEINLINE bool has_component() const;

		/// <summary>
		/// Creates and adds anew component
		/// </summary>
		template<typename TComponent,typename ...TParameters>
		FORCEINLINE TComponent* create_component(TParameters... parameters);

		/// <summary>
		/// Removes the existing component,returns if the removal happened or not
		/// </summary>
		/// <returns></returns>
		template<typename TComponent>
		FORCEINLINE bool delete_component();

		/// <summary>
		/// Removes the existing component, returns if the removal happened or not
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		FORCEINLINE bool delete_component(Component* other);

		/// <summary>
		/// Destroys this entity
		/// </summary>
		void destroy();


	private:
		Entity(const String& name,World* ownerWorld);
		~Entity();

		FORCEINLINE void destory_component(Component* component);

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
	FORCEINLINE TComponent* Entity::create_component(TParameters ...parameters)
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