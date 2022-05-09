#pragma once
#include <Engine/Graphics/RenderPass/RenderPass.h>
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API VKRenderPass : public RenderPass
	{
	public:
		VKRenderPass(const RenderPassDesc& desc, VKGraphicsDevice* device);
		virtual ~VKRenderPass() override;

		FORCEINLINE VkPipelineLayout get_vk_pipeline_layout() const;
		FORCEINLINE VkRenderPass get_vk_render_pass() const;
	private:
		void create(VKGraphicsDevice* device);
	private:
		VkPipelineLayout Layout;
		VkPipeline BasePipeline;
		VkRenderPass BaseRenderPass;
		VkFramebuffer BaseFramebuffer;
	};
}