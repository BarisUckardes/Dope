#include "IterativeLogicWorldFunction.h"
#include <Engine/World/Component.h>

namespace DopeEngine
{
	void IterativeLogicWorldFunction::register_component(Component* component)
	{
		LogicInflictedComponents.add(component);
	}
	void IterativeLogicWorldFunction::remove_component(Component* component)
	{
		LogicInflictedComponents.remove(component);
	}
	void IterativeLogicWorldFunction::initialize()
	{

	}
	void IterativeLogicWorldFunction::execute()
	{
		/*
		* Iterate and invoke
		*/
		for (unsigned int i = 0; i < LogicInflictedComponents.get_cursor(); i++)
		{
			LogicInflictedComponents[i]->update();
		}
	}
	void IterativeLogicWorldFunction::finalize()
	{
		/*
		* Remove each component list
		*/
		LogicInflictedComponents.clear();
	}
}