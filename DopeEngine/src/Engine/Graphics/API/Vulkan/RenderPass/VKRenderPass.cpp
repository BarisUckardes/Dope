#include "VKRenderPass.h"
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Vulkan/Texture/VKTextureUtils.h>
#include <Engine/Graphics/Device/DeviceObjects.h>
#include <Engine/Graphics/API/Vulkan/Device/VKDeviceObjects.h>
#include <Engine/Graphics/API/Vulkan/RenderPass/VKRenderPassUtils.h>
#include <Engine/Graphics/Vertex/VertexUtils.h>
#include <Engine/Graphics/API/Vulkan/Shader/VKShader.h>
#include <Engine/Graphics/Framebuffer/Framebuffer.h>

namespace DopeEngine
{
	VKRenderPass::VKRenderPass(const RenderPassDesc& desc, VKGraphicsDevice* device) : RenderPass(desc)
	{
		create(device);
	}

	VKRenderPass::~VKRenderPass()
	{

	}

	VkPipelineLayout VKRenderPass::get_vk_pipeline_layout() const
	{
		return Layout;
	}

	VkPipeline VKRenderPass::get_vk_pipeline() const
	{
		return BasePipeline;
	}

	VkRenderPass VKRenderPass::get_vk_render_pass() const
	{
		return BaseRenderPass;
	}

	VkFramebuffer VKRenderPass::get_vk_ext_framebuffer() const
	{
		return ExtFramebuffer;
	}

	Array<VkFramebuffer> VKRenderPass::get_vk_swapchain_framebuffers() const
	{
		return SwapchainFramebuffers;
	}

	VkFramebuffer VKRenderPass::get_vk_swapchain_framebuffer(const unsigned int index) const
	{
		return SwapchainFramebuffers[index];
	}

