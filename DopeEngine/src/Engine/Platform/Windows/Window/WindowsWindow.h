#pragma once
#include <Engine/Event/Delegate.h>
#include <Engine/Application/Window/WindowCreateDescription.h>
#include <Engine/Application/Window/Window.h>
#include <Windows.h>

namespace DopeEngine
{

	class GraphicsDevice;
	class ApplicationEvent;

	/// <summary>
	/// Windows implementation of the window class
	/// </summary>
	class DOPE_ENGINE_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const HINSTANCE processHandle, const WindowCreateDescription& description);
		WindowsWindow(const WindowCreateDescription& description);
		~WindowsWindow();

		/// <summary>
		/// Returns the win32 window handle HWND
		/// </summary>
		/// <returns></returns>
		HWND get_win32_window_handle() const;

		/// <summary>
		/// Returns the win32 device context HDC
		/// </summary>
		/// <returns></returns>
		HDC get_win32_device_context() const;
	private:
		static LRESULT CALLBACK Win32WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void _create_win32_window(const HINSTANCE processHandle);

		// Inherited via Window
		virtual void set_title_impl(const String& title) override;
		virtual void poll_messages_impl() override;
		virtual void set_visibility_impl(const bool state) override;
	private:
		HWND WindowHandle;
		HDC WindowDeviceContext;
	};


}