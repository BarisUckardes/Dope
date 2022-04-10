#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Array.h>
#include <Engine/Application/Devices/Portable/PortableDeviceInformation.h>
namespace DopeEngine
{
	/// <summary>
	/// An interface for the protable device enumarator
	/// </summary>
	class DOPE_ENGINE_API IPortableDeviceEnumarator
	{
	public:
		static IPortableDeviceEnumarator* create();
		IPortableDeviceEnumarator() = default;
		~IPortableDeviceEnumarator() = default;

		/// <summary>
		/// Enumarates and returns the list of currently connected portable devices
		/// </summary>
		/// <returns></returns>
		virtual Array<PortableDeviceInformation> enumarate_devices() const = 0;
	};

}
