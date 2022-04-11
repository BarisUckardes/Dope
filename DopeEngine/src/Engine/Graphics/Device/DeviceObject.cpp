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
}