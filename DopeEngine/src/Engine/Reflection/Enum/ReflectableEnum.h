#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Reflection/Enum/ReflectableEnumField.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API ReflectableEnum
	{
	public:
		ReflectableEnum();
		~ReflectableEnum() = default;

		FORCEINLINE Array<ReflectableEnumField> get_fields() const;
		FORCEINLINE String get_name() const;
		FORCEINLINE unsigned int get_field_count() const;
		FORCEINLINE ReflectableEnumField get_field(const String& name) const;
	private:
		Array<ReflectableEnumField> Fields;
		String Name;
		unsigned int FieldCount;
	};
}