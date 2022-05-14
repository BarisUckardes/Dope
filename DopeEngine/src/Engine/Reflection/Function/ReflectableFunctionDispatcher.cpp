#include "ReflectableFunctionDispatcher.h"
#include <Engine/Reflection/Type/ReflectableType.h>
#include <Engine/Reflection/Function/ReflectableFunction.h>
namespace DopeEngine
{

	ReflectableFunctionDispatcher::ReflectableFunctionDispatcher(const String& name, ReflectableType* returnType, const ReflectionBindingFlags flags, ReflectableType* ownerType)
	{
		/*
		* Create reflectable function
		*/
		ReflectableFunction* function = new ReflectableFunction(name,returnType,flags);

		/*
		* Set
		*/
		ownerType->_register_function(function);

		/*
		* Register dispatched function
		*/
		DispatchedFunction = function;
	}
	ReflectableFunction* ReflectableFunctionDispatcher::get_dispatched_function() const
	{
		return DispatchedFunction;
	}
}