#include "VKGraphicsDevicePropertiesUtils.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	inline String VKGraphicsDevicePropertiesUtils::get_vk_vendor_name(const unsigned int vendorID)
	{
		switch (vendorID)
		{
			case 0x1002:
				return "AMD";
				break;
			case 0x1010:
				return "ImgTec";
				break;
			case 0x10DE:
				return "NVIDIA";
				break;
			case 0x13B5:
				return "Arm";
				break;
			case 0x5143:
				return "Qualcomm";
				break;
			case 0x8086:
				return "INTEL";
				break;
			default:
				ASSERT(false, "VKGraphicsDeviceUtils", "Invalid vendorID, cannot produce vendor name out of the vendorID");
				break;
		}
	}

}