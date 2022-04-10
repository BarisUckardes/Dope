#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Structures/Array.h>
#include <Engine/World/WorldResolver.h>
namespace DopeEngine
{
	class GameSession;
	class Entity;

	/// <summary>
	/// Represents a collection of entities
	/// </summary>
	class DOPE_ENGINE_API World
	{
		friend class GameSession;
	public:
		/// <summary>
		/// Returns a reference to the entity list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Array<Entity*>& get_entities_fast() const;

		/// <summary>
		/// Returns a copy to the entity list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Entity*> get_entities_slow() const;

		/// <summary>
		/// Returns a reference to the resolver list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<WorldResolver*>& get_resolvers_fast();

		/// <summary>
		/// Returns a copy to the resolver list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<WorldResolver*> get_resolvers_slow();

		/// <summary>
		/// Returns whether this world is current
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_current() const;

		/// <summary>
		/// Returns the owning game session of this world
		/// </summary>
		/// <returns></returns>
		FORCEINLINE GameSession* get_owner_session() const;

		/// <summary>
		/// Creates anew entity and returns it
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		FORCEINLINE Entity* create_entity(const String& name = "Default Entity Name");

		/// <summary>
		/// Deletes an existing entity
		/// </summary>
		FORCEINLINE void delete_entity(Entity* entity);

		/// <summary>
		/// Returns a resolver with the specified type
		/// </summary>
		/// <typeparam name="TResolver"></typeparam>
		/// <returns></returns>
		template<typename TResolver>
		FORCEINLINE TResolver* get_resolver() const;

		/// <summary>
		/// Registers anew resolver to the world
		/// </summary>
		/// <typeparam name="TResolver"></typeparam>
		template<typename TResolver,typename... TParameters>
		void register_resolver(TParameters... parameters);

		/// <summary>
		/// Attempts to remove a resolver by type, returns whether the removal was successfull or not
		/// </summary>
		/// <typeparam name="TResolver"></typeparam>
		/// <returns></returns>
		template<typename TResolver>
		bool remove_resolver();

		/// <summary>
		/// Runs the world routine
		/// </summary>
		void tick_world();

		/// <summary>
		/// Destroys this world
		/// </summary>
		void destroy();
	private:
		World(const String& name = "Default World Name", GameSession* ownerSession = nullptr);
		~World() = default;

		void _mark_current();
		void _unmark_current();
		void _on_destroy();
	private:
		Array<Entity*> Entities;
		Array<WorldResolver*> Resolvers;
		GameSession* OwnerSession;
		String Name;
		bool Current;
	};


	template<typename TResolver>
	FORCEINLINE TResolver* World::get_resolver() const
	{
		/*
		* Get resolver class name
		*/
		const String className = TResolver::get_resolver_class_name_static();

		/*
		* Iterate and find
		*/
		for (unsigned int i = 0; i < Resolvers.get_cursor(); i++)
		{
			/*
			* Get resolver
			*/
			WorldResolver* resolver = Resolvers[i];

			/*
			* Validate match
			*/
			if (className == resolver->get_resolver_class_name())
				return (TResolver*)resolver;
		}
		return nullptr;
	}

	template<typename TResolver,typename... TParameters>
	inline void World::register_resolver(TParameters... parameters)
	{
		/*
		* Create resolver
		*/
		TResolver* resolver = new TResolver(parameters...);

		/*
		* Set owner world
		*/
		resolver->_set_owner_world(this);

		/*
		* Initialize
		*/
		resolver->initialize();

		/*
		* Register it to the world resolvers list
		*/
		Resolvers.add(resolver);
	}

	template<typename TResolver>
	inline bool World::remove_resolver()
	{
		/*
		* Get resolver class name
		*/
		const String className = TResolver::get_resolver_class_name_static();

		/*
		* Iterate and find a match
		*/
		for (unsigned int i = 0; i < Resolvers.get_cursor(); i++)
		{
			/*
			* Get resolver
			*/
			WorldResolver* resolver = Resolvers[i];

			/*
			* Validate class names
			*/
			if (className == resolver->get_resolver_class_name())
			{
				/*
				* Finalize resolvers
				*/
				resolver->finalize();

				/*
				* Free heap memory
				*/
				delete resolver;

				/*
				* Remove it from the world resolvers list
				*/
				Resolvers.remove_index(i);
				i--;

				return true;
			}
		}

		return false;
	}

}