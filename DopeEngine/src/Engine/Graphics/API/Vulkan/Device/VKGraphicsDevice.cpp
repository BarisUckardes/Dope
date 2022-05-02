#include "VKGraphicsDevice.h"

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Window/WindowsWindow.h>
#include <VULKAN/vulkan_win32.h>
typedef DopeEngine::WindowsWindow WindowAbstraction;
#endif
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevicePropertiesUtils.h>
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDeviceFeaturesDesc.h>
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDeviceFeatures.h>
#include <Engine/Graphics/API/Vulkan/Framebuffer/VKSwapchainFramebuffer.h>

namespace DopeEngine
{
	VKGraphicsDevice::VKGraphicsDevice(Window* ownerWindow) : GraphicsDevice(ownerWindow)
	{
		/*
		* Create vulkan device
		*/
		_create_vulkan_device();
	}
	VkInstance VKGraphicsDevice::get_vk_instance() const
	{
		return Instance;
	}
	VkPhysicalDevice VKGraphicsDevice::get_vk_physicalDevice() const
	{
		return PhysicalDevice;
	}
	VkDevice VKGraphicsDevice::get_vk_logical_device() const
	{
		return LogicalDevice;
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
		/*
		* Create swapchain framebuffer desc
		*/
		SwapchainFramebufferDesc desc = {};
		desc.Count = 3;
		desc.DepthFormat = TextureFormat::R8unorm;
		desc.Format = TextureFormat::RGBA8unorm;
		desc.GenerateDepth = false;
		desc.Width = width;
		desc.Height = height;

		return new VKSwapchainFramebuffer(desc,(VKGraphicsDevice*)this,(Window*)get_owner_window());
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
		Array<const char*> instanceExtensionNames = Array<const char*>
		{
			VK_KHR_SURFACE_EXTENSION_NAME,
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME
		};
		instanceCreateInfo.ppEnabledExtensionNames = instanceExtensionNames.get_data();
		instanceCreateInfo.enabledExtensionCount = instanceExtensionNames.get_cursor();

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
		bool minimalPhysicalDeviceFound = false;
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

			/*
			* Validate physical device
			*/
			if (physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
				minimalPhysicalDeviceFound = true;
			else
				continue;


			/*
			* Set as target physical device
			*/
			PhysicalDevice = physicalDevice;

			/*
			* Create graphics device properties
			*/
			const String vendor = VKGraphicsDevicePropertiesUtils::get_vk_vendor_name(physicalDeviceProperties.vendorID);
			const String model = physicalDeviceProperties.deviceName;
			const GraphicsDeviceProperties properties(vendor, model);

			/*
			* Set graphics device properties
			*/
			set_properties(properties);

			/*
			* Create graphics device features
			*/
			GraphicsDeviceFeaturesDesc baseFeaturesDesc = {};
			baseFeaturesDesc.ComputeShader = physicalDeviceProperties.limits.timestampComputeAndGraphics;
			baseFeaturesDesc.GeometryShader = physicalDeviceFeatures.geometryShader;
			baseFeaturesDesc.TesellationShader = physicalDeviceFeatures.tessellationShader;
			baseFeaturesDesc.MaxColorAttachments = physicalDeviceProperties.limits.maxColorAttachments;
			baseFeaturesDesc.MaxComputeWorkGroupCount.X = physicalDeviceProperties.limits.maxComputeWorkGroupCount[0];
			baseFeaturesDesc.MaxComputeWorkGroupCount.Y = physicalDeviceProperties.limits.maxComputeWorkGroupCount[1];
			baseFeaturesDesc.MaxComputeWorkGroupCount.Z = physicalDeviceProperties.limits.maxComputeWorkGroupCount[2];
			baseFeaturesDesc.MaxComputeWorkGroupInvocations = physicalDeviceProperties.limits.maxComputeWorkGroupInvocations;
			baseFeaturesDesc.MaxComputeWorkGroupSize.X = physicalDeviceProperties.limits.maxComputeWorkGroupSize[0];
			baseFeaturesDesc.MaxComputeWorkGroupSize.Y = physicalDeviceProperties.limits.maxComputeWorkGroupSize[1];
			baseFeaturesDesc.MaxComputeWorkGroupSize.Z = physicalDeviceProperties.limits.maxComputeWorkGroupSize[2];
			baseFeaturesDesc.MaxCubeTextureDimension = physicalDeviceProperties.limits.maxImageDimensionCube;
			baseFeaturesDesc.MaxDrawCallIndexCount = physicalDeviceProperties.limits.maxDrawIndexedIndexValue;
			baseFeaturesDesc.MaxFramebufferHeight = physicalDeviceProperties.limits.maxFramebufferHeight;
			baseFeaturesDesc.MaxFramebufferWidth = physicalDeviceProperties.limits.maxFramebufferWidth;
			baseFeaturesDesc.MaxPerShaderStageResources = physicalDeviceProperties.limits.maxPerStageResources;
			baseFeaturesDesc.MaxTexture1DDimension = physicalDeviceProperties.limits.maxImageDimension1D;
			baseFeaturesDesc.MaxTexture2DDimension = physicalDeviceProperties.limits.maxImageDimension2D;
			baseFeaturesDesc.MaxTexture3DDimension = physicalDeviceProperties.limits.maxImageDimension3D;
			baseFeaturesDesc.MultipleViewports = physicalDeviceFeatures.multiViewport;
			baseFeaturesDesc.ShadingRate = physicalDeviceFeatures.sampleRateShading;
			baseFeaturesDesc.debug_log_desc(baseFeaturesDesc);

			/*
			* Create vk graphics device features desc
			*/
			VKGraphicsDeviceFeaturesDesc vkFeaturesDesc = {};

			/*
			* Get queue family properties
			*/
			unsigned int queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &queueFamilyCount, nullptr);
			VkQueueFamilyProperties* queueFamilyProperties = new VkQueueFamilyProperties[queueFamilyCount];
			vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &queueFamilyCount, queueFamilyProperties);

