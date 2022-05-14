#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	enum DOPE_ENGINE_API ReflectionBindingFlags
	{
		ReflectionBindingFlags_None  = 0,
		ReflectionBindingFlags_Public = 1 << 0,
		ReflectionBindingFlags_Private = 1 << 1,
		ReflectionBindingFlags_Protected = 1 << 2,
		ReflectionBindingFlags_Instance = 1 << 3,
		ReflectionBindingFlags_Static = 1 << 4,
		ReflectionBindingFlags_Function = 1 << 5,
		ReflectionBindingFlags_Const = 1 << 6,
		ReflectionBindingFlags_Reference = 1 << 7,
		ReflectionBindingFlags_Pointer = 1 << 8,
		ReflectionBindingFlags_Value = 1 << 9,
		ReflectionBindingFlags_Virtual = 1 << 10,
		ReflectionBindingFlags_PureVirtual = 1 < 11,
	};
}