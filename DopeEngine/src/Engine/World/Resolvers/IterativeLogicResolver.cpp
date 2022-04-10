#include "IterativeLogicResolver.h"
#include <Engine/World/Component.h>

namespace DopeEngine
{
	void IterativeLogicResolver::register_component(Component* component)
	{
		LogicInflictedComponents.add(component);
	}
	void IterativeLogicResolver::remove_component(Component* component)
	{
		LogicInflictedComponents.remove(component);
	}
	void IterativeLogicResolver::initialize()
	{

	}
	void IterativeLogicResolver::resolve()
	{
		/*
		* Iterate and invoke
		*/
		for (unsigned int i = 0; i < LogicInflictedComponents.get_cursor(); i++)
		{
			LogicInflictedComponents[i]->update();
		}
	}
	void IterativeLogicResolver::finalize()
	{
		/*
		* Remove each component list
		*/
		LogicInflictedComponents.clear();
	}
}