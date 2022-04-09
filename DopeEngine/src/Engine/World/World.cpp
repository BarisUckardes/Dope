#include "World.h"
#include <Engine/World/Entity.h>
namespace DopeEngine
{
    Array<Entity*>& World::get_entities_fast()
    {
        return Entities;
    }
    Array<Entity*> World::get_entities_slow() const
    {
        return Entities;
    }
    Entity* World::create_entity(const String& name)
    {
        /*
        * Create entity
        */
        Entity* entity = new Entity(name, this);

        return entity;
    }
    void World::delete_entity(Entity* entity)
    {
        /*
        * Try find
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
    World::World(const String& name, ApplicationSession* ownerSession)
    {
        Name = name;
        OwnerSession = ownerSession;
    }
}