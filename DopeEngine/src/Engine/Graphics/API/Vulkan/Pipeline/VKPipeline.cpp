#include "VKPipeline.h"
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <Engine/Core/Assert.h>

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
		VkPipelineDepthStencilStateCreateInfo deptStencilStateCreateInfo = {};
		deptStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;

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
	}
}