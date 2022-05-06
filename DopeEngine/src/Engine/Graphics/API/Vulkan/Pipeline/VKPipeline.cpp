#include "VKPipeline.h"
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Vulkan/Texture/VKTextureUtils.h>
#include <Engine/Graphics/Device/DeviceObjects.h>

namespace DopeEngine
{
	VKPipeline::VKPipeline(const PipelineDescription& desc, VKGraphicsDevice* device) : Pipeline(desc)
	{
		create(device);
	}

	VKPipeline::~VKPipeline()
	{

	}

	VkPipelineLayout VKPipeline::get_vk_pipeline_layout() const
	{
		return Layout;
	}

	void VKPipeline::create(VKGraphicsDevice* device)
	{
		/*
		* Create vertex input state
		*/
		VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo = {};
		vertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		
		/*
		* Create input assembler state
		*/
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = {};
		inputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;

		/*
		* Create rasterizer state
		*/
		VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo = {};
		rasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		
		/*
		* Create blending state
		*/
		VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo = {};
		colorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;

		/*
		* Create depth stencil state
		*/
		VkPipelineDepthStencilStateCreateInfo depthStencilStateCreateInfo = {};
		depthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;

		/*
		* Create multisample state
		*/
		VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo = {};
		multisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;

		/*
		* Create dynamic state
		*/
		VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {};
		dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;

		/*
		* Create viewport and scissors
		*/
		VkPipelineViewportStateCreateInfo viewportStateCreateInfo = {};
		viewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

		/*
		* Create pipeline layout
		*/
		VkPipelineLayoutCreateInfo layoutCreateInfo = {};
		layoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

		/*
		* Create pipeline 
		*/
		const VkResult layoutCreateVkR = vkCreatePipelineLayout(device->get_vk_logical_device(), &layoutCreateInfo, nullptr,&Layout);

		/*
		* Validate layout creation
		*/
		ASSERT(layoutCreateVkR == VK_SUCCESS, "VKPipeline", "Pipeline layout creation failed!");

		/*
		* Create render pass attachments
		*/
		const OutputDescription outputDesc = get_output_desc();
		const unsigned int colorAttachmentCount = outputDesc.OutputFormats.get_cursor();
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
			attachmentDesc.format = VKTextureUtils::get_vk_format(outputDesc.OutputFormats[i]);
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
		const VkResult createRenderPassVkR = vkCreateRenderPass(device->get_vk_logical_device(), &renderPassCreateInfo, nullptr, &RenderPass);

		/*
		* Validate render pass creation
		*/
		ASSERT(createRenderPassVkR == VK_SUCCESS, "VKPipeline", "Pipeline creation failed!");
		
		/*
		* Create shader state
		*/
		const Array<Shader*>& shaders = get_shader_set()->get_shaders_fast();
		Array<VkPipelineShaderStageCreateInfo> pipelineShaderStageCreateInfos;
		pipelineShaderStageCreateInfos.reserve(shaders.get_cursor());
		for (unsigned int i = 0; i < shaders.get_cursor(); i++)
		{
			/*
			* Get shader
			*/
			const Shader* shader = shaders[i];

			/*
			* Create pipeline shader stage create info
			*/
			VkPipelineShaderStageCreateInfo shaderStageCreateInfo = {};
			shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;

			/*
			* Register
			*/
			pipelineShaderStageCreateInfos.add(shaderStageCreateInfo);
		}

		/*
		* Create pipeline create info
		*/
		const PipelineType pipelineType = get_type();
		switch (pipelineType)
		{
			case DopeEngine::PipelineType::Graphics:
			{
				VkGraphicsPipelineCreateInfo graphicsPipelineCreateInfo = {};
				graphicsPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
				graphicsPipelineCreateInfo.stageCount = shaders.get_cursor();
				graphicsPipelineCreateInfo.pStages = pipelineShaderStageCreateInfos.get_data();
				graphicsPipelineCreateInfo.pVertexInputState = &vertexInputStateCreateInfo;
				graphicsPipelineCreateInfo.pInputAssemblyState = &inputAssemblyStateCreateInfo;
				graphicsPipelineCreateInfo.pRasterizationState = &rasterizationStateCreateInfo;
				graphicsPipelineCreateInfo.pColorBlendState = &colorBlendStateCreateInfo;
				graphicsPipelineCreateInfo.pDepthStencilState = &depthStencilStateCreateInfo;
				graphicsPipelineCreateInfo.pMultisampleState = &multisampleStateCreateInfo;
				graphicsPipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;
				graphicsPipelineCreateInfo.pViewportState = &viewportStateCreateInfo;
				graphicsPipelineCreateInfo.renderPass = RenderPass;
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
			case DopeEngine::PipelineType::Compute:
				break;
		}

	}
}