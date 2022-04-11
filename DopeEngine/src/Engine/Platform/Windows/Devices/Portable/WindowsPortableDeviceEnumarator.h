#pragma once
#include <Engine/Application/Devices/Portable/PortableDeviceInformation.h>
#include <Engine/Structures/Array.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API WindowsPortableDeviceEnumarator final
	{
	public:
		WindowsPortableDeviceEnumarator() = default;
		~WindowsPortableDeviceEnumarator() = default;

		// Inherited via IPortableDeviceManager
		Array<PortableDeviceInformation> enumarate_devices() const;
	};


}