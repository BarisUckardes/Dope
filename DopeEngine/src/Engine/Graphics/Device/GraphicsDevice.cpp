#include "GraphicsDevice.h"
#include <Engine/Graphics/API/OpenGL/Device/OpenGLGraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Device/Directx11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Device/Directx12GraphicsDevice.h>
#include <Engine/Graphics/API/Vulkan/Device/VulkanGraphicsDevice.h>
#include <Engine/Graphics/Device/DeviceObject.h>
#include <Engine/Graphics/Buffer/Buffer.h>
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Graphics/Pipeline/Pipeline.h>
#include <Engine/Graphics/Shader/Shader.h>
#include <Engine/Graphics/Shader/ShaderSet.h>
#include <Engine/Graphics/Texture/Texture.h>
#include <Engine/Graphics/Vertex/VertexLayout.h>
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	GraphicsDevice* GraphicsDevice::create(GraphicsAPIType api, Window* ownerWindow)
	{
		switch (api)
		{
			case DopeEngine::GraphicsAPIType::Undefined:
				ASSERT(false,"GraphicsDevice", "Specified graphics api type is undefined!");
				break;
			case DopeEngine::GraphicsAPIType::OpenGL:
				return new OpenGLGraphicsDevice(ownerWindow);
				break;
			case DopeEngine::GraphicsAPIType::Directx11:
				return new Directx11GraphicsDevice(ownerWindow);
				break;
			case DopeEngine::GraphicsAPIType::Directx12:
				return new Directx12GraphicsDevice(ownerWindow);
				break;
			case DopeEngine::GraphicsAPIType::Vulkan:
				return new VulkanGraphicsDevice(ownerWindow);
				break;
		}
		ASSERT(false,"GraphicsDevice", "Specified graphics api type is not valid!");
		return nullptr;
	}

	VertexLayout* GraphicsDevice::create_vertex_layout(const VertexLayoutDescription& description)
	{
		/*
		* Create vertex layout
		*/
		VertexLayout* layout = create_vertex_layout_impl(description);

		return layout;
	}

	CommandBuffer* GraphicsDevice::create_command_buffer()
	{
		return create_command_buffer_impl();
	}

	void GraphicsDevice::submit_command_buffer(CommandBuffer* commandBuffer)
	{
		submit_command_buffer_impl(commandBuffer);
	}

	GraphicsDevice::GraphicsDevice(Window* ownerWindow)
	{
		OwnerWindow = ownerWindow;
		OwnerWindow->assing_graphics_device(this);
	}
	
	

	bool GraphicsDevice::is_current() const
	{
		return Current;
	}

	const Window* GraphicsDevice::get_owner_window() const
	{
		return OwnerWindow;
	}
	void GraphicsDevice::make_current()
	{
		/*
		* Calll api implementation
		*/
		make_current_impl();

		/*
		* Set current state
		*/
		Current = true;
	}
	void GraphicsDevice::delete_device_object(DeviceObject* object)
	{
		/*
		* Remove it from this device
		*/
		ChildObjects.remove(object);

		/*
		* Call impl
		*/
		delete_device_object_impl(object);

		/*
		* Delete heap
		*/
		delete object;
	}
	Buffer* GraphicsDevice::create_buffer(const BufferDescription& description)
	{
		/*
		* Create buffer impl
		*/
		Buffer* buffer = create_buffer_impl(description);

		/*
		* Register it to this device
		*/
		ChildObjects.add(buffer);

		return buffer;
	}
	Framebuffer* GraphicsDevice::create_framebuffer(const FramebufferDescription& description)
	{
		/*
		* Create framebuffer impl
		*/
		Framebuffer* framebuffer = create_framebuffer_impl(description);

		/*
		* Register it to this device
		*/
		ChildObjects.add(framebuffer);

		return framebuffer;
	}
	Pipeline* GraphicsDevice::create_pipeline(const PipelineDescription& description)
	{
		/*
		* Create pipeline impl
		*/
		Pipeline* pipeline = create_pipeline_impl(description);

		/*
		* Register it to this device
		*/
		ChildObjects.add(pipeline);

		return pipeline;
	}
	Shader* GraphicsDevice::create_shader(const ShaderDescription& description)
	{
		/*
		* Create shader impl
		*/
		Shader* shader = create_shader_impl(description);

		/*
		* Register it to this device
		*/
		ChildObjects.add(shader);

		return shader;
	}
	ShaderSet* GraphicsDevice::create_shader_set(const Array<Shader*>& shaders)
	{
		/*
		* Create shader set
		*/
		ShaderSet* shaderSet = create_shader_set_impl(shaders);

		/*
		* Register it to this device
		*/
		ChildObjects.add(shaderSet);

		return shaderSet;
	}
	Texture* GraphicsDevice::create_texture(const TextureDescription& description)
	{
		/*
		* Create texture
		*/
		Texture* texture = create_texture_impl(description);

		/*
		* Register it to this device
		*/
		ChildObjects.add(texture);

		return texture;
	}
}