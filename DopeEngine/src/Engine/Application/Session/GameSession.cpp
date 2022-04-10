#include "GameSession.h"
#include <Engine/World/World.h>
namespace DopeEngine
{
    GameSession::GameSession(Window* window)
    {
        SessionWindow = window;
    }
    GameSession::~GameSession()
    {

    }
    World* GameSession::get_current_world() const
    {
        return CurrentWorld;
    }
    const Array<World*>& GameSession::get_existing_worlds_fast() const
    {
        return ExistingWorlds;
    }
    Array<World*> GameSession::get_existing_worlds_slow() const
    {
        return ExistingWorlds;
    }
    Window* GameSession::get_window() const
    {
        return SessionWindow;
    }
    World* GameSession::create_world(const String& name)
    {
        /*
        * Create new world
        */
        World* world = new World(name, this);

        /*
        * Register to the existing world lsit
        */
        ExistingWorlds.add(world);

        return world;
    }
    void GameSession::delete_world(World* world)
    {
        /*
        * Set current nullptr if the world is the current world
        */
        if (world->is_current())
            CurrentWorld = nullptr;

        /*
        * Destroy world
        */
        world->_on_destroy();

        /*
        * Remove it from the list
        */
        ExistingWorlds.remove(world);

        /*
        * Delete world
        */
        delete world;
    }
    void GameSession::set_world_current(World* world)
    {
        /*
        * Unmark all the worlds
        */
        unmark_existing_worlds();

        /*
        * Mark the world current
        */
        world->_mark_current();
    }
    void GameSession::unmark_existing_worlds()
    {
        for (unsigned int i = 0; i < ExistingWorlds.get_cursor(); i++)
        {
            ExistingWorlds[i]->_unmark_current();
        }
    }
}