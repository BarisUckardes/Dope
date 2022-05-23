#include "GraphicsDevice.h"
#include <Engine/Graphics/API/OpenGL/Device/OpenGLGraphicsDevice.h>
#include <Engine/Graphics/API/Directx11/Device/DX11GraphicsDevice.h>
#include <Engine/Graphics/API/Directx12/Device/DX12GraphicsDevice.h>
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevice.h>
#include <Engine/Graphics/Device/GraphicsDeviceObject.h>
#include <Engine/Graphics/Buffer/GraphicsBuffer.h>
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Graphics/RenderPass/RenderPass.h>
#include <Engine/Graphics/Shader/Shader.h>
#include <Engine/Graphics/Texture/Texture.h>
#include <Engine/Application/Window/Window.h>
#include <Engine/Graphics/Framebuffer/SwapchainFramebuffer.h>
#include <Engine/Graphics/Device/GraphicsDeviceObjects.h>
#include <Engine/Graphics/Device/GraphicsDeviceFeatures.h>
#include <Engine/Graphics/Resource/GraphicsResource.h>
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	GraphicsDevice* GraphicsDevice::create(const GraphicsDeviceFeatures* requestedFeatures,GraphicsAPIType api, Window* ownerWindow,const SwapchainFramebufferDesc* swapchainDesc)
	{
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
		
		Array<String> messages;
		ASSERT(device->does_support_features(requestedFeatures, messages),"GraphicsDevice","Cannot create the device with the requested features.One or more features does not supported on this device");

		
		if (ownerWindow != nullptr && swapchainDesc != nullptr) // wants to create a graphics device with swapchain and window
		{
			const GraphicsDeviceFeatures* supportedFeatures = device->get_supported_features();
			ASSERT(supportedFeatures->can_display(), "GraphicsDevice", "Swapchain requsted but this device cant display!");

			ASSERT(swapchainDesc->Width <= supportedFeatures->get_max_framebuffer_width() && swapchainDesc->Height <= supportedFeatures->get_max_framebuffer_height(),
				"GraphicsDevice", "This device doesnt support the requester framebuffer size!. Requested size %d,%d but device supports only %d,%d",
				swapchainDesc->Width, swapchainDesc->Height, supportedFeatures->get_max_framebuffer_width(), supportedFeatures->get_max_framebuffer_height());

			device->create_swapchain_framebuffer(swapchainDesc);

			Window::bind_window_and_device(ownerWindow, device);
		}
			
		return device;
	}



	GraphicsCommandBuffer* GraphicsDevice::create_command_buffer()
	{
		return create_command_buffer_impl();
	}

	GraphicsResource* GraphicsDevice::create_resource(const GraphicsResourceDesc& desc)
	{
		GraphicsResource* resource = create_resource_impl(desc);
		register_device_object(resource);

		return resource;
	}

	void GraphicsDevice::submit_command_buffer(GraphicsCommandBuffer* GraphicsCommandBuffer)
	{
		submit_command_buffer_impl(GraphicsCommandBuffer);
	}

	void GraphicsDevice::update_texture(Texture* texture, const Byte* data)
	{
		update_texture_impl(texture, data);
	}

	void GraphicsDevice::update_buffer(GraphicsBuffer* buffer, const Byte* data)
	{
		update_buffer_impl(buffer, data);
	}

	void GraphicsDevice::swap_swapchain_buffers(const SwapchainFramebuffer* framebuffer)
	{
		ASSERT(framebuffer->is_swapchain_framebuffer(), "GraphicsDevice", "Given framebuffer is not a swapchain framebuffer");

		swap_swapchain_buffers_impl(framebuffer);
	}

	void GraphicsDevice::wait_for_finish()
	{
		wait_for_finish_impl();
	}

	bool GraphicsDevice::does_support_features(const GraphicsDeviceFeatures* features, Array<String>& messages)
	{
		unsigned char result = 1;
		if(features->has_compute_shader_support())
			result *= Features->has_compute_shader_support() == true ? 1 : 0;
		if(features->has_geometry_shader_support())
			result *= Features->has_geometry_shader_support() == true ? 1 : 0;
		if(features->has_tesellation_shader_support())
			result *= Features->has_tesellation_shader_support() == true ? 1 : 0;
		if(features->has_shading_rate_support())
			result *= Features->has_shading_rate_support() == true ? 1 : 0;
		if(features->can_display())
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

		return result;
	}

	GraphicsDevice::GraphicsDevice(Window* ownerWindow)
	{
		if (ownerWindow != nullptr)
		{
			OffscreenGraphicsDevice = false;
		}
		else
		{
			OffscreenGraphicsDevice = true;
		}

		OwnerWindow = ownerWindow;
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
		make_current_impl();
		Current = true;
	}
	void GraphicsDevice::delete_device_object(GraphicsDeviceObject* object)
	{
		remove_device_object(object);

		delete_device_object_impl(object);
		delete object;
	}
	GraphicsBuffer* GraphicsDevice::create_buffer(const BufferDescription& description)
	{
		GraphicsBuffer* buffer = create_buffer_impl(description);
		register_device_object(buffer);

		return buffer;
	}
	Framebuffer* GraphicsDevice::create_framebuffer(const FramebufferDescription& description)
	{
		Framebuffer* framebuffer = create_framebuffer_impl(description);
		register_device_object(framebuffer);

		return framebuffer;
	}
	RenderPass* GraphicsDevice::create_render_pass(const RenderPassDesc& desc)
	{
		RenderPass* renderPass = create_render_pass_impl(desc);
		register_device_object(renderPass);

		return renderPass;
	}
	Shader* GraphicsDevice::create_shader(const ShaderDescription& description)
	{
		Shader* shader = create_shader_impl(description);
		register_device_object(shader);

		return shader;
	}
	Texture* GraphicsDevice::create_texture(const TextureDescription& description)
	{
		Texture* texture = create_texture_impl(description);
		register_device_object(texture);

		return texture;
	}
	void GraphicsDevice::create_swapchain_framebuffer(const SwapchainFramebufferDesc* desc)
	{
		SWCHNFramebuffer = (SwapchainFramebuffer*)create_window_swapchain_framebuffer_impl(desc);
		LOG("GraphicsDevice", "Created swapchainFramebuffer");
	}
	void GraphicsDevice::register_device_object(GraphicsDeviceObject* object)
	{
		ChildObjects.add(object);
	}
	void GraphicsDevice::remove_device_object(GraphicsDeviceObject* object)
	{
		ChildObjects.remove(object);
	}
}