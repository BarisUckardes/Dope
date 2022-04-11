#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Array.h>
#include <Engine/Application/Devices/Drivers/DeviceDriverInformation.h>

namespace DopeEngine
{
	/// <summary>
	/// Windows implementation of a DeviceDriverEnumarator
	/// </summary>
	class DOPE_ENGINE_API WindowsDriverEnumarator final
	{
	public:
		WindowsDriverEnumarator() = default;
		~WindowsDriverEnumarator() = default;

		// Inherited via IDeviceDriverEnumarator
		Array<DeviceDriverInformation> enumarate_drivers();
	};


}