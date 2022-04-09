#include "Window.h"

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Window/WindowsWindow.h>
typedef DopeEngine::WindowsWindow WindowAbstraction;
#endif

namespace DopeEngine
{
	Window* Window::create(const String& title, const unsigned int width, const unsigned int height)
	{
		return new WindowAbstraction(title, width, height);
	}
	Window::Window(const String& title, const unsigned int width, const unsigned int height)
	{
		/*
		* Initialize
		*/
		Title = title;
		Width = width;
		Height = height;
	}
	unsigned int Window::get_width() const
	{
		return Width;
	}
	unsigned int Window::get_height() const
	{
		return Height;
	}
	String Window::get_title() const
	{
		return Title;
	}
	bool Window::is_visible() const
	{
		return Visibility;
	}
	void Window::swap_buffers()
	{
		/*
		* Call os implementation
		*/
		swap_buffers_impl();
	}
	void Window::poll_messages()
	{
		/*
		* Call os implementation
		*/
		poll_messages_impl();
	}
	void Window::set_title(const String& title)
	{
		/*
		* Call os implementation
		*/
		set_title_impl(title);

		/*
		* Set the title
		*/
		Title = title;
	}

	void Window::set_window_visibility(bool state)
	{
		/*
		* Call os implementation
		*/
		set_visibility_impl(state);

		/*
		* Set visibility
		*/
		Visibility = state;
	}
}