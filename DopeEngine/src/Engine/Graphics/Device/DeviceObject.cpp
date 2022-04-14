#include "DeviceObject.h"

namespace DopeEngine
{
    String DeviceObject::get_debug_name() const
    {
        return DebugName;
    }
    void DeviceObject::set_debug_name(const String& name)
    {
        DebugName = name;
    }
    DeviceObjectType DeviceObject::get_device_object_type() const
    {
        return Type;
    }
}