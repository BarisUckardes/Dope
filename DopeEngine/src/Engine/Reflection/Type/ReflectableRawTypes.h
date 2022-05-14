#pragma once
#include <Engine/Reflection/Type/ReflectableType.h>

#define GENERATE_RAW_REFLECTION_ACCESSOR(type)\
	class DOPE_ENGINE_API GET_RAW_NAME(type)_reflection_type_accessor_\
	{\
	public:\
		static DopeEngine::ReflectableType* get_owner_type() { return s_OwnerType; }\
	private:\
		static DopeEngine::ReflectableType* s_OwnerType;\
	}


GENERATE_RAW_REFLECTION_ACCESSOR(int);
GENERATE_RAW_REFLECTION_ACCESSOR(float);
GENERATE_RAW_REFLECTION_ACCESSOR(short);
GENERATE_RAW_REFLECTION_ACCESSOR(double);
GENERATE_RAW_REFLECTION_ACCESSOR(long);
GENERATE_RAW_REFLECTION_ACCESSOR(char);
GENERATE_RAW_REFLECTION_ACCESSOR(bool);
GENERATE_RAW_REFLECTION_ACCESSOR(void);