#include "VKSwapchainFramebuffer.h"
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <VULKAN/vulkan_win32.h>
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Vulkan/Texture/VKTextureFormatUtils.h>
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
		surfaceCreateInfo.hinstance = GetModuleHandle(nullptr);

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
		swapchainCreateInfo.imageFormat = VKTextureFormatUtils::get_vk_format(get_swapchain_buffer_format());
		swapchainCreateInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		swapchainCreateInfo.imageExtent.width = Math::clamp(get_width(), surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width);
		swapchainCreateInfo.imageExtent.height = Math::clamp(get_height(), surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height);
		swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchainCreateInfo.minImageCount = get_swapchain_buffer_count();
		swapchainCreateInfo.imageArrayLayers = 1;
		swapchainCreateInfo.preTransform = surfaceCapabilities.currentTransform;
		swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapchainCreateInfo.clipped = VK_TRUE;

		/*
		* We might want to change this in near future
		*/
		swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapchainCreateInfo.queueFamilyIndexCount = 0; 
		swapchainCreateInfo.pQueueFamilyIndices = nullptr; 

		/*
		* Create swapchain
		*/
		const VkResult swapchainCreateVkR = vkCreateSwapchainKHR(device->get_vk_logical_device(), &swapchainCreateInfo, nullptr, &Swapchain);

		/*
		* Validate swapchain create
		*/
		ASSERT(swapchainCreateVkR == VK_SUCCESS, "VKSwapchainFramebuffer", "Cannot create swapchain");
	}

}