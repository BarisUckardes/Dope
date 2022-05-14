#include "ReflectableFunctionParameterDispatcher.h"
#include <Engine/Reflection/Function/ReflectableFunction.h>
namespace DopeEngine
{
	ReflectableFunctionParameterDispatcher::ReflectableFunctionParameterDispatcher(const String& name, ReflectableType* type, const ReflectionBindingFlags flags, ReflectableFunction* function)
	{
		/*
		* Create parameter
		*/
		ReflectableFunctionParameter parameter = { name,type,flags };

		/*
		* Register
		*/
		function->_register_parameter(parameter);
	}


}