	void VKRenderPass::create(VKGraphicsDevice* device)
	{
		/*
		* Create vertex input state
		*/
		VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = {};
		vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		Array<VkVertexInputAttributeDescription> vertexInputAttributeDescs;
		Array<VkVertexInputBindingDescription> vertexInputBindingDescs;
		const VertexLayoutDescription vertexLayoutDesc = get_vertex_layout();
		const Array<VertexElementDescription>& vertexLayoutElementDescs = vertexLayoutDesc.get_elements_fast();
		unsigned int currentOffset = 0;
		for (unsigned int i = 0; i < vertexLayoutElementDescs.get_cursor(); i++)
		{
			/*
			* Get element description
			*/
			const VertexElementDescription elementDesc = vertexLayoutElementDescs[i];

			/*
			* Create vertex input attribute desc
			*/
			VkVertexInputAttributeDescription attributeDesc = {};
			attributeDesc.binding = i;
			attributeDesc.format = VK_FORMAT_UNDEFINED; // will be changed
			attributeDesc.location = i;
			attributeDesc.offset = currentOffset; // will be changed

			/*
			* Create vertex input binding desc
			*/
			VkVertexInputBindingDescription bindingDesc = {};
			bindingDesc.binding = i;
			bindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; // should be adaptable
			bindingDesc.stride = vertexLayoutDesc.get_stride();

			/*
			* Register descs
			*/
			vertexInputAttributeDescs.add(attributeDesc);
			vertexInputBindingDescs.add(bindingDesc);

			/*
			* Increment offset
			*/
			currentOffset += VertexUtils::get_data_type_size(elementDesc.DataType);
		}
		vertexInputStateCreateInfo.vertexAttributeDescriptionCount = vertexInputAttributeDescs.get_cursor();
		vertexInputStateCreateInfo.pVertexAttributeDescriptions = vertexInputAttributeDescs.get_data();
		vertexInputStateCreateInfo.vertexBindingDescriptionCount = vertexInputBindingDescs.get_cursor();
		vertexInputStateCreateInfo.pVertexBindingDescriptions = vertexInputBindingDescs.get_data();

		/*
		* Create input assembler state
		*/
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {};
		inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssemblyStateCreateInfo.topology = VKRenderPassUtils::get_vk_primitive_topology(get_primitives()); // will be changed
		inputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;

		/*
		* Create rasterizer state
		*/
		VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
		rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizationStateCreateInfo.depthBiasEnable = false;
		rasterizationStateCreateInfo.depthClampEnable = false;
		rasterizationStateCreateInfo.rasterizerDiscardEnable = false; // default for Dope
		rasterizationStateCreateInfo.cullMode = VKRenderPassUtils::get_vk_cull_mode(get_cull_mode());
		rasterizationStateCreateInfo.frontFace = VKRenderPassUtils::get_vk_front_face(get_front_face());
		rasterizationStateCreateInfo.polygonMode = VKRenderPassUtils::get_vk_polygon_mode(get_fill_mode());
		rasterizationStateCreateInfo.lineWidth = 5.0f; // will be changed
		rasterizationStateCreateInfo.depthBiasConstantFactor = 0.0f; // Default for Dope
		rasterizationStateCreateInfo.depthBiasClamp = 0.0f; // Default for Dope
		rasterizationStateCreateInfo.depthBiasSlopeFactor = 0.0f; // Default for Dope

		/*
		* Create blending state
		*/
		VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo = {};
		colorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;

		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
		colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
		colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
		colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
		colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

		colorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
		colorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY; // Optional
		colorBlendStateCreateInfo.attachmentCount = 1;
		colorBlendStateCreateInfo.pAttachments = &colorBlendAttachment;
		colorBlendStateCreateInfo.blendConstants[0] = 0.0f; // Optional
		colorBlendStateCreateInfo.blendConstants[1] = 0.0f; // Optional
		colorBlendStateCreateInfo.blendConstants[2] = 0.0f; // Optional
		colorBlendStateCreateInfo.blendConstants[3] = 0.0f; // Optional

		/*
		* Create depth stencil state
		*/
		VkPipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo = {};
		depthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencilStateCreateInfo.depthTestEnable = is_depth_test_enabled() ? VK_TRUE : VK_FALSE;
		depthStencilStateCreateInfo.depthWriteEnable = is_depth_write_enabled() ? VK_TRUE : VK_FALSE;

		/*
		* Create multisample state
		*/
		VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};
		multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampleStateCreateInfo.sampleShadingEnable = VK_FALSE; // may be changed in the future
		multisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampleStateCreateInfo.minSampleShading = 1.0f; // may be changed in the future
		multisampleStateCreateInfo.pSampleMask = nullptr; // may be changed in the future
		multisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE; // may be changed in the future
		multisampleStateCreateInfo.alphaToOneEnable = VK_FALSE; // may be changed in the future

		/*
		* Create dynamic state
		*/
		VkDynamicState vkDefaultDynamicStates[] =
		{ VK_DYNAMIC_STATE_VIEWPORT,VK_DYNAMIC_STATE_SCISSOR };
		VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {};
		dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicStateCreateInfo.dynamicStateCount = 2;
		dynamicStateCreateInfo.pDynamicStates = vkDefaultDynamicStates; // default for Dope

		/*
		* Get target framebuffer properties
		*/
		const Framebuffer* targetFramebuffer = get_target_framebuffer();
		Array<TextureFormat> framebufferAttachmentFormats;
		if (targetFramebuffer->is_swapchain_framebuffer())
		{
			const SwapchainFramebuffer* swapchainFramebuffer = (const SwapchainFramebuffer*)targetFramebuffer;
			framebufferAttachmentFormats.add(swapchainFramebuffer->get_swapchain_buffer_format());
		}
		else
		{
			//framebufferAttachmentFormats = targetFramebuffer
		}

