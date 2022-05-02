#include "GraphicsDevice.h"
#include <Engine/Graphics/API/OpenGL/Device/OpenGLGraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <Engine/Graphics/Device/DeviceObject.h>
#include <Engine/Graphics/Buffer/Buffer.h>
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Graphics/Pipeline/Pipeline.h>
#include <Engine/Graphics/Shader/Shader.h>
#include <Engine/Graphics/Shader/ShaderSet.h>
#include <Engine/Graphics/Texture/Texture.h>
#include <Engine/Application/Window/Window.h>
#include <Engine/Graphics/Framebuffer/SwapchainFramebuffer.h>
#include <Engine/Graphics/Device/DeviceObjects.h>
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	GraphicsDevice* GraphicsDevice::create(const GraphicsDeviceFeatures* requestedFeatures,GraphicsAPIType api, Window* ownerWindow)
	{
		/*
		* Create graphics device
		*/
		GraphicsDevice* device = nullptr;
		switch (api)
		{
			case DopeEngine::GraphicsAPIType::Undefined:
				ASSERT(false,"GraphicsDevice", "Specified graphics api type is undefined!");
				break;
			case DopeEngine::GraphicsAPIType::OpenGL:
				device = new OpenGLGraphicsDevice(ownerWindow);
				break;
			case DopeEngine::GraphicsAPIType::Directx11:
				device =  new DX11GraphicsDevice(ownerWindow);
				break;
			case DopeEngine::GraphicsAPIType::Directx12:
				device = new DX12GraphicsDevice(ownerWindow);
				break;
			case DopeEngine::GraphicsAPIType::Vulkan:
				device = new VKGraphicsDevice(ownerWindow);
				break;
			default:
				ASSERT(false, "GraphicsDevice", "Specified graphics api type is not valid!");
				break;
		}
		
		/*
		* Validate
		*/
		Array<String> messages;
		ASSERT(device->does_support_features(requestedFeatures, messages),"GraphicsDevice","Cannot create the device with the requested features.One or more features does not supported on this device");

		/*
		* Log unsupported features
		*/
		for (unsigned int i = 0; i < messages.get_cursor(); i++)
		{
			/*
			* Get string
			*/
			const String message = messages[i];

			/*
			* Log
			*/
			LOG("GraphicsDevice", "Feature %s not supported on this device",*message);
		}

		/*
		* Create swapchainbuffer (IF REQUESTED)
		*/
		if(ownerWindow != nullptr)
			device->create_swapchain_framebuffer();
		
		return device;
	}



	CommandBuffer* GraphicsDevice::create_command_buffer()
	{
		return create_command_buffer_impl();
	}

	ResourceLayout* GraphicsDevice::create_resource_layout(const ResourceDescription& description)
	{
		/*
		* Create resource layout
		*/
		ResourceLayout* layout = create_resource_layout_impl(description);

		/*
		* Register
		*/
		register_device_object(layout);

		return layout;
	}

	ResourceView* GraphicsDevice::create_resource_view(const ResourceViewDescription& description)
	{
		/*
		* Create resource view
		*/
		ResourceView* view = create_resource_view_impl(description);

		/*
		* Register
		*/
		register_device_object(view);

		return view;
	}

	void GraphicsDevice::submit_command_buffer(CommandBuffer* commandBuffer)
	{
		submit_command_buffer_impl(commandBuffer);
	}

	void GraphicsDevice::update_texture(Texture* texture, const Byte* data)
	{
		update_texture_impl(texture, data);
	}

	void GraphicsDevice::update_buffer(Buffer* buffer, const Byte* data)
	{
		update_buffer_impl(buffer, data);
	}

	void GraphicsDevice::swap_swapchain_buffers(const SwapchainFramebuffer* framebuffer)
	{
		/*
		* Validate if target framebuffer is an swapchain framebuffer
		*/
		ASSERT(framebuffer->is_swapchain_framebuffer(), "GraphicsDevice", "Given framebuffer is not a swapchain framebuffer");

		/*
		* Call swapbuffer impls
		*/
		swap_swapchain_buffers_impl(framebuffer);
	}

	void GraphicsDevice::wait_for_finish()
	{
		wait_for_finish_impl();
	}

	bool GraphicsDevice::does_support_features(const GraphicsDeviceFeatures* features, Array<String>& messages)
	{
		/*
		* Check features
		*/
		unsigned char result = 1;
		result *= Features->has_compute_shader_support() == true ? 1 : 0;
		result *= Features->has_geometry_shader_support() == true ? 1 : 0;
		result *= Features->has_tesellation_shader_support() == true ? 1 : 0;
		result *= Features->has_shading_rate_support() == true ? 1 : 0;
		result *= Features->can_display() == true ? 1 : 0;
		result *= Features->get_max_texture1D_dimension() >= features->get_max_texture1D_dimension() ? 1 : 0;
		result *= Features->get_max_texture2D_dimension() >= features->get_max_texture2D_dimension() ? 1 : 0;
		result *= Features->get_max_texture3D_dimension() >= features->get_max_texture3D_dimension() ? 1 : 0;
		result *= Features->get_max_cubeTexture_dimension() >= features->get_max_cubeTexture_dimension() ? 1 : 0;
		result *= Features->get_max_color_attachments() >= features->get_max_color_attachments() ? 1 : 0;
		result *= Features->get_max_per_shader_stage_resources() >= features->get_max_per_shader_stage_resources() ? 1 : 0;
		result *= Features->get_compute_work_group_count().X >= features->get_compute_work_group_count().X ? 1 : 0;
		result *= Features->get_compute_work_group_count().Y >= features->get_compute_work_group_count().Y ? 1 : 0;
		result *= Features->get_compute_work_group_count().Z >= features->get_compute_work_group_count().Z ? 1 : 0;
		result *= Features->get_compute_work_group_invocations() >= features->get_compute_work_group_invocations() ? 1 : 0;
		result *= Features->get_compute_work_group_size().X >= features->get_compute_work_group_size().X ? 1 : 0;
		result *= Features->get_compute_work_group_size().Y >= features->get_compute_work_group_size().Y ? 1 : 0;
		result *= Features->get_compute_work_group_size().Z >= features->get_compute_work_group_size().Z ? 1 : 0;
		result *= Features->get_max_draw_call_index_count() >= features->get_max_draw_call_index_count() ? 1 : 0;
		result *= Features->get_max_framebuffer_width() >= features->get_max_framebuffer_width() ? 1 : 0;
		result *= Features->get_max_framebuffer_height() >= features->get_max_framebuffer_height() ? 1 : 0;

		return result == 1;
	}

	GraphicsDevice::GraphicsDevice(Window* ownerWindow)
	{
		/*
		* Validate and set offscreen state
		*/
		if (ownerWindow != nullptr)
		{
			ownerWindow->assing_graphics_device(this);
			OffscreenGraphicsDevice = false;
		}
		else
		{
			OffscreenGraphicsDevice = true;
		}

		/*
		* Set target window even if its a nullptr value
		*/
		OwnerWindow = ownerWindow;

		/*
		* Initialize
		*/
		Current = false;
		Features = {};
		SWCHNFramebuffer = nullptr;
	}

	void GraphicsDevice::set_properties(const GraphicsDeviceProperties& properties)
	{
		Properties = properties;
	}

	void GraphicsDevice::set_features(const GraphicsDeviceFeatures* features)
	{
		Features = (GraphicsDeviceFeatures*)features;
	}
	
	bool GraphicsDevice::is_current() const
	{
		return Current;
	}

	bool GraphicsDevice::is_offscreen_device() const
	{
		return OffscreenGraphicsDevice;
	}

	const Window* GraphicsDevice::get_owner_window() const
	{
		return OwnerWindow;
	}
	SwapchainFramebuffer* GraphicsDevice::get_swapchain_framebuffer() const
	{
		return SWCHNFramebuffer;
	}
	const GraphicsDeviceFeatures* GraphicsDevice::get_supported_features() const
	{
		return Features;
	}
	GraphicsDeviceProperties GraphicsDevice::get_properties() const
	{
		return Properties;
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
		remove_device_object(object);

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
		register_device_object(buffer);

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
		register_device_object(framebuffer);

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
		register_device_object(pipeline);

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
		register_device_object(shader);

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
		register_device_object(shaderSet);

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
		register_device_object(texture);

		return texture;
	}
	void GraphicsDevice::create_swapchain_framebuffer()
	{
		SWCHNFramebuffer = (SwapchainFramebuffer*)create_window_swapchain_framebuffer_impl(OwnerWindow->get_width(),OwnerWindow->get_height());
		LOG("GraphicsDevice", "Created swapchainFramebuffer");
	}
	void GraphicsDevice::register_device_object(DeviceObject* object)
	{
		ChildObjects.add(object);
	}
	void GraphicsDevice::remove_device_object(DeviceObject* object)
	{
		ChildObjects.remove(object);
	}
}