			/*
			* Collect queue family flags
			*/
			Array<VkQueueFlags> foundQueueFamilies;
			for (unsigned int p = 0; p < queueFamilyCount; p++)
			{
				/*
				* Get queue family properties
				*/
				const VkQueueFamilyProperties queueFamilyProperty = queueFamilyProperties[p];

				/*
				* Register supported queue family
				*/
				foundQueueFamilies.add(queueFamilyProperty.queueFlags);
			}
			vkFeaturesDesc.Queues = foundQueueFamilies;

			/*
			* Set graphics features
			*/
			VKGraphicsDeviceFeatures* vkDeviceFeatures = new VKGraphicsDeviceFeatures(vkFeaturesDesc, baseFeaturesDesc);
			set_features(vkDeviceFeatures);
		}

		/*
		* Validate minimal device found
		*/
		ASSERT(minimalPhysicalDeviceFound, "VKGraphicsDevice", "Minimal physical device couldnt be found!");

		/*
		* Get supported queues
		*/
		const Array<VkQueueFlags> supportedQueues = ((const VKGraphicsDeviceFeatures*)get_supported_features())->get_vk_queues();

		/*
		* Iterate and create vk queue creation infos
		*/
		Array<VkDeviceQueueCreateInfo> queueCreateInfos;
		queueCreateInfos.reserve(supportedQueues.get_cursor());
		constexpr float queuePriority = 1.0f;
		for (unsigned int i = 0; i < queueCreateInfos.get_cursor(); i++)
		{
			/*
			* Get vk queue flag
			*/
			const VkQueueFlags queueFlag = supportedQueues[i];

			/*
			* Create queue create info
			*/
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFlag;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;

			/*
			* Register create info
			*/
			queueCreateInfos.add(queueCreateInfo);
		}

		/*
		* Create logical device
		*/
		VkDeviceCreateInfo logicalDeviceCreateInfo{};
		logicalDeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		logicalDeviceCreateInfo.pQueueCreateInfos = queueCreateInfos.get_data();
		logicalDeviceCreateInfo.queueCreateInfoCount = queueCreateInfos.get_cursor();
		logicalDeviceCreateInfo.enabledExtensionCount = 0;
		logicalDeviceCreateInfo.ppEnabledExtensionNames = nullptr;
		logicalDeviceCreateInfo.enabledLayerCount = layerNames.get_cursor();
		logicalDeviceCreateInfo.ppEnabledLayerNames = layerNames.get_data();
		
		/*
		* Create logical device
		*/
		const VkResult createLogicalDeviceVkR = vkCreateDevice(PhysicalDevice, &logicalDeviceCreateInfo, nullptr,&LogicalDevice);

		/*
		* Validate logical device creation
		*/
		ASSERT(createLogicalDeviceVkR == VK_SUCCESS, "VKGraphicsDevice", "Creating logical device failed!");

		/*
		* Collect logical device queues
		*/
		for (unsigned int i = 0; i < supportedQueues.get_cursor(); i++)
		{
			/*
			* Get queue family index
			*/
			const VkQueueFlags familyIndex = supportedQueues[i];

			/*
			* Get queue
			*/
			VkQueue queue;
			vkGetDeviceQueue(LogicalDevice, familyIndex, i, &queue);
			
			/*
			* Register queue
			*/
			Queues.add(queue);
		}
	}

	bool VKGraphicsDevice::does_support_features(const GraphicsDeviceFeatures* features, Array<String>& messages)
	{
		/*
		* Check base desc support
		*/
		const bool baseFeaturesSupported = GraphicsDevice::does_support_features(features, messages);

		/*
		* Get Vk features
		*/
		const VKGraphicsDeviceFeatures* targetVkFeatures = (const VKGraphicsDeviceFeatures*)features;
		const VKGraphicsDeviceFeatures* selfFeatures = (const VKGraphicsDeviceFeatures*)get_supported_features();
		unsigned char vkResult = 1;

		/*
		* Validate features
		*/
		vkResult *= selfFeatures->get_vk_queues().hasAll(targetVkFeatures->get_vk_queues()) == true ? 1 : 0;

		/*
		* Set final validation
		*/
		const bool vkFeaturesSupported = vkResult == 1 ? true : false;

		return baseFeaturesSupported && vkFeaturesSupported;
	}

}