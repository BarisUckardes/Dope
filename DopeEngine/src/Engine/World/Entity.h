#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Structures/Array.h>
#include <Engine/World/Component.h>
namespace DopeEngine
{
	class World;

	/// <summary>
	/// A single entity object which acts as a component container in a world
	/// </summary>
	class DOPE_ENGINE_API Entity
	{
		friend class World;
	public:
		/// <summary>
		/// Returns a reference to the components list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Component*>& get_components_fast();

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
		/// Returns whether the target component exists or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool has_component();

		/// <summary>
		/// Creates and adds anew component
		/// </summary>
		template<typename TComponent,typename ...TParameters>
		FORCEINLINE void create_component(TParameters... parameters);

		/// <summary>
		/// Removes the existing component,returns if the removal happened or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool delete_component();

		/// <summary>
		/// Destroys this entity
		/// </summary>
		void destroy();


	private:
		Entity(const String& name,World* ownerWorld);
		~Entity();
		void _on_destroy();
	private:
		Array<Component*> Components;
		World* OwnerWorld;
		String Name;
	};


	template<typename TComponent, typename ...TParameters>
	FORCEINLINE void Entity::create_component(TParameters ...parameters)
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
	}

}