		/*
		* Create pipeline layout
		*/
		VkPipelineLayoutCreateInfo layoutCreateInfo = {};
		layoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		layoutCreateInfo.setLayoutCount = 0; // will be changed in the future
		layoutCreateInfo.pSetLayouts = nullptr; // will be changed in the future
		layoutCreateInfo.pushConstantRangeCount = 0; // will be changed in the future
		layoutCreateInfo.pPushConstantRanges = nullptr; // will be changed in the future

		/*
		* Create pipeline 
		*/
		const VkResult layoutCreateVkR = vkCreatePipelineLayout(device->get_vk_logical_device(), &layoutCreateInfo, nullptr,&Layout);

		/*
		* Validate layout creation
		*/
		ASSERT(layoutCreateVkR == VK_SUCCESS, "VKPipeline", "Pipeline layout creation failed!");

		/*
		* Create shader state
		*/
		const Array<Shader*>& shaders = get_shader_set();
		Array<VkPipelineShaderStageCreateInfo> pipelineShaderStageCreateInfos;
		pipelineShaderStageCreateInfos.reserve(shaders.get_cursor());
		for (unsigned int i = 0; i < shaders.get_cursor(); i++)
		{
			/*
			* Get shader
			*/
			const VKShader* shader =(const VKShader*)shaders[i];

			/*
			* Create pipeline shader stage create info
			*/
			VkPipelineShaderStageCreateInfo shaderStageCreateInfo = {};
			shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			shaderStageCreateInfo.module = shader->get_vk_shader_module();
			shaderStageCreateInfo.stage = VKRenderPassUtils::get_vk_shader_stage(shader->get_type());
			shaderStageCreateInfo.pName = "main";

			/*
			* Register
			*/
			pipelineShaderStageCreateInfos.add(shaderStageCreateInfo);
		}

		/*
		* Create render pass attachments
		*/
		const unsigned int colorAttachmentCount = framebufferAttachmentFormats.get_cursor();
		Array<VkAttachmentDescription> colorAttachmentDescs;
		Array<VkAttachmentReference> colorAttachmentReferences;
		colorAttachmentDescs.reserve(colorAttachmentCount);
		colorAttachmentReferences.reserve(colorAttachmentCount);
		for (unsigned int i = 0; i < colorAttachmentCount; i++)
		{
			/*
			* Create attachment desc
			*/
			VkAttachmentDescription attachmentDesc = {};
			attachmentDesc.samples = VK_SAMPLE_COUNT_1_BIT;
			attachmentDesc.format = VKTextureUtils::get_vk_format(framebufferAttachmentFormats[i]);
			attachmentDesc.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
			attachmentDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
			attachmentDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			attachmentDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			attachmentDesc.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			attachmentDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

			/*
			* Create color attachment reference
			*/
			VkAttachmentReference attachmentReference = {};
			attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
			attachmentReference.attachment = i;

			/*
			* Register attachment desc and reference
			*/
			colorAttachmentDescs.add(attachmentDesc);
			colorAttachmentReferences.add(attachmentReference);
		}

		/*
		* Create subpass desc
		*/
		VkSubpassDescription subpassDescription = {};
		subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpassDescription.colorAttachmentCount = colorAttachmentCount;
		subpassDescription.pColorAttachments = colorAttachmentReferences.get_data();

		/*
		* Create render pass create info
		*/
		VkRenderPassCreateInfo renderPassCreateInfo = {};
		renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassCreateInfo.attachmentCount = colorAttachmentCount;
		renderPassCreateInfo.pAttachments = colorAttachmentDescs.get_data();
		renderPassCreateInfo.subpassCount = 1; // default for DopeEngine
		renderPassCreateInfo.pSubpasses = &subpassDescription;

		/*
		* Create render pass
		*/
		const VkResult createRenderPassVkR = vkCreateRenderPass(device->get_vk_logical_device(), &renderPassCreateInfo, nullptr, &BaseRenderPass);

