#include "VKVertexBuffer.h"
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	VKVertexBuffer::VKVertexBuffer(const BufferDescription& desc, VKGraphicsDevice* device) : VertexBuffer(desc)
	{
		create(device);
	}

	VKVertexBuffer::~VKVertexBuffer()
	{

	}

	VkBuffer VKVertexBuffer::get_vk_vertex_buffer() const
	{
		return Buffer;
	}

	void VKVertexBuffer::create(VKGraphicsDevice* device)
	{
		/*
		* Create buffer create info
		*/
		VkBufferCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		createInfo.size = get_allocated_size();
		createInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		/*
		* Create buffer
		*/
		const VkResult createBufferVkR = vkCreateBuffer(device->get_vk_logical_device(), &createInfo, nullptr,&Buffer);

		/*
		* Validate buffer creation
		*/
		ASSERT(createBufferVkR == VK_SUCCESS, "VKVertexBuffer", "Buffer creation failed!");
	}

}