#include "VKConstanBuffer.h"
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
    VKConstantBuffer::VKConstantBuffer(const BufferDescription& desc, VKGraphicsDevice* device) : UniformBuffer(desc)
    {
        create(device);
    }

    VKConstantBuffer::~VKConstantBuffer()
    {

    }

    void VKConstantBuffer::create(VKGraphicsDevice* device)
    {
        VkBufferCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        createInfo.size = get_allocated_size();
        createInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        const VkResult createBufferVkR = vkCreateBuffer(device->get_vk_logical_device(), &createInfo, nullptr, &Buffer);
        ASSERT(createBufferVkR == VK_SUCCESS, "VKConstantBuffer", "Buffer creation failed!");
    }

}