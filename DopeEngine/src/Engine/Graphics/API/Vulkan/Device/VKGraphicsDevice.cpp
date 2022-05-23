#include "VKGraphicsDevice.h"

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Window/WindowsWindow.h>
#include <VULKAN/vulkan_win32.h>
#endif

#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDevicePropertiesUtils.h>
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDeviceFeaturesDesc.h>
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDeviceFeatures.h>
#include <Engine/Graphics/API/Vulkan/Framebuffer/VKSwapchainFramebuffer.h>
#include <Engine/Graphics/Buffer/BufferType.h>
#include <Engine/Graphics/Buffer/GraphicsBuffer.h>
#include <Engine/Graphics/API/Vulkan/Device/VKDeviceObjects.h>

namespace DopeEngine
{
	static VKAPI_ATTR VkBool32 VKAPI_CALL validation_debug_callback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);
	VKGraphicsDevice::VKGraphicsDevice(Window* ownerWindow) : GraphicsDevice(ownerWindow)
	{
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
	VkCommandPool VKGraphicsDevice::get_vk_command_pool() const
	{
		return GraphicsCommandPool;
	}
	VkQueue VKGraphicsDevice::get_vk_graphics_queue() const
	{
		return GraphicsQueue;
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

	void VKGraphicsDevice::delete_device_object_impl(GraphicsDeviceObject* object)
	{

	}

	GraphicsBuffer* VKGraphicsDevice::create_buffer_impl(const BufferDescription& description)
	{
		BufferType bufferType = description.Type;
		GraphicsBuffer* buffer = nullptr;
		switch (bufferType)
		{
			case DopeEngine::BufferType::VertexBuffer:
				buffer = new VKVertexBuffer(description, this);
				break;
			case DopeEngine::BufferType::IndexBuffer:
				buffer = new VKIndexBuffer(description, this);
				break;
			case DopeEngine::BufferType::UniformBuffer:
				buffer = new VKConstantBuffer(description, this);
				break;
			default:
				ASSERT(false, "VKGraphicsDevice", "Invalid BufferType, cannot produce a buffer");
				break;
		}

		return buffer;
	}

	Framebuffer* VKGraphicsDevice::create_framebuffer_impl(const FramebufferDescription& description)
	{
		return nullptr;
	}

	Framebuffer* VKGraphicsDevice::create_window_swapchain_framebuffer_impl(const SwapchainFramebufferDesc* desc) const
	{
		return new VKSwapchainFramebuffer(*desc,(VKGraphicsDevice*)this,(Window*)get_owner_window());
	}

	RenderPass* VKGraphicsDevice::create_render_pass_impl(const RenderPassDesc& desc)
	{
		return new VKRenderPass(desc,this);
	}

	Shader* VKGraphicsDevice::create_shader_impl(const ShaderDescription& description)
	{
		return new VKShader(description,this);
	}


	Texture* VKGraphicsDevice::create_texture_impl(const TextureDescription& description)
	{
		return nullptr;
	}

	GraphicsCommandBuffer* VKGraphicsDevice::create_command_buffer_impl()
	{
		return new VKCommandBuffer(this);
	}

	GraphicsResource* VKGraphicsDevice::create_resource_impl(const GraphicsResourceDesc& desc)
	{
		return nullptr;
	}

	void VKGraphicsDevice::submit_command_buffer_impl(GraphicsCommandBuffer* GraphicsCommandBuffer)
	{

		const VKCommandBuffer* vkCommandBuffer = (const VKCommandBuffer*)GraphicsCommandBuffer;

		VkCommandBuffer vkCmdBuffer = vkCommandBuffer->get_vk_command_buffer();
		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &vkCmdBuffer;
		submitInfo.signalSemaphoreCount = 0;
		submitInfo.waitSemaphoreCount = 0;

		const VkResult submitVkR = vkQueueSubmit(GraphicsQueue, 1, &submitInfo,VK_NULL_HANDLE);
		ASSERT(submitVkR == VK_SUCCESS, "VKGraphicsDevice", "Couldnt submit the queue");
	}

	void VKGraphicsDevice::update_buffer_impl(GraphicsBuffer* buffer, const Byte* data)
	{

	}

	void VKGraphicsDevice::update_texture_impl(Texture* texture, const Byte* data)
	{

	}

	void VKGraphicsDevice::swap_swapchain_buffers_impl(const SwapchainFramebuffer* framebuffer)
	{
		VKSwapchainFramebuffer* vkSwapchainFramebuffer = (VKSwapchainFramebuffer*)framebuffer;


		const VkSwapchainKHR vkSwapchain = vkSwapchainFramebuffer->get_vk_swapchain();

		const unsigned int imageIndex = vkSwapchainFramebuffer->get_vk_current_swapchain_image_index();

		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 0;
		presentInfo.pWaitSemaphores = VK_NULL_HANDLE;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &vkSwapchain;
		presentInfo.pImageIndices = &imageIndex;
		presentInfo.pResults = VK_NULL_HANDLE;
		vkQueuePresentKHR(GraphicsQueue, &presentInfo);

		vkSwapchainFramebuffer->increment_vk_swapchain_image_index();
	}

	void VKGraphicsDevice::wait_for_finish_impl()
	{
		vkDeviceWaitIdle(LogicalDevice);
	}

	void VKGraphicsDevice::_create_vulkan_device()
	{
#ifdef DOPE_OS_WINDOWS
		_create_win32_vulkan_device();
#endif

	}

	void VKGraphicsDevice::_create_win32_vulkan_device()
	{
		const WindowsWindow* win32Window = (const WindowsWindow*)get_owner_window();

		unsigned int extensionPropertyCount = 0;
		const VkResult instanceExtensionEnumarationVkResult = vkEnumerateInstanceExtensionProperties(nullptr, &extensionPropertyCount, nullptr);
		ASSERT(instanceExtensionEnumarationVkResult == VK_SUCCESS, "VKGraphicsDevice", "Instance extension enumaration failed!");
		ASSERT(extensionPropertyCount > 0, "VKGraphicsDevice", "Instance extension properties must be not be zero!");


		VkExtensionProperties* vkExtensionProperties = new VkExtensionProperties[extensionPropertyCount];
		const VkResult instanceExtensionEnumarationVkResult2 = vkEnumerateInstanceExtensionProperties(nullptr, &extensionPropertyCount, vkExtensionProperties);
		ASSERT(instanceExtensionEnumarationVkResult2 == VK_SUCCESS, "VKGraphicsDevice", "Instance extension enumaration failed!");

		for (unsigned char i = 0; i < extensionPropertyCount; i++)
		{
			/*
			* Get extension property
			*/
			const VkExtensionProperties extensionProperty = vkExtensionProperties[i];

		}

		unsigned int instanceLayerPropertyCount = 0;
		const VkResult enumarateLayerPropertiesVkR = vkEnumerateInstanceLayerProperties(&instanceLayerPropertyCount, nullptr);
		ASSERT(enumarateLayerPropertiesVkR == VK_SUCCESS, "VKGraphicsDevice", "Instance layer enumaration failed!");

		VkLayerProperties* layerProperties = new VkLayerProperties[instanceLayerPropertyCount];
		Array<const char*> layerNames(instanceLayerPropertyCount);
		const VkResult enumarateLayerPropertiesVkR2 = vkEnumerateInstanceLayerProperties(&instanceLayerPropertyCount, layerProperties);
#ifdef _DEBUG
		for (unsigned char i = 0; i < instanceLayerPropertyCount; i++)
		{
			const VkLayerProperties layerProperty = layerProperties[i];

			layerNames.add(layerProperty.layerName);
		}
#endif


		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = *win32Window->get_title();
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Dope Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo instanceCreateInfo = {};
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &appInfo;

		Array<const char*> instanceExtensionNames = Array<const char*>();
		instanceExtensionNames.add(VK_KHR_SURFACE_EXTENSION_NAME);
		instanceExtensionNames.add(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

#if _DEBUG
		instanceExtensionNames.add(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		instanceExtensionNames.add(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
		instanceCreateInfo.ppEnabledExtensionNames = instanceExtensionNames.get_data();
		instanceCreateInfo.enabledExtensionCount = instanceExtensionNames.get_cursor();

		instanceCreateInfo.enabledLayerCount = layerNames.get_cursor();
		instanceCreateInfo.ppEnabledLayerNames = layerNames.get_data();

#ifdef _DEBUG
		VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo{};
		debugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugMessengerCreateInfo.pfnUserCallback = validation_debug_callback;
		debugMessengerCreateInfo.pUserData = nullptr; // Optional

		instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugMessengerCreateInfo; //WTF is this?? some sort of chain creation i guess
#endif
		VkResult createInstanceVkResult = vkCreateInstance(&instanceCreateInfo, nullptr, &Instance);
		ASSERT(createInstanceVkResult == VK_SUCCESS, "VKGraphicsDevice", "Creating VkInstance failed!");

		unsigned int physicalDeviceCount = 0;
		const VkResult enumaratePhysicalDeviceVkR = vkEnumeratePhysicalDevices(Instance, &physicalDeviceCount, nullptr);
		ASSERT(enumaratePhysicalDeviceVkR == VK_SUCCESS, "VKGraphicsDevice", "Physical device enumaration failed!");
		ASSERT(physicalDeviceCount > 0, "VKGraphicsDevice", "There is no physical gpu's found on this computer!");

		VkPhysicalDevice* physicalDevices = new VkPhysicalDevice[physicalDeviceCount];
		const VkResult enumaratePhysicalDeviceVkR2 = vkEnumeratePhysicalDevices(Instance, &physicalDeviceCount, physicalDevices);
		ASSERT(enumaratePhysicalDeviceVkR2 == VK_SUCCESS, "VKGraphicsDevice", "Physical device enumaration failed!");

		bool minimalPhysicalDeviceFound = false;
		for (unsigned char i = 0; i < physicalDeviceCount; i++)
		{
			const VkPhysicalDevice physicalDevice = physicalDevices[i];

			VkPhysicalDeviceProperties physicalDeviceProperties = { 0 };
			VkPhysicalDeviceFeatures physicalDeviceFeatures = { 0 };
			vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
			vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);

			if (physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
				minimalPhysicalDeviceFound = true;
			else
				continue;

			PhysicalDevice = physicalDevice;

			const String vendor = VKGraphicsDevicePropertiesUtils::get_vk_vendor_name(physicalDeviceProperties.vendorID);
			const String model = physicalDeviceProperties.deviceName;
			const GraphicsDeviceProperties properties(vendor, model);
			set_properties(properties);

			GraphicsDeviceFeaturesDesc baseFeaturesDesc = {};
			baseFeaturesDesc.ComputeShader = physicalDeviceProperties.limits.timestampComputeAndGraphics;
			baseFeaturesDesc.GeometryShader = physicalDeviceFeatures.geometryShader;
			baseFeaturesDesc.TesellationShader = physicalDeviceFeatures.tessellationShader;
			baseFeaturesDesc.CanDisplay = instanceExtensionNames.has(VK_KHR_SURFACE_EXTENSION_NAME);
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

			VKGraphicsDeviceFeaturesDesc vkFeaturesDesc = {};

			unsigned int queueFamilyCount = 0;
			vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &queueFamilyCount, nullptr);

			VkQueueFamilyProperties* queueFamilyProperties = new VkQueueFamilyProperties[queueFamilyCount];
			vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &queueFamilyCount, queueFamilyProperties);

			Array<VKQueueFamilyProperties> foundQueueFamilies;
			for (unsigned int p = 0; p < queueFamilyCount; p++)
			{
				const VkQueueFamilyProperties queueFamilyProperty = queueFamilyProperties[p];

				VkQueueFlags flag = 0;
				if (queueFamilyProperty.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				{
					GraphicsQueueFamilyIndex = p;
					flag = VK_QUEUE_GRAPHICS_BIT;
				}
				else if (queueFamilyProperty.queueFlags & VK_QUEUE_COMPUTE_BIT)
				{
					ComputeQueueFamilyIndex = p;
					flag = VK_QUEUE_COMPUTE_BIT;
				}

				foundQueueFamilies.add({flag,queueFamilyProperty.queueCount,p});
			}
			vkFeaturesDesc.QueueFamilies = foundQueueFamilies;

			VKGraphicsDeviceFeatures* vkDeviceFeatures = new VKGraphicsDeviceFeatures(vkFeaturesDesc, baseFeaturesDesc);
			set_features(vkDeviceFeatures);
		}
		ASSERT(minimalPhysicalDeviceFound, "VKGraphicsDevice", "Minimal physical device couldnt be found!");

		const VKGraphicsDeviceFeatures* vkSupportedDeviceFeatures = (const VKGraphicsDeviceFeatures*)get_supported_features();
		const Array<VKQueueFamilyProperties> supportedQueueFamilies = vkSupportedDeviceFeatures->get_vk_queues();

		Array<VkDeviceQueueCreateInfo> queueCreateInfos;
		queueCreateInfos.reserve(supportedQueueFamilies.get_cursor());

		const float defaultQueuePriority = 1.0f;

		for (unsigned int i = 0; i < supportedQueueFamilies.get_cursor(); i++)
		{
			const VKQueueFamilyProperties familyProperty = supportedQueueFamilies[i];

			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueCount = 1; // its always 1 for DopeEngine
			queueCreateInfo.pQueuePriorities = &defaultQueuePriority;
			queueCreateInfo.queueFamilyIndex = familyProperty.get_family_index();

			queueCreateInfos.add(queueCreateInfo);
		}
		
		/*
		* Create logical device
		*/
		const char* deviceExtensions = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
		VkDeviceCreateInfo logicalDeviceCreateInfo{};
		logicalDeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		logicalDeviceCreateInfo.pQueueCreateInfos = queueCreateInfos.get_data();
		logicalDeviceCreateInfo.queueCreateInfoCount = queueCreateInfos.get_cursor();
		logicalDeviceCreateInfo.enabledExtensionCount = 1;
		logicalDeviceCreateInfo.ppEnabledExtensionNames = &deviceExtensions;
		logicalDeviceCreateInfo.enabledLayerCount = layerNames.get_cursor();
		logicalDeviceCreateInfo.ppEnabledLayerNames = layerNames.get_data();
		
		const VkResult createLogicalDeviceVkR = vkCreateDevice(PhysicalDevice, &logicalDeviceCreateInfo, nullptr,&LogicalDevice);
		ASSERT(createLogicalDeviceVkR == VK_SUCCESS, "VKGraphicsDevice", "Creating logical device failed!");

		vkGetDeviceQueue(LogicalDevice, GraphicsQueueFamilyIndex, 0, &GraphicsQueue);

		VkCommandPoolCreateInfo commandPoolCreateInfo = {};
		commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCreateInfo.queueFamilyIndex = GraphicsQueueFamilyIndex;
		commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT; // default for Dope

		const VkResult createCommandPoolVkR = vkCreateCommandPool(LogicalDevice, &commandPoolCreateInfo, nullptr, &GraphicsCommandPool);
		ASSERT(createCommandPoolVkR == VK_SUCCESS, "VKGraphicsDevice", "Creating command pool failed!");

		delete[] vkExtensionProperties;
		delete[] layerProperties;
		delete[] physicalDevices;
	}

	bool VKGraphicsDevice::does_support_features(const GraphicsDeviceFeatures* features, Array<String>& messages)
	{
		const bool baseFeaturesSupported = GraphicsDevice::does_support_features(features, messages);

		const VKGraphicsDeviceFeatures* targetVkFeatures = (const VKGraphicsDeviceFeatures*)features;
		const VKGraphicsDeviceFeatures* selfFeatures = (const VKGraphicsDeviceFeatures*)get_supported_features();
		unsigned char vkResult = 1;

		vkResult *= selfFeatures->get_vk_queues().hasAll(targetVkFeatures->get_vk_queues()) == true ? 1 : 0;

		const bool vkFeaturesSupported = vkResult == 1 ? true : false;

		return baseFeaturesSupported && vkFeaturesSupported;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL validation_debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
		if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
			LOG("VKGraphicsDevice", "%s", pCallbackData->pMessage);
		}
		return VK_FALSE;
	}


}