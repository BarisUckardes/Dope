#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>

namespace DopeEngine
{
	/// <summary>
	/// Hold's the descriptive device information
	/// </summary>
	class DOPE_ENGINE_API PortableDeviceInformation final

	{
	public:
		PortableDeviceInformation(const String& manufacturer,const String& friendlyName,const String& description);
		PortableDeviceInformation() = default;
		~PortableDeviceInformation() = default;

		/// <summary>
		/// Returns the manufacturer name
		/// </summary>
		/// <returns></returns>
		 String get_manufacturer() const;

		/// <summary>
		/// Returns the device friendly name
		/// </summary>
		/// <returns></returns>
		 String get_friendly_name() const;

		/// <summary>
		/// Returns the description of the device
		/// </summary>
		/// <returns></returns>
		 String get_description() const;
	private:
		String Manufacturer;
		String FriendlyName;
		String Description;
	};


}