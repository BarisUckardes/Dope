#include "ReflectableEnum.h"


namespace DopeEngine
{
	ReflectableEnum::ReflectableEnum()
	{

	}
	Array<ReflectableEnumField> ReflectableEnum::get_fields() const
	{
		return Fields;
	}

	String ReflectableEnum::get_name() const
	{
		return Name;
	}

	unsigned int ReflectableEnum::get_field_count() const
	{
		return FieldCount;
	}

}