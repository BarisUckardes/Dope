#include "VKGraphicsDeviceFeatures.h"

namespace DopeEngine
{
	VKGraphicsDeviceFeatures::VKGraphicsDeviceFeatures(const VKGraphicsDeviceFeaturesDesc& vkDesc, const GraphicsDeviceFeaturesDesc& baseDesc) : GraphicsDeviceFeatures(baseDesc)
	{
		Queues = vkDesc.Queues;
	}

	Array<VkQueueFlags> VKGraphicsDeviceFeatures::get_vk_queues() const
	{
		return Queues;
	}

}