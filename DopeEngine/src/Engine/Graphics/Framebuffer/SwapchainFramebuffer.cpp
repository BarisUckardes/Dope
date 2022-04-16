#include "SwapchainFramebuffer.h"
#include <Engine/Application/Events/ApplicationEvent.h>
#include <Engine/Application/Events/Window/WindowResizedEvent.h>
#include <Engine/Application/Window/Window.h>
#include <Engine/Event/Event.h>
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{
	SwapchainFramebuffer::SwapchainFramebuffer(const unsigned int initialWidth, const unsigned int initialHeight,GraphicsDevice* device,Window* window) : Framebuffer(FramebufferDescription())
	{
		/*
		* Set event feed listener
		*/
		window->set_event_feed_listener(Delegate<void,ApplicationEvent*>(BIND_TARGET_EVENT(this, SwapchainFramebuffer::on_event_receive)));

		/*
		* Set initial size
		*/
		_set_width(this, initialWidth);
		_set_height(this, initialHeight);
		_mark_swapchain(this);
	}
	void SwapchainFramebuffer::on_event_receive(ApplicationEvent* event)
	{
		if (event->get_type() == ApplicationEventType::WindowResized)
		{
			WindowResizedEvent* wEvent = (WindowResizedEvent*)event;
			_set_width(this, wEvent->get_width());
			_set_height(this, wEvent->get_height());
		}
	}
}