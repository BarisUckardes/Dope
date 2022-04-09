#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Array.h>
#include <Engine/Application/Devices/Drivers/DeviceDriverInformation.h>

namespace DopeEngine
{
	/// <summary>
	/// Device driver enumarator abstraction class
	/// </summary>
	class DOPE_ENGINE_API IDeviceDriverEnumarator
	{
	public:
		static IDeviceDriverEnumarator* create();

		IDeviceDriverEnumarator() = default;
		~IDeviceDriverEnumarator() = default;

		/// <summary>
		/// Returns the enumarated drivers
		/// </summary>
		/// <returns></returns>
		virtual Array<DeviceDriverInformation> enumarate_drivers() = 0;
	};


}