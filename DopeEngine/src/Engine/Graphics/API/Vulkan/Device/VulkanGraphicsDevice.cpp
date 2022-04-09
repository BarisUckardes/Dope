#include "VulkanGraphicsDevice.h"
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
    VulkanGraphicsDevice::VulkanGraphicsDevice(Window* ownerWindow) : GraphicsDevice(ownerWindow)
    {
        _create_vulkan_device();
    }
    GraphicsAPIType VulkanGraphicsDevice::get_api_type() const
    {
        return GraphicsAPIType::Vulkan;
    }
    String VulkanGraphicsDevice::get_version() const
    {
        return "Not implemented yet";
    }
    void VulkanGraphicsDevice::make_current_impl()
    {

    }
    void VulkanGraphicsDevice::_create_vulkan_device()
    {
#ifdef DOPE_OS_WINDOWS
        _create_win32_vulkan_device();
#endif
    }
    void VulkanGraphicsDevice::_create_win32_vulkan_device()
    {
        ASSERT(false, "VulkanGraphicsDevice", "Not implemented yet");
    }
}