		/*
		* Validate render pass creation
		*/
		ASSERT(createRenderPassVkR == VK_SUCCESS, "VKPipeline", "Pipeline creation failed!");

		/*
		* Get attachment views
		*/
		if (targetFramebuffer->is_swapchain_framebuffer())
		{
			/*
			* Get vk swapchain framebuffer
			*/
			const VKSwapchainFramebuffer* vkSwapchainFramebuffer = (const VKSwapchainFramebuffer*)targetFramebuffer;

			/*
			* Set attachments
			*/
			const VkImageView swapchainMainImageView = vkSwapchainFramebuffer->get_vk_main_image_view();

			/*
			* Create framebuffer for each swapchain image
			*/
			for (unsigned int i = 0; i < vkSwapchainFramebuffer->get_swapchain_buffer_count(); i++)
			{
				/*
				* Create framebuffer create info
				*/
				VkFramebufferCreateInfo framebufferCreateInfo = {};
				framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
				framebufferCreateInfo.renderPass = BaseRenderPass;
				framebufferCreateInfo.attachmentCount = 1;
				framebufferCreateInfo.pAttachments = &swapchainMainImageView;
				framebufferCreateInfo.width = targetFramebuffer->get_width();
				framebufferCreateInfo.height = targetFramebuffer->get_height();
				framebufferCreateInfo.layers = 1; // default for swapchains in Dope

				/*
				* Create framebuffer
				*/
				VkFramebuffer vkFramebuffer = VK_NULL_HANDLE;
				const VkResult createFramebufferVkR = vkCreateFramebuffer(device->get_vk_logical_device(), &framebufferCreateInfo, nullptr, &vkFramebuffer);

				/*
				* Validate framebuffer creation
				*/
				ASSERT(createFramebufferVkR == VK_SUCCESS, "VKSwapchainFramebuffer", "Swapchainframebuffer creation failed!");

				/*
				* Register
				*/
				SwapchainFramebuffers.add(vkFramebuffer);
				LOG("VKRenderPass", "Created 1 framebuffer for swapchain");
			}
			
		}

		

		/*
		* Create pipeline create info
		*/
		const RenderPassType renderPassType = get_type();
		switch (renderPassType)
		{
			case RenderPassType::Graphics:
			{
				VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo = {};
				graphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
				graphicsPipelineCreateInfo.stageCount = 0; // will be changed
				graphicsPipelineCreateInfo.pStages = VK_NULL_HANDLE; // will be changed
				graphicsPipelineCreateInfo.pVertexInputState = &vertexInputStateCreateInfo;
				graphicsPipelineCreateInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;
				graphicsPipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
				graphicsPipelineCreateInfo.pColorBlendState = &colorBlendStateCreateInfo; // will be changed
				graphicsPipelineCreateInfo.pDepthStencilState = &depthStencilStateCreateInfo;
				graphicsPipelineCreateInfo.pMultisampleState = &multisampleStateCreateInfo;
				graphicsPipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;
				graphicsPipelineCreateInfo.pViewportState = VK_NULL_HANDLE; // viewport state is dynamic state as default in Dope
				graphicsPipelineCreateInfo.renderPass = BaseRenderPass;
				graphicsPipelineCreateInfo.subpass = 0;
				graphicsPipelineCreateInfo.layout = Layout;
				graphicsPipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
				graphicsPipelineCreateInfo.basePipelineIndex = -1;

				/*
				* Create pipeline
				*/
				const VkResult createGraphicsPipelineVkR = vkCreateGraphicsPipelines(device->get_vk_logical_device(), VK_NULL_HANDLE, 1, &graphicsPipelineCreateInfo, nullptr, &BasePipeline);

				/*
				* Validate graphics pipeline creation
				*/
				ASSERT(createGraphicsPipelineVkR == VK_SUCCESS, "VKPipeline", "Graphics pipeline creation failed!");

				break;
			}
			case RenderPassType::Compute:
				break;
		}


	}
}