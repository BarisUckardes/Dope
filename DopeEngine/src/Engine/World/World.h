#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Structures/Array.h>
#include <Engine/World/WorldFunction.h>
namespace DopeEngine
{
	class GameSession;
	class Entity;

	/// <summary>
	/// Represents a collection of entities
	/// </summary>
	class DOPE_ENGINE_API World final
	{
		friend class GameSession;
	public:
		FORCEINLINE String get_name() const;
		FORCEINLINE const Array<Entity*>& get_entities_fast() const;
		FORCEINLINE Array<WorldFunction*>& get_functions();
		FORCEINLINE bool is_current() const;

		Entity* create_entity(const String& name = "Default Entity Name");
		void delete_entity(Entity* entity);

		void mark_current();

		template<typename TFunction>
		TFunction* get_function() const;
		template<typename TFunction,typename... TParameters>
		void register_function(TParameters... parameters);
		template<typename TFunction>
		bool remove_function();

		void destroy();

	private:
		World(const String& name = "Default World Name", GameSession* ownerSession = nullptr);
		~World() = default;

		FORCEINLINE GameSession* get_owner_session() const;

		void _unmark_current();
		
		void _on_destroy();
	private:
		Array<Entity*> Entities;
		Array<WorldFunction*> Functions;
		GameSession* OwnerSession;
		String Name;
		bool Current;
	};


	template<typename TFunction>
	TFunction* World::get_function() const
	{
		/*
		* Get function class name
		*/
		const String className = TFunction::get_function_class_name_static();

		/*
		* Iterate and find
		*/
		for (unsigned int i = 0; i < Functions.get_cursor(); i++)
		{
			/*
			* Get function
			*/
			WorldFunction* function = Functions[i];

			/*
			* Validate match
			*/
			if (className == function->get_function_class_name())
				return (TFunction*)function;
		}
		return nullptr;
	}

	template<typename TFunction,typename... TParameters>
	inline void World::register_function(TParameters... parameters)
	{
		/*
		* Create function
		*/
		TFunction* function = new TFunction(parameters...);

		/*
		* Set owner world
		*/
		function->_set_owner_world(this);

		/*
		* Initialize
		*/
		function->initialize();

		/*
		* Register it to the world functions list
		*/
		Functions.add(function);
	}

	template<typename TFunction>
	inline bool World::remove_function()
	{
		/*
		* Get resolver class name
		*/
		const String className = TFunction::get_function_class_name_static();

		/*
		* Iterate and find a match
		*/
		for (unsigned int i = 0; i < Functions.get_cursor(); i++)
		{
			/*
			* Get function
			*/
			WorldFunction* function = Functions[i];

			/*
			* Validate class names
			*/
			if (className == function->get_function_class_name())
			{
				/*
				* Finalize function
				*/
				function->finalize();

				/*
				* Free heap memory
				*/
				delete function;

				/*
				* Remove it from the world functions list
				*/
				Functions.remove_index(i);
				i--;

				return true;
			}
		}

		return false;
	}

}