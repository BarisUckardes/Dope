#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Array.h>
#include <Engine/Application/Devices/Portable/PortableDeviceInformation.h>
#include <Engine/Application/Devices/Drivers/DeviceDriverInformation.h>
#include <Engine/Application/Window/WindowCreateDescription.h>
#include <Engine/Graphics/Device/GraphicsAPIType.h>
#include <Engine/Application/ApplicationModule.h>
#include <Engine/Application/Window/Window.h>

namespace DopeEngine
{
	class ApplicationEvent;
	class ApplicationModule;

	/// <summary>
	/// Represents the whole application
	/// </summary>
	class DOPE_ENGINE_API Application final
	{
	public:
		Application(const WindowCreateDescription& windowDescription,GraphicsAPIType requestedGraphicsApiType);
		~Application();

		/// <summary>
		/// Returns the window of this application
		/// </summary>
		/// <returns></returns>
		 Window* get_app_window() const;

		/// <summary>
		/// Starts and runs the application loop
		/// </summary>
		void run();

		/// <summary>
		/// Registers a pending module
		/// </summary>
		/// <typeparam name="TModule"></typeparam>
		/// <typeparam name="...TParameters"></typeparam>
		/// <param name="...parameters"></param>
		template<typename TModule,typename... TParameters>
		void register_pending_module(TParameters... parameters);
	private:
		/// <summary>
		/// Collects the current connected portable devices
		/// </summary>
		void collect_portable_devices();

		/// <summary>
		/// Collects current device drivers
		/// </summary>
		void collect_device_drivers();

		/// <summary>
		/// Creates the native application window
		/// </summary>
		void create_application_window(const WindowCreateDescription& windowDescription);

		/// <summary>
		/// Creates the requested graphics api type
		/// </summary>
		/// <param name="requestedApiType"></param>
		void create_graphics_device(GraphicsAPIType requestedApiType);

		/// <summary>
		/// Called when window broadcasts a new event
		/// </summary>
		/// <param name="event"></param>
		void on_receive_application_event(ApplicationEvent* event);
	private:
		Window* ApplicationWindow;
		Array<ApplicationEvent*> BufferedEvents;
		Array<ApplicationModule*> PendingModules;
		Array<ApplicationModule*> ActiveModules;
		Array<PortableDeviceInformation> PortableDeviceInformations;
		Array<DeviceDriverInformation> DeviceDriverInformations;
	};


	template<typename TModule, typename ...TParameters>
	inline void Application::register_pending_module(TParameters ...parameters)
	{
		/*
		* Create module
		*/
		TModule* module = new TModule(parameters...);

		/*
		* Register pending module
		*/
		PendingModules.add(module);
	}

}