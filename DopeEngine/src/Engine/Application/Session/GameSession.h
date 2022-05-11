#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Application/Window/Window.h>

namespace DopeEngine
{
	class World;
	class DOPE_ENGINE_API GameSession final
	{
	public:
		GameSession(Window* window);
		~GameSession();

		/// <summary>
		/// Returns the current world of this game session
		/// </summary>
		/// <returns></returns>
		World* get_current_world() const;

		/// <summary>
		/// Returns a reference to the existing world list
		/// </summary>
		/// <returns></returns>
		const Array<World*>& get_existing_worlds_fast() const;

		/// <summary>
		/// Returns a copy to the existing world list
		/// </summary>
		/// <returns></returns>
		Array<World*> get_existing_worlds_slow() const;

		/// <summary>
		/// Returns the window for the game session
		/// </summary>
		/// <returns></returns>
		Window* get_window() const;

		/// <summary>
		/// Creates anew world
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		World* create_world(const String& name);

		/// <summary>
		/// Deletes the specified world
		/// </summary>
		/// <param name="world"></param>
		void delete_world(World* world);

		/// <summary>
		/// Sets a world as current 
		/// </summary>
		/// <param name="world"></param>
		void set_world_current(World* world);
	private:
		void unmark_existing_worlds();
	private:
		Array<World*> ExistingWorlds;
		World* CurrentWorld;
		Window* SessionWindow;
	};


}