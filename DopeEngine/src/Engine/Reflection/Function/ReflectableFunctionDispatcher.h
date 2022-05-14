#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Reflection/ReflectionBindingFlags.h>

namespace DopeEngine
{
	class ReflectableType;
	class ReflectableFunction;
	class DOPE_ENGINE_API ReflectableFunctionDispatcher
	{
	public:
		ReflectableFunctionDispatcher(const String& name, ReflectableType* returnType, const ReflectionBindingFlags flags, ReflectableType* ownerType);
		~ReflectableFunctionDispatcher() = default;

		ReflectableFunction* get_dispatched_function() const;
	private:
		ReflectableFunction* DispatchedFunction;
	};

#define GENERATE_MEMBER_FUNCTION(ownerType,name,returnType,flags)\
	DopeEngine::ReflectableFunctionDispatcher reflectable_member_function_dispatcher(#name,typeof(returnType),flags,typeof(ownerType));
}