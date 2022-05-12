#include "Application.h"
#include <Engine/Application/Window/Window.h>
#include <Engine/Application/Devices/Portable/PortableDeviceEnumarator.h>
#include <Engine/Application/Devices/Drivers/DeviceDriverEnumarator.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/Event/Delegate.h>
#include <Engine/Application/ApplicationModule.h>
#include <Engine/Application/Events/ApplicationEvent.h>
#include <Engine/Application/Session/GameSession.h>
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDeviceFeaturesDesc.h>
#include <Engine/Graphics/API/Vulkan/Device/VKGraphicsDeviceFeatures.h>
#include <Engine/Graphics/Framebuffer/SwapchainFramebufferDesc.h>
#include <Engine/Audio/Device/AudioDevice.h>

namespace DopeEngine
{
	Application::Application(const WindowCreateDescription& windowDescription,GraphicsAPIType requestGraphicsApi,const AudioAPIType requestedAudioApiType)
	{
		collect_portable_devices();
		collect_device_drivers();
		create_application_window(windowDescription);
		create_graphics_device(requestGraphicsApi);
		create_audio_device(requestedAudioApiType);
	}
	Application::~Application()
	{

	}
	Window* Application::get_app_window() const
	{
		return ApplicationWindow;
	}
	void Application::run()
	{
		/*
		* Create states
		*/
		String exitReasonMessage = "None";
		bool shouldExit = false;

		/*
		* Create game session
		*/
		GameSession* session = new GameSession(ApplicationWindow);

		/*
		* Initialize pending modules
		*/
		for (unsigned int i = 0; i < PendingModules.get_cursor(); i++)
		{
			/*
			* Get module
			*/
			ApplicationModule* module = PendingModules[i];

			/*
			* Set owner session
			*/
			module->_set_owner_session(session);

			/*
			* Initialize module
			*/
			module->initialize();

			/*
			* Register to modules
			*/
			ActiveModules.add(module);
		}
		PendingModules.clear();

		/*
		* Make window visible
		*/
		ApplicationWindow->set_visibility(true);

		/*
		* Run app loop
		*/
		while (!shouldExit)
		{
			/*
			* Poll window events
			*/
			ApplicationWindow->poll_messages();

			/*
			* Broadcast events
			*/
			for (unsigned int eventIndex = 0; eventIndex < BufferedEvents.get_cursor(); eventIndex++)
			{
				/*
				* Get event
				*/
				ApplicationEvent* event = BufferedEvents[eventIndex];
				for (int moduleIndex = ActiveModules.get_cursor() - 1; moduleIndex > 0; moduleIndex--)
				{
					/*
					* Broadcast event to the module
					*/
					ActiveModules[moduleIndex]->on_receive_application_event(event);

					/*
					* Validate if the event is handled or not
					*/
					if (event->is_handled())
					{
						break;
					}
				}
			}

			/*
			* Clear buffered events
			*/
			for (unsigned int i = 0; i < BufferedEvents.get_cursor(); i++)
			{
				delete BufferedEvents[i];
			}
			BufferedEvents.clear();

			/*
			* Update modules
			*/
			for (unsigned int i = 0; i < ActiveModules.get_cursor(); i++)
			{
				ActiveModules[i]->update();
			}

			/*
			* Validate window should close
			*/
			if (ApplicationWindow->has_close_request())
			{
				shouldExit = true;
				exitReasonMessage = "Window closed";
			}
		}

		/*
		* Finalize modules
		*/
		for (unsigned int i = 0; i < ActiveModules.get_cursor(); i++)
		{
			/*
			* Get module
			*/
			ApplicationModule* module = ActiveModules[i];
			const String className = module->get_module_class_name();

			/*
			* Finalize module
			*/
			module->finalize();

			/*
			* Free heap memory
			*/
			delete module;
		}
		ActiveModules.clear();

		/*
		* Log exit reason
		*/
		LOG("Application", "Terminated, reason: %s", *exitReasonMessage);

	}
	void Application::collect_portable_devices()
	{


		/*
		* Create portable device enumarator
		*/
		PortableDeviceEnumarator portableDeviceEnumarator;

		/*
		* Collect devices
		*/
		PortableDeviceInformations = portableDeviceEnumarator.enumarate_devices();

		/*
		* Simple debug
		*/
		for (unsigned int i = 0; i < PortableDeviceInformations.get_cursor(); i++)
		{
			const PortableDeviceInformation& deviceInformation = PortableDeviceInformations[i];
			/*LOG("Application","Portable Device -> Manufacturer: %s,\nFriendly Name: %s\n,Description:%s\n",
				*deviceInformation.get_manufacturer(),
				*deviceInformation.get_friendly_name(),
				*deviceInformation.get_description())*/
		}
	}
	void Application::collect_device_drivers()
	{

		/*
		* Create device driver enumarator
		*/
		DeviceDriverEnumarator driverEnumarator;

		/*
		* Collect drivers
		*/
		DeviceDriverInformations = driverEnumarator.enumarate_drivers();

		/*
		* Simple debug
		*/
		for (unsigned int i = 0; i < DeviceDriverInformations.get_cursor(); i++)
		{
			const DeviceDriverInformation& driverInformation = DeviceDriverInformations[i];
			//LOG("Application", "Device Driver -> Manufacturer: %s", *driverInformation.get_base_name());
		}
		

		/*
		* Free resources
		*/
	}
	void Application::create_application_window(const WindowCreateDescription& windowDescription)
	{
		/*
		* Create window
		*/
		ApplicationWindow = Window::create_window(windowDescription);

		/*
		* Set feed
		*/
		ApplicationWindow->register_event_feed_listener(Delegate<void, ApplicationEvent*>(BIND_TARGET_EVENT(this,Application::on_receive_application_event)));
	}
	void Application::create_graphics_device(GraphicsAPIType requestedApiType)
	{
		/*
		* Create requested graphics device features
		*/
		GraphicsDeviceFeaturesDesc requestedFeaturesDesc = {};
		GraphicsDeviceFeatures* requestedFeatures = nullptr;

		/*
		* Catch api type and request default features
		*/
		switch (requestedApiType)
		{
			case DopeEngine::GraphicsAPIType::Undefined:
				break;
			case DopeEngine::GraphicsAPIType::OpenGL:
				break;
			case DopeEngine::GraphicsAPIType::Directx11:
			{
				GraphicsDeviceFeaturesDesc featuresDesc = {};
				requestedFeatures = new GraphicsDeviceFeatures(featuresDesc);
				break;
			}
			case DopeEngine::GraphicsAPIType::Directx12:
				break;
			case DopeEngine::GraphicsAPIType::Vulkan:
			{
				VKGraphicsDeviceFeaturesDesc vkFeatures = {};
				vkFeatures.QueueFamilies.add({ VK_QUEUE_GRAPHICS_BIT,1,99 });
				vkFeatures.QueueFamilies.add({ VK_QUEUE_COMPUTE_BIT,1,999 });
				requestedFeatures = new VKGraphicsDeviceFeatures(vkFeatures, GraphicsDeviceFeaturesDesc());
				break;
			}
			default:
				break;
		}
		
		/*
		* Create swapchain desc
		*/
		SwapchainFramebufferDesc swapchainDesc = {};
		swapchainDesc.Width = ApplicationWindow->get_width();
		swapchainDesc.Height = ApplicationWindow->get_height();
		swapchainDesc.Count = 3;
		swapchainDesc.Format = TextureFormat::RGBA8unorm;
		swapchainDesc.GenerateDepth = false;
		swapchainDesc.DepthFormat = TextureFormat::R8unorm;

		/*
		* Create graphics device
		*/
		ApplicationGraphicsDevice = GraphicsDevice::create(requestedFeatures,requestedApiType, ApplicationWindow,&swapchainDesc);
	}
	void Application::create_audio_device(AudioAPIType requestedApiType)
	{
		/*
		* Create audio device
		*/
		ApplicationAudioDevice = AudioDevice::create(requestedApiType);

	}
	void Application::on_receive_application_event(ApplicationEvent* event)
	{
		BufferedEvents.add(event);
	}
}