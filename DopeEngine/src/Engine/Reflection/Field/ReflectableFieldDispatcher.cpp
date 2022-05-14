#include "ReflectableFieldDispatcher.h"
#include <Engine/Reflection/Type/ReflectableType.h>
#include <Engine/Reflection/Field/ReflectableField.h>
namespace DopeEngine
{
	ReflectableFieldDispatcher::ReflectableFieldDispatcher(ReflectableType* ownerType, ReflectableType* fieldType, const String& name, const unsigned int offset, const unsigned int size, const ReflectionBindingFlags flags)
	{
		/*
		* Create new field
		*/
		ReflectableField* field = new ReflectableField(name, offset, size, ownerType, fieldType, flags);

		/*
		* Register
		*/
		ownerType->_register_field(field);
	}

}