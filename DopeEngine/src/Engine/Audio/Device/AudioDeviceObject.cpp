#include "AudioDeviceObject.h"

namespace DopeEngine
{
    String AudioDeviceObject::get_name() const
    {
        return Name;
    }

    AudioDeviceObjectType AudioDeviceObject::get_type() const
    {
        return Type;
    }

    void AudioDeviceObject::set_name(const String& name)
    {
        Name = name;
    }

}