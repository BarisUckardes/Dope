#include "VKCommandBuffer.h"
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <Engine/Graphics/API/Vulkan/Device/VKDeviceObjects.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Vulkan/RenderPass/VKRenderPassUtils.h>

namespace DopeEngine
{
	VKCommandBuffer::VKCommandBuffer(VKGraphicsDevice* device)
	{
		create(device);
	}
	VKCommandBuffer::~VKCommandBuffer()
	{

	}
	VkCommandBuffer VKCommandBuffer::get_vk_command_buffer() const
	{
		return BaseCommandBuffer;
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

		/*
		* Reset command buffer
		*/
		//const VkResult resetVkR = vkResetCommandBuffer(BaseCommandBuffer, 0);

		/*
		* Validate reset
		*/
		//ASSERT(resetVkR == VK_SUCCESS, "VKCommandBuffer", "Couldnt reset the command buffer");
	}

	void VKCommandBuffer::unlock_impl()
	{
		/*
		* End command buffer
		*/
		vkEndCommandBuffer(BaseCommandBuffer);
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
	void VKCommandBuffer::start_render_pass_impl(const RenderPass* renderPass)
	{
		/*
		* Get VK render pass
		*/
		const VKRenderPass* vkRenderPass = (const VKRenderPass*)renderPass;
		
		/*
		* Get render pass framebuffer
		*/
		const Framebuffer* targetFramebuffer = vkRenderPass->get_target_framebuffer();

		/*
		* Catch framebuffer type
		*/
		VkFramebuffer vkFramebuffer = VK_NULL_HANDLE;
		if (targetFramebuffer->is_swapchain_framebuffer())
		{
			/*
			* Get vk swapchain framebuffer
			*/
			const VKSwapchainFramebuffer* vkSwapchainFramebuffer = (const VKSwapchainFramebuffer*)targetFramebuffer;
			vkFramebuffer = vkRenderPass->get_vk_swapchain_framebuffer(vkSwapchainFramebuffer->get_vk_current_swapchain_image_index());
		}
		else
		{

		}

		/*
		* Get viewport&scissors desc
		*/
		const ViewportDesc viewportDesc = renderPass->get_viewport_desc();
		const ScissorsDesc scissorsDesc = renderPass->get_scissors_desc();

		/*
		* Set render pass begin info
		*/
		const VkClearValue vkClearValue = { 1.0f,0,0,1.0f };
		renderPassBeginInfo = {};
		renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassBeginInfo.renderPass = vkRenderPass->get_vk_render_pass();
		renderPassBeginInfo.framebuffer = vkFramebuffer; 
		renderPassBeginInfo.renderArea.offset = { (int)viewportDesc.OffsetX,(int)viewportDesc.OffsetY };
		renderPassBeginInfo.renderArea.extent = { viewportDesc.Width,viewportDesc.Height };
		renderPassBeginInfo.clearValueCount = 0;
		renderPassBeginInfo.pClearValues = VK_NULL_HANDLE;

		/*
		* Begin render pass
		*/
		vkCmdBeginRenderPass(BaseCommandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

		/*
		* Bind pipeline
		*/
		const VkPipelineBindPoint bindPoint = VKRenderPassUtils::get_vk_pipeline_type(vkRenderPass->get_type());
		const VkPipeline pipeline = vkRenderPass->get_vk_pipeline();
		//vkCmdBindPipeline(BaseCommandBuffer, bindPoint, pipeline);
	}

	void VKCommandBuffer::clear_color_impl(const ColorRgbaByte& color)
	{
		/*
		* Create vk clear color
		*/
		VkClearValue vkClearValue = { color.Red,color.Green,color.Blue,color.Alpha };

		/*
		* Create clear rect
		*/
		const ViewportDesc viewportDesc = get_bound_render_pass()->get_viewport_desc();
		const VkClearRect vkClearRect = { {viewportDesc.OffsetX,viewportDesc.OffsetY},viewportDesc.Width,viewportDesc.Height };

		/*
		* Get framebuffer
		*/
		const Framebuffer* boundFramebuffer = get_bound_render_pass()->get_target_framebuffer();

		/*
		* Create vk clear attachments
		*/
		const unsigned int clearAttachmentCount = boundFramebuffer->is_swapchain_framebuffer() ? 1 : boundFramebuffer->get_attachments_fast().get_cursor();
		Array<VkClearAttachment> vkClearAttachments;
		for (unsigned int i = 0;i< clearAttachmentCount; i++)
		{
			/*
			* Create vk clear attachment
			*/
			VkClearAttachment clearAttachment = {};
			clearAttachment.aspectMask = 0;
			clearAttachment.clearValue = vkClearValue;
			clearAttachment.colorAttachment = i;

			/*
			* register vk clear attachment
			*/
			vkClearAttachments.add(clearAttachment);
		}
		

		/*
		* Set clear attachments
		*/
		vkCmdClearAttachments(BaseCommandBuffer,vkClearAttachments.get_cursor(),vkClearAttachments.get_data(),1,&vkClearRect);
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