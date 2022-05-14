#pragma once
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	struct DOPE_ENGINE_API ReflectableEnumField
	{
		ReflectableEnumField(const String& name,const unsigned int value) : Name(name),Value(value)
		{}
		ReflectableEnumField() : Name("Empty_Field"),Value(0) {}
		~ReflectableEnumField() = default;

		String Name;
		unsigned int Value;
	};
}