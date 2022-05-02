#pragma once
#include <Engine/Graphics/Device/GraphicsDeviceFeatures.h>
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDeviceFeaturesDesc.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API VKGraphicsDeviceFeatures : public GraphicsDeviceFeatures
	{
	public:
		VKGraphicsDeviceFeatures(const VKGraphicsDeviceFeaturesDesc& vkDesc, const GraphicsDeviceFeaturesDesc& baseDesc);
		~VKGraphicsDeviceFeatures() = default;

		FORCEINLINE Array<VkQueueFlags> get_vk_queues() const;
	private:
		Array<VkQueueFlags> Queues;
	};


}