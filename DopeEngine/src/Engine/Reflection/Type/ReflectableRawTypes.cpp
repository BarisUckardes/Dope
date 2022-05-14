#include "ReflectableRawTypes.h"

#define GENERATE_RAW_TYPE(type) DopeEngine::ReflectableType* GET_RAW_NAME(type)_reflection_type_accessor_::s_OwnerType = new DopeEngine::ReflectableType(#type,sizeof(type),true);
#define GENERATE_VOID_TYPE DopeEngine::ReflectableType* GET_RAW_NAME(void)_reflection_type_accessor_::s_OwnerType = new DopeEngine::ReflectableType("void",0,true);

GENERATE_RAW_TYPE(int);
GENERATE_RAW_TYPE(float);
GENERATE_RAW_TYPE(short);
GENERATE_RAW_TYPE(double);
GENERATE_RAW_TYPE(long);
GENERATE_RAW_TYPE(char);
GENERATE_RAW_TYPE(bool);
GENERATE_VOID_TYPE;