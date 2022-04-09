#include "IPortableDeviceEnumarator.h"

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Devices/Portable/WindowsPortableDeviceManager.h>
typedef DopeEngine::WindowsPortableDeviceManager DeviceManagerAbstraction;
#endif
namespace DopeEngine
{
    IPortableDeviceEnumarator* IPortableDeviceEnumarator::create()
    {
        return new DeviceManagerAbstraction();
    }
}