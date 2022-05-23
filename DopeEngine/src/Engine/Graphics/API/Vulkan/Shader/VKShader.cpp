#include "VKShader.h"
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	VKShader::VKShader(const ShaderDescription& desc, VKGraphicsDevice* device) : Shader(desc)
	{
		create(device);
	}

	VKShader::~VKShader()
	{

	}

	VkShaderModule VKShader::get_vk_shader_module() const
	{
		return ShaderModule;
	}

	void VKShader::create(VKGraphicsDevice* device)
	{
		const String source = get_source();

		VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
		shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderModuleCreateInfo.flags = 0;
		shaderModuleCreateInfo.codeSize = source.get_cursor();
		shaderModuleCreateInfo.pCode = (const unsigned int*)source.get_source();

		const VkResult shaderModuleCreateVkR = vkCreateShaderModule(device->get_vk_logical_device(), &shaderModuleCreateInfo, nullptr,&ShaderModule);
		ASSERT(shaderModuleCreateVkR == VK_SUCCESS, "VKShader", "Cannot create shader module!");
	}

	void VKShader::compile()
	{
	}

}