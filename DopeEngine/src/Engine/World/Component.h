#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	class Entity;
	class Spatial;
	/// <summary>
	/// Single logic object for entities to carry around
	/// </summary>
	class DOPE_ENGINE_API Component
	{
		friend class Entity;
	public:
		/// <summary>
		/// Returns the spatial of this component's owner entity
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Spatial* get_spatial() const;

		/// <summary>
		/// Returns the owning entity of this component
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Entity* get_owner_entity() const;

		/// <summary>
		/// Destroys this component
		/// </summary>
		void destroy();

		/// <summary>
		/// Returns the component class name for identification
		/// </summary>
		/// <returns></returns>
		virtual String get_component_class_name() const = 0;

		/// <summary>
		/// Returns whether this component should tick or not
		/// </summary>
		/// <returns></returns>
		virtual bool should_tick() const = 0;

		/// <summary>
		/// Called upon first creation
		/// </summary>
		virtual void initialize();

		/// <summary>
		/// Called every frame from the logic feed
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// Called upon destroy
		/// </summary>
		virtual void finalize();

	protected:
		Component() = default;
		~Component();

	private:
		void _set_owner_entity(Entity* ownerEntity);
	private:
		Entity* OwnerEntity;
	};

#define GENERATE_COMPONENT(className) public: static String get_component_class_name_static() { return #className; } virtual String get_component_class_name() const override { return #className;}
}