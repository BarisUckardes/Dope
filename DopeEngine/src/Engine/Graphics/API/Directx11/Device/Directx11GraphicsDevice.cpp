//#include "Directx11GraphicsDevice.h"
//#include <Engine/Core/Assert.h>
//namespace DopeEngine
//{
//	Directx11GraphicsDevice::Directx11GraphicsDevice(Window* ownerWindow) : GraphicsDevice(ownerWindow)
//	{
//		_create_directx11_device();
//	}
//	void Directx11GraphicsDevice::_create_directx11_device()
//	{
//#ifdef DOPE_OS_WINDOWS
//		_create_win32_directx11_device();
//#else
//		ASSERT(false,"Directx11GraphicsDevice", "Directx11 cannot be initialized with non-windows operating system");
//#endif
//	}
//	void Directx11GraphicsDevice::_create_win32_directx11_device()
//	{
//		ASSERT(false,"Directx11GraphicsDevice", "Not implemented yet!");
//	}
//	Framebuffer* Directx11GraphicsDevice::create_window_swapchain_framebuffer_impl() const
//	{
//		return nullptr;
//	}
//	CommandBuffer* Directx11GraphicsDevice::create_command_buffer_impl()
//	{
//		return nullptr;
//	}
//	void Directx11GraphicsDevice::submit_command_buffer_impl(CommandBuffer* commandBuffer)
//	{
//	}
//	void Directx11GraphicsDevice::delete_device_object_impl(DeviceObject* object)
//	{
//	}
//	Buffer* Directx11GraphicsDevice::create_buffer_impl(const BufferDescription& description)
//	{
//		return nullptr;
//	}
//	Framebuffer* Directx11GraphicsDevice::create_framebuffer_impl(const FramebufferDescription& description)
//	{
//		return nullptr;
//	}
//	Pipeline* Directx11GraphicsDevice::create_pipeline_impl(const PipelineDescription& description)
//	{
//		return nullptr;
//	}
//	Shader* Directx11GraphicsDevice::create_shader_impl(const ShaderDescription& description)
//	{
//		return nullptr;
//	}
//	ShaderSet* Directx11GraphicsDevice::create_shader_set_impl(const Array<Shader*>& shaders)
//	{
//		return nullptr;
//	}
//	Texture* Directx11GraphicsDevice::create_texture_impl(const TextureDescription& description)
//	{
//		return nullptr;
//	}
//	GraphicsAPIType Directx11GraphicsDevice::get_api_type() const
//	{
//		return GraphicsAPIType::Directx11;
//	}
//	String Directx11GraphicsDevice::get_version() const
//	{
//		return String();
//	}
//	void Directx11GraphicsDevice::make_current_impl()
//	{
//	}
//}