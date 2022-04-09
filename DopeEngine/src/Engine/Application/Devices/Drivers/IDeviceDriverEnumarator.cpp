#include "IDeviceDriverEnumarator.h"

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Devices/Drivers/WindowsDriverEnumarator.h>
typedef DopeEngine::WindowsDriverEnumarator DriverEnumaratorAbstraction;
#endif

namespace DopeEngine
{
	IDeviceDriverEnumarator* IDeviceDriverEnumarator::create()
	{
		return new DriverEnumaratorAbstraction();
	}
}