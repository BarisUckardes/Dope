#pragma once
#include <Engine/Reflection/Function/ReflectableFunctionParameter.h>
#include <Engine/Structures/Array.h>
#include <Engine/Reflection/Function/ReflectableFunctionDispatcher.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API ReflectableFunction
	{
		friend class ReflectableFunctionDispatcher;
		friend class ReflectableFunctionParameterDispatcher;
	public:
		ReflectableFunction(const String& name, ReflectableType* returnType, ReflectionBindingFlags flags);
		~ReflectableFunction() = default;

		FORCEINLINE String get_name() const;
		Array<ReflectableFunctionParameter> get_parameters() const;
		ReflectableType* get_return_type() const;
		ReflectionBindingFlags get_flags() const;

	private:
		void _register_parameter(const ReflectableFunctionParameter& parameter);
	private:
		Array<ReflectableFunctionParameter> Parameters;
		ReflectableType* ReturnType;
		String Name;
		ReflectionBindingFlags Flags;
	};


}