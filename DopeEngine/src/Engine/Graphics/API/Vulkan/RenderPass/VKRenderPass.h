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
		FORCEINLINE VkPipeline get_vk_pipeline() const;
		FORCEINLINE VkRenderPass get_vk_render_pass() const;
		FORCEINLINE VkFramebuffer get_vk_ext_framebuffer() const;
		FORCEINLINE Array<VkFramebuffer> get_vk_swapchain_framebuffers() const;
		FORCEINLINE VkFramebuffer get_vk_swapchain_framebuffer(const unsigned int index) const;
	private:
		void create(VKGraphicsDevice* device);
	private:
		VkPipelineLayout Layout;
		VkPipeline BasePipeline;
		VkRenderPass BaseRenderPass;
		Array<VkFramebuffer> SwapchainFramebuffers;
		VkFramebuffer ExtFramebuffer;
	};
}