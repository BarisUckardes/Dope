#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	class Entity;
	/// <summary>
	/// Single logic object for entities to carry around
	/// </summary>
	class DOPE_ENGINE_API Component
	{
		friend class Entity;
	public:
		/// <summary>
		/// Returns the component class name for identification
		/// </summary>
		/// <returns></returns>
		virtual String get_component_class_name() const;

		virtual void initialize() = 0;
		virtual void update() = 0;
		virtual void finalize() = 0;

	protected:
		Component() = default;
		~Component();

	private:
		void _set_owner_entity(Entity* ownerEntity);
	private:
		Entity* OwnerEntity;
	};

#define GENERATE_COMPONENT(className) virtual String get_component_class_name() const override { return #className;}
}