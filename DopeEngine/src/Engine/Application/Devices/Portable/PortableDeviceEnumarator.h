#pragma once
#include <Engine/Core/Symbols.h>

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Devices/Portable/WindowsPortableDeviceEnumarator.h>
typedef DopeEngine::WindowsPortableDeviceEnumarator PortableDeviceEnumarator;
#endif