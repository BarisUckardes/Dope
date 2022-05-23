#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Array.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	class Component;
	class World;

	/// <summary>
	/// A world procedure unit, can create renderer,logic,physics and etc routines
	/// </summary>
	class DOPE_ENGINE_API WorldFunction
	{
		friend class World;
	public:
		virtual String get_function_class_name() const = 0;

		virtual void register_component(Component* component) = 0;
		virtual void remove_component(Component* component) = 0;
		virtual void initialize() = 0;
		virtual void execute() = 0;
		virtual void finalize() = 0;
	protected:
		WorldFunction() : OwnerWorld(nullptr) {}
		~WorldFunction() = default;

		World* get_owner_world() const;
	private:
		void _set_owner_world(World* world);
	private:
		World* OwnerWorld;
	};


#define GENERATE_WORLD_FUNCTION(className) public: static String get_function_class_name_static() { return #className; } virtual String get_function_class_name() const override { return #className;}
}