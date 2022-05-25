#include "TestingModule.h"
#include <Engine/World/World.h>
#include <Engine/World/Entity.h>
#include <Engine/Application/Session/GameSession.h>
#include <Engine/World/Components/TestComponent.h>
#include <IterativeLogic/IterativeLogicWorldFunction.h>
namespace DopeEngine
{
	void TestingModule::initialize()
	{
		/*
		* Create dummy world
		*/
		World* world = get_owner_session()->create_world("Dope engine test world");
		world->mark_current();

		/*
		* Register logic resolver
		*/
		world->register_function<IterativeLogicWorldFunction>();

		/*
		* Create entity
		*/
		Entity* debugEntity = world->create_entity("Debug entity");

		/*
		* Create component
		*/
		TestComponent* testComponent = debugEntity->create_component<TestComponent>("my log message");
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