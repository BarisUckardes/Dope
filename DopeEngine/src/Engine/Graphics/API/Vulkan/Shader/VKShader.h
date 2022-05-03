#pragma once
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Shader/Shader.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API VKShader : public Shader
	{
	public:
		VKShader(const ShaderDescription& desc,VKGraphicsDevice* device);
		virtual ~VKShader() override;

		FORCEINLINE VkShaderModule get_vk_shader_module() const;
	private:
		void create(VKGraphicsDevice* device);
	private:
		VkShaderModule ShaderModule;
	};


}