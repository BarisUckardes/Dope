#include "DeviceDriverInformation.h"

namespace DopeEngine
{
	DeviceDriverInformation::DeviceDriverInformation(const String& baseName)
	{
		BaseName = baseName;
	}
	String DeviceDriverInformation::get_base_name() const
	{
		return BaseName;
	}
}