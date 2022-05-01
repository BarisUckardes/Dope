#include "VKGraphicsDevice.h"

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Window/WindowsWindow.h>
#include <VULKAN/vulkan_win32.h>
typedef DopeEngine::WindowsWindow WindowAbstraction;
#endif
#include <Engine/Core/Assert.h>

namespace DopeEngine
{
	VKGraphicsDevice::VKGraphicsDevice(Window* ownerWindow) : GraphicsDevice(ownerWindow)
	{
		/*
		* Create vulkan device
		*/
		_create_vulkan_device();
	}
	GraphicsAPIType VKGraphicsDevice::get_api_type() const
	{
		return GraphicsAPIType::Vulkan;
	}

	String VKGraphicsDevice::get_version() const
	{
		return String();
	}

	void VKGraphicsDevice::make_current_impl()
	{

	}

	void VKGraphicsDevice::delete_device_object_impl(DeviceObject* object)
	{

	}

	Buffer* VKGraphicsDevice::create_buffer_impl(const BufferDescription& description)
	{
		return nullptr;
	}

	Framebuffer* VKGraphicsDevice::create_framebuffer_impl(const FramebufferDescription& description)
	{
		return nullptr;
	}

	Framebuffer* VKGraphicsDevice::create_window_swapchain_framebuffer_impl(const unsigned int width, const unsigned int height) const
	{
		return nullptr;
	}

	Pipeline* VKGraphicsDevice::create_pipeline_impl(const PipelineDescription& description)
	{
		return nullptr;
	}

	Shader* VKGraphicsDevice::create_shader_impl(const ShaderDescription& description)
	{
		return nullptr;
	}

	ShaderSet* VKGraphicsDevice::create_shader_set_impl(const Array<Shader*>& shaders)
	{
		return nullptr;
	}

	Texture* VKGraphicsDevice::create_texture_impl(const TextureDescription& description)
	{
		return nullptr;
	}

	CommandBuffer* VKGraphicsDevice::create_command_buffer_impl()
	{
		return nullptr;
	}

	ResourceLayout* VKGraphicsDevice::create_resource_layout_impl(const ResourceDescription& description)
	{
		return nullptr;
	}

	ResourceView* VKGraphicsDevice::create_resource_view_impl(const ResourceViewDescription& description)
	{
		return nullptr;
	}

	void VKGraphicsDevice::submit_command_buffer_impl(CommandBuffer* commandBuffer)
	{
	}

	void VKGraphicsDevice::update_buffer_impl(Buffer* buffer, const Byte* data)
	{
	}

	void VKGraphicsDevice::update_texture_impl(Texture* texture, const Byte* data)
	{
	}

	void VKGraphicsDevice::swap_swapchain_buffers_impl(const SwapchainFramebuffer* framebuffer)
	{
	}

	void VKGraphicsDevice::wait_for_finish_impl()
	{
	}

	void VKGraphicsDevice::_create_vulkan_device()
	{
#ifdef DOPE_OS_WINDOWS
		_create_win32_vulkan_device();
#endif
	}

