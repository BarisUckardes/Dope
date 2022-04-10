#include "WorldResolverModule.h"
#include <Engine/Structures/Array.h>
#include <Engine/World/World.h>
#include <Engine/Application/Session/GameSession.h>
namespace DopeEngine
{
    void WorldResolverModule::initialize()
    {
    }
    void WorldResolverModule::update()
    {
        /*
        * Get world
        */
        const Array<World*>& worlds = get_owner_session()->get_existing_worlds_fast();

        /*
        * Iterate each world
        */
        for (unsigned int worldIndex = 0; worldIndex < worlds.get_cursor(); worldIndex++)
        {
            /*
            * Get world
            */
            World* world = worlds[worldIndex];

            /*
            * Get world resolvers
            */
            const Array<WorldResolver*>& resolvers = world->get_resolvers_fast();

            /*
            * Iterate each resolver
            */
            for (unsigned int resolverIndex = 0; resolverIndex < resolvers.get_cursor(); resolverIndex++)
            {
                resolvers[resolverIndex]->resolve();
            }

        }
    }
    void WorldResolverModule::finalize()
    {

    }
    void WorldResolverModule::on_receive_application_event(ApplicationEvent* event)
    {

    }
}