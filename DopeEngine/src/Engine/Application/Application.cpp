#include "Application.h"
#include <Engine/Application/Window/Window.h>
#include <Engine/Application/Devices/Portable/IPortableDeviceEnumarator.h>
#include <Engine/Application/Devices/Drivers/IDeviceDriverEnumarator.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>

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
		return Window;
	}
	void Application::collect_portable_devices()
	{
		LOG("Application","Collecting portable devices...");

		/*
		* Create portable device enumarator
		*/
		IPortableDeviceEnumarator* portableDeviceEnumarator = IPortableDeviceEnumarator::create();

		/*
		* Collect devices
		*/
		PortableDeviceInformations = portableDeviceEnumarator->enumarate_devices();

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
		
		/*
		* Free resources
		*/
		delete portableDeviceEnumarator;
	}
	void Application::collect_device_drivers()
	{
		LOG("Application", "Collecting device drivers...");

		/*
		* Create device driver enumarator
		*/
		IDeviceDriverEnumarator* driverEnumarator = IDeviceDriverEnumarator::create();

		/*
		* Collect drivers
		*/
		DeviceDriverInformations = driverEnumarator->enumarate_drivers();

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
		Window = Window::create(windowDescription);
	}
	void Application::create_graphics_device(GraphicsAPIType requestedApiType)
	{
		/*
		* Create graphics device
		*/
		GraphicsDevice* device = GraphicsDevice::create(requestedApiType, Window);
	}
}