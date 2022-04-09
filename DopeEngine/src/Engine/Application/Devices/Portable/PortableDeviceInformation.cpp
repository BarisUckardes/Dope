#include "PortableDeviceInformation.h"

namespace DopeEngine
{
	PortableDeviceInformation::PortableDeviceInformation(const String& manufacturer, const String& friendlyName, const String& description)
	{
		Manufacturer = manufacturer;
		FriendlyName = friendlyName;
		Description = description;
	}
	String PortableDeviceInformation::get_manufacturer() const
	{
		return Manufacturer;
	}
	String PortableDeviceInformation::get_friendly_name() const
	{
		return FriendlyName;
	}
	String PortableDeviceInformation::get_description() const
	{
		return Description;
	}
}