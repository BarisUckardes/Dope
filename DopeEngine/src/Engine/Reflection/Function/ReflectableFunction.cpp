#include "ReflectableFunction.h"

namespace DopeEngine
{
    ReflectableFunction::ReflectableFunction(const String& name, ReflectableType* returnType, ReflectionBindingFlags flags)
    {
        Name = name;
        ReturnType = returnType;
        Flags = flags;
    }
    String ReflectableFunction::get_name() const
    {
        return Name;
    }

    Array<ReflectableFunctionParameter> ReflectableFunction::get_parameters() const
    {
        return Parameters;
    }

    ReflectableType* ReflectableFunction::get_return_type() const
    {
        return ReturnType;
    }

    ReflectionBindingFlags ReflectableFunction::get_flags() const
    {
        return Flags;
    }

    void ReflectableFunction::_register_parameter(const ReflectableFunctionParameter& parameter)
    {
        Parameters.add(parameter);
    }

}