#include "World.h"
#include <Engine/World/Entity.h>
#include <Engine/Application/Session/GameSession.h>
#include <Engine/World/WorldResolver.h>
namespace DopeEngine
{
    const Array<Entity*>& World::get_entities_fast() const
    {
        return Entities;
    }

    Array<Entity*> World::get_entities_slow() const
    {
        return Entities;
    }

    Array<WorldResolver*>& World::get_resolvers_fast()
    {
        return Resolvers;
    }

    Array<WorldResolver*> World::get_resolvers_slow()
    {
        return Resolvers;
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
        /*
        * Create entity
        */
        Entity* entity = new Entity(name, this);

        /*
        * Register the entity to the entity list
        */
        Entities.add(entity);

        return entity;
    }

    void World::delete_entity(Entity* entity)
    {
        /*
        * Try find index
        */
        const int index = Entities.find_index(entity);

        /*
        * Validate index
        */
        if (index != -1)
        {
            /*
            * Get entity
            */
            Entity* entity = Entities[index];

            /*
            * Call on destory procedure
            */
            entity->_on_destroy();

            /*
            * Remove from the entities of this world
            */
            Entities.remove_index(index);

            /*
             * Free entity memory (???)
            */
            delete entity;
        }
    }

    void World::tick_world()
    {
        /*
        * Iterate resolvers and resolve them
        */
        for (unsigned int i = 0; i < Resolvers.get_cursor(); i++)
        {
            Resolvers[i]->resolve();
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
    void World::_mark_current()
    {
        Current = true;
    }
    void World::_unmark_current()
    {
        Current = false;
    }
    void World::_on_destroy()
    {
        /*
        * Destroy resolvers
        */
        for (unsigned int i = 0; i < Resolvers.get_cursor(); i++)
        {
            /*
            * Get resolvers
            */
            WorldResolver* resolver = Resolvers[i];

            /*
            * Finalize resolver
            */
            resolver->finalize();

            /*
            * Delete heap memory
            */
            delete resolver;
        }
        Resolvers.clear();

        /*
        * Destroy entities
        */
        for (unsigned int i = 0; i < Entities.get_cursor(); i++)
        {
            /*
            * Get entity
            */
            Entity* entity = Entities[i];

            /*
            * Destroy entity
            */
            entity->destroy();
        }
        Entities.clear();

    }

}