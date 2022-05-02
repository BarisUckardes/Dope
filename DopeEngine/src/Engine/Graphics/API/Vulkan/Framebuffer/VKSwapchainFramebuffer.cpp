#include "VKSwapchainFramebuffer.h"
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <VULKAN/vulkan_win32.h>
#include <Engine/Core/Assert.h>

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
	}

}