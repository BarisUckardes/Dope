#include "ReflectableField.h"

namespace DopeEngine
{
	ReflectableField::ReflectableField(const String& name, const unsigned int offset, const unsigned int size, ReflectableType* ownerType, ReflectableType* fieldType, const ReflectionBindingFlags flags)
	{
		Name = name;
		Offset = offset;
		Size = size;
		OwnerType = ownerType;
		FieldType = fieldType;
		Flags = flags;

	}

	unsigned int ReflectableField::get_offset() const
	{
		return Offset;
	}

	unsigned int ReflectableField::get_size() const
	{
		return Size;
	}

	String ReflectableField::get_name() const
	{
		return Name;
	}

	ReflectableType* ReflectableField::get_field_type() const
	{
		return FieldType;
	}

	ReflectableType* ReflectableField::get_owner_type() const
	{
		return OwnerType;
	}

	ReflectionBindingFlags ReflectableField::get_flags() const
	{
		return Flags;
	}

}