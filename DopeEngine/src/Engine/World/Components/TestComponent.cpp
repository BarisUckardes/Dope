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
		return false;
	}
	void TestComponent::initialize()
	{
		Component::initialize();
	}
	void TestComponent::update()
	{

	}
	void TestComponent::finalize()
	{
		Component::finalize();
	}
}