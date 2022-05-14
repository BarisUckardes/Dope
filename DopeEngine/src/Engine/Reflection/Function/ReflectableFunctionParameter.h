#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Reflection/ReflectionBindingFlags.h>

namespace DopeEngine
{
	class ReflectableType;

	struct DOPE_ENGINE_API ReflectableFunctionParameter
	{
		ReflectableFunctionParameter(const String& name, ReflectableType* type,const ReflectionBindingFlags flags) : Name(name),Type(type),Flags(flags) {}
		ReflectableFunctionParameter() : Name("Undefined"),Type(nullptr),Flags(ReflectionBindingFlags_None) {}

		String Name;
		ReflectableType* Type;
		ReflectionBindingFlags Flags;
	};
}