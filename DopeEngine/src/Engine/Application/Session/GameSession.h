#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Application/Window/Window.h>

namespace DopeEngine
{
	class World;

	/// <summary>
	/// Represents a single whole DopeEngine session state
	/// </summary>
	class DOPE_ENGINE_API GameSession final
	{
	public:
		GameSession(Window* window);
		~GameSession();

		FORCEINLINE World* get_current_world() const;
		FORCEINLINE const Array<World*>& get_existing_worlds_fast() const;
		Window* get_window() const;

		World* create_world(const String& name);
		void delete_world(World* world);
		void set_world_current(World* world);
	private:
		void unmark_existing_worlds();
	private:
		Array<World*> ExistingWorlds;
		World* CurrentWorld;
		Window* SessionWindow;
	};


}