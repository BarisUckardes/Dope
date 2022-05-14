#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Reflection/ReflectionBindingFlags.h>

namespace DopeEngine
{
	class ReflectableType;
	class DOPE_ENGINE_API ReflectableFieldDispatcher
	{
	public:
		ReflectableFieldDispatcher(ReflectableType* ownerType,ReflectableType* fieldType,const String& name,const unsigned int offset,const unsigned int size,const ReflectionBindingFlags flags);
		~ReflectableFieldDispatcher() = default;
	};


}