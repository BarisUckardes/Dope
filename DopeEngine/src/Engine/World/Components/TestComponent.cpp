#include "TestComponent.h"
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{
	TestComponent::TestComponent(const String& debugMessage)
	{
		Message = debugMessage;
	}
	bool TestComponent::should_tick() const
	{
		return true;
	}
	void TestComponent::initialize()
	{
		Component::initialize();
	}
	void TestComponent::update()
	{
		LOG("TestComponent", "Update tick message -> %s", *Message);
	}
	void TestComponent::finalize()
	{
		Component::finalize();
	}
}