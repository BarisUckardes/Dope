#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Reflection/ReflectionBindingFlags.h>
#include <Engine/Reflection/Field/ReflectableFieldDispatcher.h>
namespace DopeEngine
{
	class ReflectableType;
	class DOPE_ENGINE_API ReflectableField
	{
		friend class ReflectableFieldDispatcher;
	public:
		ReflectableField(const String& name,
			const unsigned int offset, const unsigned int size,
			ReflectableType* ownerType, ReflectableType* fieldType,
			const ReflectionBindingFlags flags);
		~ReflectableField() = default;

		unsigned int get_offset() const;
		unsigned int get_size() const;
		String get_name() const;
		ReflectableType* get_field_type() const;
		ReflectableType* get_owner_type() const;
		ReflectionBindingFlags get_flags() const;

		template<typename TValue>
		TValue* get_field_ptr_as(void* object) const;

		template<typename TValue>
		TValue get_field_value_as(void* object) const;

		template<typename TValue>
		void set_field_value(void* object, const TValue& value)const;
	private:
		ReflectableType* OwnerType;
		ReflectableType* FieldType;
		String Name;
		unsigned int Offset;
		unsigned int Size;
		ReflectionBindingFlags Flags;
	};
	template<typename TValue>
	inline TValue* ReflectableField::get_field_ptr_as(void* object) const
	{
		/*
		* Get offset ptr
		*/
		const Byte* offsetPtr = (const Byte*)object + Offset;

		return (TValue*)offsetPtr;
	}

	template<typename TValue>
	inline TValue ReflectableField::get_field_value_as(void* object) const
	{
		/*
		* Get offset ptr
		*/
		const Byte* offsetPtr = (const Byte*)object + Offset;


		return *((TValue*)offsetPtr);
	}

	template<typename TValue>
	inline void ReflectableField::set_field_value(void* object, const TValue& value) const
	{
		/*
		* Get offset ptr
		*/
		const Byte* offsetPtr = (const Byte*)object + Offset;

		/*
		* Get as TValue
		*/
		TValue* targetPtr = (TValue*)offsetPtr;

		/*
		* Set value
		*/
		*targetPtr = value;
	}


	#define GET_FIELD_NAME(field) field
	#define GENERATE_REFLECTABLE_FIELD(ownerType,fieldName,fieldType,bindingFlags)\
		DopeEngine::ReflectableFieldDispatcher dispatcher_fieldType_##ownerType##fieldType(typeof(ownerType),typeof(fieldType),#fieldName,offsetof(ownerType,fieldName),sizeof(fieldType),bindingFlags);
}