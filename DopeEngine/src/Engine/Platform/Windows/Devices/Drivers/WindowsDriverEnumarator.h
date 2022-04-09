#pragma once
#include <Engine/Application/Devices/Drivers/IDeviceDriverEnumarator.h>

namespace DopeEngine
{
	/// <summary>
	/// Windows implementation of a DeviceDriverEnumarator
	/// </summary>
	class DOPE_ENGINE_API WindowsDriverEnumarator : public IDeviceDriverEnumarator
	{
	public:
		WindowsDriverEnumarator() = default;
		~WindowsDriverEnumarator() = default;

		// Inherited via IDeviceDriverEnumarator
		virtual Array<DeviceDriverInformation> enumarate_drivers() override;
	};


}