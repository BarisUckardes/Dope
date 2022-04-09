#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/Array.h>
#include <Engine/Application/Devices/Portable/PortableDeviceInformation.h>
#include <Engine/Application/Devices/Drivers/DeviceDriverInformation.h>
#include <Engine/Application/Window/WindowCreateDescription.h>
#include <Engine/Graphics/Device/GraphicsAPIType.h>
namespace DopeEngine
{
	class Window;
	/// <summary>
	/// Represents the whole application
	/// </summary>
	class DOPE_ENGINE_API Application
	{
	public:
		Application(const WindowCreateDescription& windowDescription,GraphicsAPIType requestedGraphicsApiType);
		~Application();

		/// <summary>
		/// Returns the window of this application
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Window* get_app_window() const;

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
	private:
		Window* Window;
		Array<PortableDeviceInformation> PortableDeviceInformations;
		Array<DeviceDriverInformation> DeviceDriverInformations;
	};


}