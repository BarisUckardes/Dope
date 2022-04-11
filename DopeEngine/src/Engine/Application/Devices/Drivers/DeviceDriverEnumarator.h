#pragma once
#include <Engine/Core/Symbols.h>

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Devices/Drivers/WindowsDriverEnumarator.h>
typedef DopeEngine::WindowsDriverEnumarator DeviceDriverEnumarator;
#endif
