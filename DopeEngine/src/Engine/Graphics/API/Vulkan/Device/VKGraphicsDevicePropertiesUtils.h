#pragma once
#include <Engine/Graphics/Device/GraphicsDeviceProperties.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API VKGraphicsDevicePropertiesUtils
	{
	public:
		VKGraphicsDevicePropertiesUtils() = delete;
		~VKGraphicsDevicePropertiesUtils() = delete;

		static String get_vk_vendor_name(const unsigned int vendorID);
	};
}