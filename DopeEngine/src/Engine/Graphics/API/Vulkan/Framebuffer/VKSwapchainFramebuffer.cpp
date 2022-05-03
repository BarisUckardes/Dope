#include "VKSwapchainFramebuffer.h"
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <VULKAN/vulkan_win32.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Vulkan/Texture/VKTextureUtils.h>
#include <Engine/Math/Math.h>

namespace DopeEngine
{
	VKSwapchainFramebuffer::VKSwapchainFramebuffer(const SwapchainFramebufferDesc& desc, VKGraphicsDevice* device, Window* targetWindow) : SwapchainFramebuffer(desc,(GraphicsDevice*)device,targetWindow)
	{
		create(device, targetWindow);
	}

	VKSwapchainFramebuffer::~VKSwapchainFramebuffer()
	{

	}

	void VKSwapchainFramebuffer::on_swapchain_resize_impl()
	{

	}

	void VKSwapchainFramebuffer::create(VKGraphicsDevice* device, Window* window)
	{
#ifdef DOPE_OS_WINDOWS
		create_win32(device, window);
#endif	
	}

	void VKSwapchainFramebuffer::create_win32(VKGraphicsDevice* device, Window* window)
	{
		/*
		* Get device features
		*/
		const GraphicsDeviceFeatures* supportedFeatures = device->get_supported_features();

		/*
		* Create win32 surface creation
		*/
		VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceCreateInfo.hwnd = window->get_win32_window_handle();
		surfaceCreateInfo.hinstance = GetModuleHandleA(nullptr);

		/*
		* Create win32 surface
		*/
		const VkResult surfaceCreateVkR = vkCreateWin32SurfaceKHR(device->get_vk_instance(), &surfaceCreateInfo, nullptr,&Surface);

		/*
		* Validate surface creation
		*/
		ASSERT(surfaceCreateVkR == VK_SUCCESS, "VKSwapchainFramebuffer", "Win32 surface creation failed!");

		/*
		* Get physical device surface capabilities
		*/
		VkSurfaceCapabilitiesKHR surfaceCapabilities = {};
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->get_vk_physicalDevice(), Surface, &surfaceCapabilities);

		/*
		* Get surface formats
		*/
		unsigned int surfaceFormatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device->get_vk_physicalDevice(),Surface,&surfaceFormatCount,nullptr);
		VkSurfaceFormatKHR* surfaceFormats = new VkSurfaceFormatKHR[surfaceFormatCount];

		/*
		* Iterate formats
		*/
		for (unsigned int i = 0; i < surfaceFormatCount; i++)
		{
			/*
			* Get format
			*/
			const VkSurfaceFormatKHR surfaceFormat = surfaceFormats[i];
		}

		/*
		* Get present modes
		*/
		unsigned int presentModeCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device->get_vk_physicalDevice(), Surface, &presentModeCount, nullptr);
		VkPresentModeKHR* presentModes = new VkPresentModeKHR[presentModeCount];
		vkGetPhysicalDeviceSurfacePresentModesKHR(device->get_vk_physicalDevice(), Surface, &presentModeCount, nullptr);

		/*
		* Iterate present modes
		*/
		for (unsigned int i = 0; i < presentModeCount; i++)
		{
			/*
			* Get present mode
			*/
			const VkPresentModeKHR presentMode = presentModes[i];

		}

		/*
		* Create surface
		*/
		VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
		swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // might change this in the future for dept stencil buffers
		swapchainCreateInfo.imageFormat = VKTextureUtils::get_vk_format(get_swapchain_buffer_format());
		swapchainCreateInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR; // might change this in the future
		swapchainCreateInfo.imageExtent.width = Math::clamp(get_width(), surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width);
		swapchainCreateInfo.imageExtent.height = Math::clamp(get_height(), surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height);
		swapchainCreateInfo.minImageCount = get_swapchain_buffer_count();
		swapchainCreateInfo.imageArrayLayers = 1;
		swapchainCreateInfo.preTransform = surfaceCapabilities.currentTransform;
		swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapchainCreateInfo.clipped = VK_TRUE;
		swapchainCreateInfo.presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR; // Default in dopeengine
		swapchainCreateInfo.surface = Surface;
		swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; // Default in DopeEngine
		swapchainCreateInfo.queueFamilyIndexCount = 0;
		swapchainCreateInfo.pQueueFamilyIndices = nullptr;

		/*
		* Create swapchain
		*/
		const VkResult swapchainCreateVkR = vkCreateSwapchainKHR(device->get_vk_logical_device(), &swapchainCreateInfo, nullptr, &Swapchain);

		/*
		* Validate swapchain create
		*/
		LOG("VKSwapchainFramebuffer", "Swapchain status: %d", swapchainCreateVkR);
		ASSERT(swapchainCreateVkR == VK_SUCCESS, "VKSwapchainFramebuffer", "Cannot create swapchain");

		/*
		* Get swapchain images
		*/
		unsigned int swapchainImageCount = 0;
		vkGetSwapchainImagesKHR(device->get_vk_logical_device(),Swapchain,&swapchainImageCount,nullptr);
		VkImage* swapchainImages = new VkImage[swapchainImageCount];
		vkGetSwapchainImagesKHR(device->get_vk_logical_device(), Swapchain, &swapchainImageCount, swapchainImages);

		/*
		* Validate image count
		*/
		ASSERT(get_swapchain_buffer_count() == swapchainImageCount, "VKSwapchainFramebuffer", "Requested %d buffers for swapchain but given is %d", get_swapchain_buffer_count(), swapchainImageCount);

		/*
		* Create image views
		*/
		Array<VkImageView> swapchainImageViews;
		swapchainImageViews.reserve(swapchainImageCount);
		for (unsigned int i = 0; i < swapchainImageCount; i++)
		{
			/*
			* Create image view create info
			*/
			VkImageViewCreateInfo imageViewCreateInfo = {};
			imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			imageViewCreateInfo.image = swapchainImages[i];
			imageViewCreateInfo.format = VKTextureUtils::get_vk_format(get_swapchain_buffer_format());
			imageViewCreateInfo.viewType = VKTextureUtils::get_vk_image_view_type(TextureType::Texture2D);

			VkImageSubresourceRange subresourceRange = { };
			subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			subresourceRange.baseArrayLayer = 0;
			subresourceRange.baseMipLevel = 0;
			subresourceRange.layerCount = 1;
			subresourceRange.levelCount = 1;
			imageViewCreateInfo.subresourceRange = subresourceRange;

			VkComponentMapping componentMapping = {}; // may change in future
			componentMapping.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			componentMapping.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			componentMapping.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			componentMapping.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			imageViewCreateInfo.components = componentMapping;

			/*
			* Create image view
			*/
			VkImageView imageView = {};
			const VkResult createImageViewVkR = vkCreateImageView(device->get_vk_logical_device(), &imageViewCreateInfo, nullptr, &imageView);

			/*
			* Validate create image view
			*/
			ASSERT(createImageViewVkR == VK_SUCCESS, "VKSwapchainFramebuffer", "Cannot create the swapchain image view!");

			/*
			* Register view
			*/
			swapchainImageViews.add(imageView);
		}
	}

}