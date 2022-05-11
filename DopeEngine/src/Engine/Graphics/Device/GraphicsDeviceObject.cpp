#include "GraphicsDeviceObject.h"

namespace DopeEngine
{
    String GraphicsDeviceObject::get_debug_name() const
    {
        return DebugName;
    }
    void GraphicsDeviceObject::set_debug_name(const String& name)
    {
        DebugName = name;
    }
    GraphicsDeviceObjectType GraphicsDeviceObject::get_device_object_type() const
    {
        return Type;
    }
}