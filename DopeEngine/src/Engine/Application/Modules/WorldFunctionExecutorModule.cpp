#include "WorldFunctionExecutorModule.h"
#include <Engine/Structures/Array.h>
#include <Engine/World/World.h>
#include <Engine/Application/Session/GameSession.h>
namespace DopeEngine
{
    void WorldFunctionExecutorModule::initialize()
    {
    }
    void WorldFunctionExecutorModule::update()
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
            * Get world functions
            */
            const Array<WorldFunction*>& functions = world->get_functions();

            /*
            * Iterate each function
            */
            for (unsigned int functionIndex = 0; functionIndex < functions.get_cursor(); functionIndex++)
            {
                functions[functionIndex]->execute();
            }

        }
    }
    void WorldFunctionExecutorModule::finalize()
    {

    }
    void WorldFunctionExecutorModule::on_receive_application_event(ApplicationEvent* event)
    {

    }
}