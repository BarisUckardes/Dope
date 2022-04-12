#include "Directx12GraphicsDevice.h"
#include <Engine/Core/Assert.h>
namespace DopeEngine
{
	Directx12GraphicsDevice::Directx12GraphicsDevice(Window* ownerWindow) : GraphicsDevice(ownerWindow)
	{
		_create_directx12_device();
	}
	Directx12GraphicsDevice::~Directx12GraphicsDevice()
	{

	}
	void Directx12GraphicsDevice::_create_directx12_device()
	{
#ifdef DOPE_OS_WINDOWS
		_create_directx12_device();
#else
		ASSERT(false, "Directx12GraphicsDevice", "Directx12 cannot be initialized with non-windows operating system");
#endif
	}
	void Directx12GraphicsDevice::_create_win32_directx12_device()
	{
		ASSERT(false, "Directx12GraphicsDevice", "Not implemented yet!");
	}
	CommandBuffer* Directx12GraphicsDevice::create_command_buffer_impl()
	{
		return nullptr;
	}
	void Directx12GraphicsDevice::submit_command_buffer_impl(CommandBuffer* commandBuffer)
	{
	}
	void Directx12GraphicsDevice::delete_device_object_impl(DeviceObject* object)
	{
	}
	Buffer* Directx12GraphicsDevice::create_buffer_impl(const BufferDescription& description)
	{
		return nullptr;
	}
	Framebuffer* Directx12GraphicsDevice::create_framebuffer_impl(const FramebufferDescription& description)
	{
		return nullptr;
	}
	Pipeline* Directx12GraphicsDevice::create_pipeline_impl(const PipelineDescription& description)
	{
		return nullptr;
	}
	Shader* Directx12GraphicsDevice::create_shader_impl(const ShaderDescription& description)
	{
		return nullptr;
	}
	ShaderSet* Directx12GraphicsDevice::create_shader_set_impl(const Array<Shader*>& shaders)
	{
		return nullptr;
	}
	Texture* Directx12GraphicsDevice::create_texture_impl(const TextureDescription& description)
	{
		return nullptr;
	}
	VertexLayout* Directx12GraphicsDevice::create_vertex_layout_impl(const VertexLayoutDescription& description)
	{
		return nullptr;
	}
	GraphicsAPIType Directx12GraphicsDevice::get_api_type() const
	{
		return GraphicsAPIType::Directx12;
	}
	String Directx12GraphicsDevice::get_version() const
	{
		return String();
	}
	void Directx12GraphicsDevice::make_current_impl()
	{
	}
}
