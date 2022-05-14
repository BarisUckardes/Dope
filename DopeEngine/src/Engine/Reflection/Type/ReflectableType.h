#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Structures/Array.h>
#include <Engine/Structures/Guid.h>

namespace DopeEngine
{
	class ReflectableObject;
	class ReflectableField;
	class ReflectableFunction;
	typedef ReflectableObject* (*ReflectableObjectGenerator)(void);
	class DOPE_ENGINE_API ReflectableType
	{
		friend class ReflectableFieldDispatcher;
		friend class ReflectableFunctionDispatcher;
	public:
		ReflectableType(const String& name, const unsigned int size, const bool bPrimitive);
		~ReflectableType() = default;

		FORCEINLINE String get_name() const;
		FORCEINLINE Array<ReflectableType*> get_sub_types() const;

		template<typename TObject>
		TObject* generate_default_object_as() const;
	private:
		void _register_field(ReflectableField* field);
		void _register_function(ReflectableFunction* function);
		void _register_sub_type(ReflectableType* subType);
	private:
		Array<ReflectableType*> SubTypes;
		Array<ReflectableField*> Fields;
		Array<ReflectableFunction*> Functions;
		ReflectableObjectGenerator DefaultObjectGenerator;
		String Name;
		Guid ID;
		unsigned int Size;
		bool Primitive;
	};


	template<typename TObject>
	inline TObject* ReflectableType::generate_default_object_as() const
	{
		return (TObject*)DefaultObjectGenerator;
	}

	#define GET_RAW_NAME(name) name
	#define typeof(type) GET_RAW_NAME(type)_reflection_type_accessor_::get_owner_type()

#define GENERATE_REFLECTABLE_TYPE(type)\
	inline DopeEngine::ReflectableType* type::s_type_##type = new DopeEngine::ReflectableType(#type,sizeof(type),false);

#define GENERATE_REFLECTABLE_SUB_TYPE(targetType,subType)\
	DopeEngine::ReflectionSubTypeDispatcher GET_RAW_NAME(targetType)GET_RAW_NAME(subType)_reflection_sub_type(typeof(targetType),typeof(subType));

}