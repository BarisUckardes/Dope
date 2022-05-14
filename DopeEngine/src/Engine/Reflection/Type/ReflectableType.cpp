#include "ReflectableType.h"

namespace DopeEngine
{
	ReflectableType::ReflectableType(const String& name, const unsigned int size, const bool bPrimitive)
	{
		Name = name;
		Size = size;
		Primitive = bPrimitive;
	}

	String ReflectableType::get_name() const
	{
		return Name;
	}

	Array<ReflectableType*> ReflectableType::get_sub_types() const
	{
		return SubTypes;
	}

	void ReflectableType::_register_field(ReflectableField* field)
	{
		Fields.add(field);
	}

	void ReflectableType::_register_function(ReflectableFunction* function)
	{
		Functions.add(function);
	}

	void ReflectableType::_register_sub_type(ReflectableType* subType)
	{
		SubTypes.add(subType);
	}

}