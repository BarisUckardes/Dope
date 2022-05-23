#include "VKIndexBuffer.h"
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
    VKIndexBuffer::VKIndexBuffer(const BufferDescription& desc, VKGraphicsDevice* device) : IndexBuffer(desc)
    {
        create(device);
    }

    VKIndexBuffer::~VKIndexBuffer()
    {

    }

    void VKIndexBuffer::create(VKGraphicsDevice* device)
    {
        VkBufferCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        createInfo.size = get_allocated_size();
        createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        
        const VkResult createBufferVkR = vkCreateBuffer(device->get_vk_logical_device(), &createInfo, nullptr, &Buffer);
        ASSERT(createBufferVkR == VK_SUCCESS, "VKIndexBuffer", "Buffer creation failed!");
    }

}