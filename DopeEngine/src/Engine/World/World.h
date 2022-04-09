#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	class ApplicationSession;
	class Entity;

	/// <summary>
	/// Represents a collection of entities
	/// </summary>
	class DOPE_ENGINE_API World
	{
		friend class ApplicationSession;
	public:
		/// <summary>
		/// Returns a reference to the entity list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Entity*>& get_entities_fast();

		/// <summary>
		/// Returns a copy to the entity list
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<Entity*> get_entities_slow() const;

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
	private:
		World(const String& name = "Default World Name",ApplicationSession* ownerSession = nullptr);
		~World() = default;
	private:
		Array<Entity*> Entities;
		ApplicationSession* OwnerSession;
		String Name;
	};


}