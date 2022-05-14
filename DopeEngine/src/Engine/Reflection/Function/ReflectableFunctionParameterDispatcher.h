#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Reflection/Function/ReflectableFunctionParameter.h>
namespace DopeEngine
{
	class ReflectableType;
	class ReflectableFunction;
	class DOPE_ENGINE_API ReflectableFunctionParameterDispatcher
	{
	public:
		ReflectableFunctionParameterDispatcher(const String& name,ReflectableType* type,const ReflectionBindingFlags flags,ReflectableFunction* function);
		~ReflectableFunctionParameterDispatcher() = default;
	};

#define GENERATE_MEMBER_FUNCTION(ownerType,name,returnType,flags)\
	DopeEngine::ReflectableFunctionDispatcher GET_RAW_NAME(ownerType)GET_RAW_NAME(name)reflectable_member_function_dispatcher(#name,typeof(returnType),flags,typeof(ownerType));


#define GENERATE_FUNCTION_PARAMETER(memberType,ownerFunctionName,name,type,flags) \
	DopeEngine::ReflectableFunctionParameterDispatcher GET_RAW_NAME(ownerFunctionName)GET_RAW_NAME(name)_reflectable_member_function_parameter_dispatcher(#name,typeof(type),flags,GET_RAW_NAME(memberType)GET_RAW_NAME(ownerFunctionName)reflectable_member_function_dispatcher.get_dispatched_function());
}