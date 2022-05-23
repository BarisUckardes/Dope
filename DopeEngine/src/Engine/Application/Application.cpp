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
#include <Engine/GUI/Renderer/GUIRenderer.h>

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
			ApplicationModule* module = PendingModules[i];

			module->_set_owner_session(session);
			module->initialize();

			ActiveModules.add(module);
		}
		PendingModules.clear();

		ApplicationWindow->set_visibility(true);

		while (!shouldExit)
		{

			ApplicationWindow->poll_messages();
			for (unsigned int eventIndex = 0; eventIndex < BufferedEvents.get_cursor(); eventIndex++)
			{
				ApplicationEvent* event = BufferedEvents[eventIndex];

				for (int moduleIndex = ActiveModules.get_cursor() - 1; moduleIndex > 0; moduleIndex--)
				{
					ActiveModules[moduleIndex]->on_receive_application_event(event);

					if (event->is_handled())
					{
						break;
					}
				}
			}

			for (unsigned int i = 0; i < BufferedEvents.get_cursor(); i++)
			{
				delete BufferedEvents[i];
			}
			BufferedEvents.clear();

			for (unsigned int i = 0; i < ActiveModules.get_cursor(); i++)
			{
				ActiveModules[i]->update();
			}

			ApplicationWindow->present();

			if (ApplicationWindow->has_close_request())
			{
				shouldExit = true;
				exitReasonMessage = "Window closed";
			}
		}

		for (unsigned int i = 0; i < ActiveModules.get_cursor(); i++)
		{
			ApplicationModule* module = ActiveModules[i];

			module->finalize();
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
		PortableDeviceEnumarator portableDeviceEnumarator;
		PortableDeviceInformations = portableDeviceEnumarator.enumarate_devices();
	}
	void Application::collect_device_drivers()
	{
		DeviceDriverEnumarator driverEnumarator;
		DeviceDriverInformations = driverEnumarator.enumarate_drivers();
	}
	void Application::create_application_window(const WindowCreateDescription& windowDescription)
	{
		ApplicationWindow = Window::create_window(windowDescription);

		ApplicationWindow->register_event_feed_listener(Delegate<void, ApplicationEvent*>(BIND_TARGET_EVENT(this,Application::on_receive_application_event)));
	}
	void Application::create_graphics_device(GraphicsAPIType requestedApiType)
	{
		GraphicsDeviceFeaturesDesc requestedFeaturesDesc = {};
		GraphicsDeviceFeatures* requestedFeatures = nullptr;

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
		
		SwapchainFramebufferDesc swapchainDesc = {};
		swapchainDesc.Width = ApplicationWindow->get_width();
		swapchainDesc.Height = ApplicationWindow->get_height();
		swapchainDesc.BufferCount = 3;
		swapchainDesc.Format = TextureFormat::RGBA8unorm;
		swapchainDesc.GenerateDepth = false;
		swapchainDesc.DepthFormat = TextureFormat::R8unorm;

		ApplicationGraphicsDevice = GraphicsDevice::create(requestedFeatures,requestedApiType, ApplicationWindow,&swapchainDesc);
	}
	void Application::create_audio_device(AudioAPIType requestedApiType)
	{
		ApplicationAudioDevice = AudioDevice::create(requestedApiType);
	}
	void Application::on_receive_application_event(ApplicationEvent* event)
	{
		BufferedEvents.add(event);
	}
}