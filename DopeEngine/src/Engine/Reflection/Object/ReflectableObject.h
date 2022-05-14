#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	class ReflectableType;
	class DOPE_ENGINE_API ReflectableObject
	{
	public:
		virtual ReflectableType* get_type() const = 0;
	};

	#define GENERATE_REFLECTABLE_OBJECT(type) private:\
												  static DopeEngine::ReflectableType* s_type_##type;\
												  protected:\
												  public:\
												  virtual DopeEngine::ReflectableType* get_type() const override { return s_type_##type; }\
												  static DopeEngine::ReflectableType* get_static_type() { return s_type_##type;}\

	

	#define GENERATE_REFLECTION_ACCESSOR(type)\
	GENERATE_REFLECTABLE_TYPE(type);\
	class GET_RAW_NAME(type)_reflection_type_accessor_\
	{\
	public:\
		static DopeEngine::ReflectableType* get_owner_type() { return type::get_static_type();}\
	}
}