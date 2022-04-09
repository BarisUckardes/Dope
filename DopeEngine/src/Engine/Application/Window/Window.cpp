#include "Window.h"

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Window/WindowsWindow.h>
typedef DopeEngine::WindowsWindow WindowAbstraction;
#endif

namespace DopeEngine
{
	Window* Window::create(const WindowCreateDescription& description)
	{
		return new WindowAbstraction(description);
	}
	GraphicsDevice* Window::get_graphics_device() const
	{
		return GDevice;
	}
	void Window::assing_graphics_device(GraphicsDevice* device)
	{
		GDevice = device;
	}
	Window::Window(const WindowCreateDescription& description)
	{
		/*
		* Initialize
		*/
		Title = description.Title;
		Width = description.Width;
		Height = description.Height;
		PositionX = description.PositionX;
		PositionY = description.PositionY;
	}
	unsigned int Window::get_width() const
	{
		return Width;
	}
	unsigned int Window::get_height() const
	{
		return Height;
	}
	unsigned int Window::get_position_x() const
	{
		return PositionX;
	}
	unsigned int Window::get_position_y() const
	{
		return PositionY;
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