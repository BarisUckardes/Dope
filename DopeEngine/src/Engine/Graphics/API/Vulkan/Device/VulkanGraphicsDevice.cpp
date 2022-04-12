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
    CommandBuffer* VulkanGraphicsDevice::create_command_buffer_impl()
    {
        return nullptr;
    }
    void VulkanGraphicsDevice::submit_command_buffer_impl(CommandBuffer* commandBuffer)
    {
    }
    void VulkanGraphicsDevice::delete_device_object_impl(DeviceObject* object)
    {
    }
    Buffer* VulkanGraphicsDevice::create_buffer_impl(const BufferDescription& description)
    {
        return nullptr;
    }
    Framebuffer* VulkanGraphicsDevice::create_framebuffer_impl(const FramebufferDescription& description)
    {
        return nullptr;
    }
    Pipeline* VulkanGraphicsDevice::create_pipeline_impl(const PipelineDescription& description)
    {
        return nullptr;
    }
    Shader* VulkanGraphicsDevice::create_shader_impl(const ShaderDescription& description)
    {
        return nullptr;
    }
    ShaderSet* VulkanGraphicsDevice::create_shader_set_impl(const Array<Shader*>& shaders)
    {
        return nullptr;
    }
    Texture* VulkanGraphicsDevice::create_texture_impl(const TextureDescription& description)
    {
        return nullptr;
    }
    VertexLayout* VulkanGraphicsDevice::create_vertex_layout_impl(const VertexLayoutDescription& description)
    {
        return nullptr;
    }
}