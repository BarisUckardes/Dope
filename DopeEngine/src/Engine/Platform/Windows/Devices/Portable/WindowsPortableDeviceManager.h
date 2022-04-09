#pragma once
#include <Engine/Application/Devices/Portable/IPortableDeviceEnumarator.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API WindowsPortableDeviceManager : public IPortableDeviceEnumarator
	{
	public:
		WindowsPortableDeviceManager() = default;
		~WindowsPortableDeviceManager() = default;

		// Inherited via IPortableDeviceManager
		virtual Array<PortableDeviceInformation> enumarate_devices() const override;
	};


}