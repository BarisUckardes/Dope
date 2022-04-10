#include "Window.h"
#include <Engine/Application/Events/ApplicationEvent.h>

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Window/WindowsWindow.h>
typedef DopeEngine::WindowsWindow WindowAbstraction;
#endif
#include <Engine/Core/ConsoleLog.h>

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
	bool Window::has_close_request() const
	{
		return CloseRequest;
	}
	void Window::assing_graphics_device(GraphicsDevice* device)
	{
		GDevice = device;
	}
	void Window::set_application_event_feed(const Delegate<void, ApplicationEvent*>& functionDelegate)
	{
		ApplicationEventFeedDelegate = functionDelegate;
	}
	void Window::set_close_request()
	{
		CloseRequest = true;
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
		CloseRequest = false;
	}
	void Window::broadcast_application_event(ApplicationEvent* event)
	{
		/*
		* Catch events
		*/
	     const ApplicationEventType type = event->get_type();

		 switch (type)
		 {
			 case DopeEngine::ApplicationEventType::Undefined:
				 break;
			 case DopeEngine::ApplicationEventType::KeyboardKeyDown:
				 break;
			 case DopeEngine::ApplicationEventType::KeyboardKeyUp:
				 break;
			 case DopeEngine::ApplicationEventType::KeyboardChar:
				 break;
			 case DopeEngine::ApplicationEventType::WindowResized:
				 break;
			 case DopeEngine::ApplicationEventType::WindowClosed:
				 CloseRequest = true;
				 break;
			 case DopeEngine::ApplicationEventType::WindowPositionChanged:
				 break;
			 case DopeEngine::ApplicationEventType::MouseButtonDown:
				 break;
			 case DopeEngine::ApplicationEventType::MouseButtonUp:
				 break;
			 case DopeEngine::ApplicationEventType::MouseScrolled:
				 break;
			 case DopeEngine::ApplicationEventType::MousePositionChanged:
				 break;
			 case DopeEngine::ApplicationEventType::WindowFileDrop:
				 break;
			 default:
				 break;

		 }

		/*
		* Forward event to application feed
		*/
		ApplicationEventFeedDelegate.invoke(event);

		/*
		* Dummy debug
		*/
		//LOG("Window", "Event broacasting -> %s", *event->get_as_string());
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