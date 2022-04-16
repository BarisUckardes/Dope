#include "WindowsDriverEnumarator.h"
#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <stdio.h>
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{
#define DRIVER_MAX_COUNT 1024
	Array<DeviceDriverInformation> WindowsDriverEnumarator::enumarate_drivers()
	{
		Array<DeviceDriverInformation> driverInformations;
		LPVOID drivers[DRIVER_MAX_COUNT];
		DWORD cbNeeded;
		unsigned int cDrivers;
		if (EnumDeviceDrivers(drivers, sizeof(drivers), &cbNeeded) && cbNeeded < sizeof(drivers))
		{
			TCHAR szDriver[DRIVER_MAX_COUNT];
			cDrivers = cbNeeded / sizeof(drivers[0]);

			for (unsigned int i = 0; i < cDrivers; i++)
			{
				if (GetDeviceDriverBaseName(drivers[i], szDriver, sizeof(szDriver)))
				{
					//_tprintf(TEXT("Driver[%d]: %s\n"), i + 1, szDriver);
				}
			}
		}
		return driverInformations;
	}
}