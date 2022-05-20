#include "World.h"
#include <Engine/World/Entity.h>
#include <Engine/Application/Session/GameSession.h>
#include <Engine/World/WorldFunction.h>
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
        * Destroy functions
        */
        for (unsigned int i = 0; i < Functions.get_cursor(); i++)
        {
            /*
            * Get functions
            */
            WorldFunction* function = Functions[i];

            /*
            * Finalize function
            */
            function->finalize();

            /*
            * Delete heap memory
            */
            delete function;
        }
        Functions.clear();

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