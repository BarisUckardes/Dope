#pragma once
#include <Engine/Application/Window/Window.h>
#include <Windows.h>
namespace DopeEngine
{

	/// <summary>
	/// Windows implementation of the window class
	/// </summary>
	class DOPE_ENGINE_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const HINSTANCE processHandle, const String& title, const unsigned int width, const unsigned int height);
		WindowsWindow(const String& title, const unsigned int width, const unsigned int height);
		virtual ~WindowsWindow() override;

		/// <summary>
		/// Returns the win32 window handle HWND
		/// </summary>
		/// <returns></returns>
		FORCEINLINE HWND get_win32_window_handle() const;

		/// <summary>
		/// Returns the win32 device context HDC
		/// </summary>
		/// <returns></returns>
		FORCEINLINE HDC get_win32_device_context() const;

	protected:
		// Inherited via Window
		virtual void set_visibility_impl(const bool state) override;
		virtual void set_title_impl(const String& title) override;
		virtual void swap_buffers_impl() override;
		virtual void poll_messages_impl() override;

	private:
		void _create_win32_window(const HINSTANCE processHandle);
	private:
		HWND WindowHandle;
		HDC WindowDeviceContext;
	};


}