#include "World.h"
#include <Engine/World/Entity.h>
#include <Engine/Application/Session/GameSession.h>
#include <Engine/World/WorldFunction.h>
namespace DopeEngine
{
    String World::get_name() const
    {
        return Name;
    }
    const Array<Entity*>& World::get_entities_fast() const
    {
        return Entities;
    }

    Array<WorldFunction*>& World::get_functions()
    {
        return Functions;
    }

  
    bool World::is_current() const
    {
        return Current;
    }

    GameSession* World::get_owner_session() const
    {
        return OwnerSession;
    }

    Entity* World::create_entity(const String& name)
    {
        Entity* entity = new Entity(name, this);

        Entities.add(entity);

        return entity;
    }

    void World::delete_entity(Entity* entity)
    {
        const int index = Entities.find_index(entity);
        if (index != -1)
        {
            Entity* entity = Entities[index];

            entity->_on_destroy();

            Entities.remove_index(index);

            delete entity;
        }
    }

    void World::destroy()
    {
        OwnerSession->delete_world(this);
    }

    World::World(const String& name, GameSession* ownerSession)
    {
        Name = name;
        OwnerSession = ownerSession;
        Current = false;
    }
    void World::mark_current()
    {
        Current = true;
        OwnerSession->set_world_current(this);
    }
    void World::_unmark_current()
    {
        Current = false;
    }
    void World::_on_destroy()
    {
        for (unsigned int i = 0; i < Functions.get_cursor(); i++)
        {
            WorldFunction* function = Functions[i];

            function->finalize();

            delete function;
        }
        Functions.clear();

        /*
        * Destroy entities
        */
        for (unsigned int i = 0; i < Entities.get_cursor(); i++)
        {
            Entity* entity = Entities[i];

            entity->destroy();
        }
        Entities.clear();

    }

}