#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Reflection/Object/ReflectableObjectGenerator.h>

namespace DopeEngine
{
	class ReflectableType;
	class ReflectableObject;
	typedef ReflectableObject* (*ReflectableObjectGenerator)(void);
	class DOPE_ENGINE_API ReflectableObjectDispatcher
	{
	public:
		ReflectableObjectDispatcher(ReflectableObjectGenerator generator, ReflectableType* ownerType);
		~ReflectableObjectDispatcher() = default;

	};
}