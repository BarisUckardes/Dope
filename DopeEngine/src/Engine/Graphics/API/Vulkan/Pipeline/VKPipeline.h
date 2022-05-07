#pragma once
#include <Engine/Graphics/Pipeline/Pipeline.h>
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API VKPipeline : public Pipeline
	{
	public:
		VKPipeline(const PipelineDescription& desc, VKGraphicsDevice* device);
		virtual ~VKPipeline() override;

		FORCEINLINE VkPipelineLayout get_vk_pipeline_layout() const;
	private:
		void create(VKGraphicsDevice* device);
	private:
		VkPipelineLayout Layout;
		VkPipeline BasePipeline;
		VkRenderPass RenderPass;
		VkFramebuffer BaseFramebuffer;
	};
}