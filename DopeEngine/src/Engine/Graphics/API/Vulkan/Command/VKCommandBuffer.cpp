#include "VKCommandBuffer.h"
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <Engine/Graphics/API/Vulkan/Device/VKDeviceObjects.h>
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	VKCommandBuffer::VKCommandBuffer(VKGraphicsDevice* device)
	{
		create(device);
	}
	VKCommandBuffer::~VKCommandBuffer()
	{

	}
	void VKCommandBuffer::lock_impl()
	{
		/*
		* Create begin info
		*/
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.pInheritanceInfo = nullptr; // may change in the future
		beginInfo.flags = 0;

		/*
		* Begin command buffer
		*/
		const VkResult beginVkR = vkBeginCommandBuffer(BaseCommandBuffer, &beginInfo);

		/*
		* Validate begin
		*/
		ASSERT(beginVkR == VK_SUCCESS, "VKCommandBuffer", "Couldnt start the command buffer!");
	}

	void VKCommandBuffer::unlock_impl()
	{

	}

	void VKCommandBuffer::clear_cached_state_impl()
	{

	}

	void VKCommandBuffer::set_vertex_buffer_impl(const VertexBuffer* vertexBuffer)
	{

	}

	void VKCommandBuffer::set_index_buffer_impl(const IndexBuffer* indexBuffer)
	{

	}

	void VKCommandBuffer::set_uniform_buffer_impl(const UniformBuffer* buffer)
	{

	}
	void VKCommandBuffer::set_pipeline_impl(const Pipeline* pipeline)
	{

	}

	void VKCommandBuffer::clear_color_impl(const ColorRgbaByte& color)
	{

	}

	void VKCommandBuffer::clear_depth_impl(const float depth)
	{

	}

	void VKCommandBuffer::set_resource_view_impl(const unsigned int slot, const ResourceView* view)
	{

	}

	void VKCommandBuffer::indexed_draw_call_impl(const unsigned int count)
	{

	}

	void VKCommandBuffer::create(VKGraphicsDevice* device)
	{
		/*
		* Create command buffer allocate  info
		*/
		VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.commandPool = device->get_vk_command_pool();
		commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandBufferAllocateInfo.commandBufferCount = 1;

		/*
		* Create command buffer
		*/
		const VkResult createCommandBuffer = vkAllocateCommandBuffers(device->get_vk_logical_device(), &commandBufferAllocateInfo, &BaseCommandBuffer);

		/*
		* Validate command buffer creation
		*/
		ASSERT(createCommandBuffer == VK_SUCCESS, "VKCommandBuffer", "Creating CommandBuffer failed!");
	}

}