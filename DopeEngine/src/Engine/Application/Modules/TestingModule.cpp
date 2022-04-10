#include "TestingModule.h"
#include <Engine/World/World.h>
#include <Engine/World/Entity.h>
#include <Engine/Application/Session/GameSession.h>
#include <Engine/World/Components/TestComponent.h>
#include <Engine/World/Resolvers/IterativeLogicResolver.h>
namespace DopeEngine
{
	void TestingModule::initialize()
	{
		/*
		* Create dummy world
		*/
		World* world = get_owner_session()->create_world("Dope engine test world");

		/*
		* Register logic resolver
		*/
		world->register_resolver<IterativeLogicResolver>();

		/*
		* Create entity
		*/
		Entity* debugEntity = world->create_entity("Debug entity");

		/*
		* Create component
		*/
		TestComponent* testComponent = debugEntity->create_component<TestComponent>("my log message");

		world->destroy();

	}
	void TestingModule::update()
	{
	}
	void TestingModule::finalize()
	{

	}
	void TestingModule::on_receive_application_event(ApplicationEvent* event)
	{

	}
}