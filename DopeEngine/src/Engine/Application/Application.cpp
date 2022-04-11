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

namespace DopeEngine
{
	Application::Application(const WindowCreateDescription& windowDescription,GraphicsAPIType requestGraphicsApi)
	{
		collect_portable_devices();
		collect_device_drivers();
		create_application_window(windowDescription);
		create_graphics_device(requestGraphicsApi);
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

			/*
			* Log
			*/
			LOG("Application", "The pending module[%s] is initialized and registered to the active module list of the application!",*module->get_module_class_name());
		}
		PendingModules.clear();

		/*
		* Make window visible
		*/
		ApplicationWindow->set_window_visibility(true);

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
			* Swapbuffers
			*/
			ApplicationWindow->swap_buffers();

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

			/*
			* Log
			*/
			LOG("Application", "The active module[%s] is finalized and removed from the active module list of the application!", *className);
		}
		ActiveModules.clear();

		/*
		* Log exit reason
		*/
		LOG("Application", "Terminated, reason: %s", *exitReasonMessage);

	}
	void Application::collect_portable_devices()
	{
		LOG("Application","Collecting portable devices...");

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
			LOG("Application","Portable Device -> Manufacturer: %s,\nFriendly Name: %s\n,Description:%s\n",
				*deviceInformation.get_manufacturer(),
				*deviceInformation.get_friendly_name(),
				*deviceInformation.get_description())
		}
		LOG("Application", "Portable devices collected!");
	}
	void Application::collect_device_drivers()
	{
		LOG("Application", "Collecting device drivers...");

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
			LOG("Application", "Device Driver -> Manufacturer: %s", *driverInformation.get_base_name());
		}
		
		LOG("Application", "Device drivers collected!");

		/*
		* Free resources
		*/
	}
	void Application::create_application_window(const WindowCreateDescription& windowDescription)
	{
		/*
		* Create window
		*/
		ApplicationWindow = new Window(windowDescription);

		/*
		* Set feed
		*/
		ApplicationWindow->set_application_event_feed(Delegate<void, ApplicationEvent*>(BIND_TARGET_EVENT(this,Application::on_receive_application_event)));
	}
	void Application::create_graphics_device(GraphicsAPIType requestedApiType)
	{
		/*
		* Create graphics device
		*/
		GraphicsDevice* device = GraphicsDevice::create(requestedApiType, ApplicationWindow);
	}
	void Application::on_receive_application_event(ApplicationEvent* event)
	{
		BufferedEvents.add(event);
	}
}