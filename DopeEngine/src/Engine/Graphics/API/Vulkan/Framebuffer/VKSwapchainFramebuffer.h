#pragma once
#include <Engine/Graphics/API/Vulkan/Core/VKCore.h>
#include <Engine/Graphics/Framebuffer/SwapchainFramebuffer.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API VKSwapchainFramebuffer : public SwapchainFramebuffer
	{
	public:
		VKSwapchainFramebuffer(const SwapchainFramebufferDesc& desc, VKGraphicsDevice* device, Window* targetWindow);
		virtual ~VKSwapchainFramebuffer() override;


		FORCEINLINE VkImageView get_vk_main_image_view() const;
		FORCEINLINE VkSwapchainKHR get_vk_swapchain() const;
		FORCEINLINE unsigned int get_vk_current_swapchain_image_index() const;
		FORCEINLINE void increment_vk_swapchain_image_index();
	protected:
		// Inherited via SwapchainFramebuffer
		virtual void on_swapchain_resize_impl() override;
	private:
		void create(VKGraphicsDevice* device,Window* window);
		void create_win32(VKGraphicsDevice* device, Window* window);
	private:
		VkSurfaceKHR Surface;
		VkSwapchainKHR Swapchain;
		Array<VkImageView> ImageViews;
		unsigned int ImageIndex;
	};


}