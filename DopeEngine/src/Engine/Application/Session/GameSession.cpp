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
    Window* GameSession::get_window() const
    {
        return SessionWindow;
    }
    World* GameSession::create_world(const String& name)
    {
        World* world = new World(name, this);
        ExistingWorlds.add(world);
        return world;
    }
    void GameSession::delete_world(World* world)
    {
        if (world->is_current())
            CurrentWorld = nullptr;

        world->_on_destroy();

        ExistingWorlds.remove(world);
        delete world;
    }
    void GameSession::set_world_current(World* world)
    {
        unmark_existing_worlds();
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