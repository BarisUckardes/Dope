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
		FORCEINLINE Spatial* get_spatial() const;
		FORCEINLINE Entity* get_owner_entity() const;

		void destroy();

		virtual String get_component_class_name() const = 0;
		virtual bool should_tick() const = 0;

		virtual void initialize();
		virtual void update() = 0;
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