	void VKGraphicsDevice::_create_win32_vulkan_device()
	{
		/*
		* Get window abstraction
		*/
		const WindowAbstraction* window = get_owner_window();

		/*
		* Enumarate instance extension properties
		*/
		unsigned int extensionPropertyCount = 0;
		const VkResult instanceExtensionEnumarationVkResult = vkEnumerateInstanceExtensionProperties(nullptr, &extensionPropertyCount, nullptr);

		/*
		* Validate enumaration result
		*/
		ASSERT(instanceExtensionEnumarationVkResult == VK_SUCCESS, "VKGraphicsDevice", "Instance extension enumaration failed!");

		/*
		* Validate extension count
		*/
		ASSERT(extensionPropertyCount > 0, "VKGraphicsDevice", "Instance extension properties must be not be zero!");

		/*
		* Log
		*/
		LOG("VKGraphicsDevice", "Total %d extensions found!", extensionPropertyCount);

		
		/*
		* Check extension support
		*/
		VkExtensionProperties* vkExtensionProperties = new VkExtensionProperties[extensionPropertyCount];
		const VkResult instanceExtensionEnumarationVkResult2 = vkEnumerateInstanceExtensionProperties(nullptr, &extensionPropertyCount, vkExtensionProperties);

		/*
		* Validate enumaration 2s
		*/
		ASSERT(instanceExtensionEnumarationVkResult2 == VK_SUCCESS, "VKGraphicsDevice", "Instance extension enumaration failed!");

		/*
		* Log extensions
		*/
		for (unsigned char i = 0; i < extensionPropertyCount; i++)
		{
			/*
			* Get extension property
			*/
			const VkExtensionProperties extensionProperty = vkExtensionProperties[i];

			/*
			* Display log
			*/
			LOG("VKGraphicsDevice", "Support vulkan extension found: %s", extensionProperty.extensionName);
		}

		/*
		* Enumarate instance layer
		*/
		unsigned int instanceLayerPropertyCount = 0;
		const VkResult enumarateLayerPropertiesVkR = vkEnumerateInstanceLayerProperties(&instanceLayerPropertyCount, nullptr);

		/*
		* Validate enumaration
		*/
		ASSERT(enumarateLayerPropertiesVkR == VK_SUCCESS, "VKGraphicsDevice", "Instance layer enumaration failed!");

		/*
		* Log
		*/
		LOG("VKGraphicsDevice", "Total %d layers found", instanceLayerPropertyCount);

		/*
		* Enumarate instance layer names
		*/
		VkLayerProperties* layerProperties = new VkLayerProperties[instanceLayerPropertyCount];
		Array<const char*> layerNames(instanceLayerPropertyCount);
		const VkResult enumarateLayerPropertiesVkR2 = vkEnumerateInstanceLayerProperties(&instanceLayerPropertyCount, layerProperties);
		for (unsigned char i = 0; i < instanceLayerPropertyCount; i++)
		{
			/*
			* Get layer property
			*/
			const VkLayerProperties layerProperty = layerProperties[i];

			/*
			* Register name
			*/
			layerNames.add(layerProperty.layerName);

			/*
			* Display log
			*/
			LOG("VKGraphicsDevice", "Supported vulkan layer found: %s", layerNames[i]);

			
		}

		/*
		* Create application info
		*/
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = *window->get_title();
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Dope Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		/*
		* Create instance create info
		*/
		VkInstanceCreateInfo instanceCreateInfo = {};
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &appInfo;
		Array<const char*> extensionNames = Array<const char*>
		{
			VK_KHR_SURFACE_EXTENSION_NAME,
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME
		};
		instanceCreateInfo.ppEnabledExtensionNames = extensionNames.get_data();
		instanceCreateInfo.enabledExtensionCount = extensionNames.get_cursor();

#if _DEBUG
		/*
		* Enable validation layers
		*/
		instanceCreateInfo.enabledLayerCount = instanceLayerPropertyCount;
		instanceCreateInfo.ppEnabledLayerNames = layerNames.get_data();
#endif
		/*
		* Create instance
		*/
		VkResult createInstanceVkResult = vkCreateInstance(&instanceCreateInfo, nullptr, &Instance);

		/*
		* Validate instance create
		*/
		ASSERT(createInstanceVkResult == VK_SUCCESS, "VKGraphicsDevice", "Creating VkInstance failed!");

		/*
		* Enumarate physical device
		*/
		unsigned int physicalDeviceCount = 0;
		const VkResult enumaratePhysicalDeviceVkR = vkEnumeratePhysicalDevices(Instance, &physicalDeviceCount, nullptr);

		/*
		* Validate enumaration
		*/
		ASSERT(enumaratePhysicalDeviceVkR == VK_SUCCESS, "VKGraphicsDevice", "Physical device enumaration failed!");

		/*
		* Validate physical device count
		*/
		ASSERT(physicalDeviceCount > 0, "VKGraphicsDevice", "There is no physical gpu's found on this computer!");

		/*
		* Get physical devices
		*/
		VkPhysicalDevice* physicalDevices = new VkPhysicalDevice[physicalDeviceCount];
		const VkResult enumaratePhysicalDeviceVkR2 = vkEnumeratePhysicalDevices(Instance, &physicalDeviceCount, physicalDevices);

		/*
		* Iterate physical devices and catch supported device
		*/
		for (unsigned char i = 0; i < physicalDeviceCount; i++)
		{
			/*
			* Get physical device
			*/
			const VkPhysicalDevice physicalDevice = physicalDevices[i];

			/*
			* Get physical device properties and features
			*/
			VkPhysicalDeviceProperties physicalDeviceProperties = { 0 };
			VkPhysicalDeviceFeatures physicalDeviceFeatures = { 0 };
			vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
			vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);
		}
	}

	bool VKGraphicsDevice::does_support_features(const GraphicsDeviceFeatures* features, Array<String>& messages)
	{
		return true;
	}

}