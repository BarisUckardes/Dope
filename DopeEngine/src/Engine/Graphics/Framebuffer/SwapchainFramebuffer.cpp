#include "SwapchainFramebuffer.h"
#include <Engine/Application/Events/ApplicationEvent.h>
#include <Engine/Application/Events/Window/WindowResizedEvent.h>
#include <Engine/Application/Window/Window.h>
#include <Engine/Event/Event.h>
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{
	SwapchainFramebuffer::SwapchainFramebuffer(const FramebufferDescription& desc,GraphicsDevice* device,Window* window) : Framebuffer(desc)
	{
		/*
		* Intialize
		*/
		OwnerDevice = device;
		OwnerWindow = window;
		CreateDesc = desc;

		/*
		* Set event feed listener
		*/
		window->set_event_feed_listener(Delegate<void,ApplicationEvent*>(BIND_TARGET_EVENT(this, SwapchainFramebuffer::on_event_receive)));

		/*
		* Set initial size
		*/
		_set_width(this, desc.Width);
		_set_height(this, desc.Height);
		_mark_swapchain(this);
	}
	SwapchainFramebuffer::~SwapchainFramebuffer()
	{
		OwnerDevice = nullptr;
		OwnerWindow = nullptr;
	}
	GraphicsDevice* SwapchainFramebuffer::get_owner_device() const
	{
		return OwnerDevice;
	}
	Window* SwapchainFramebuffer::get_owner_window() const
	{
		return OwnerWindow;
	}
	void SwapchainFramebuffer::on_event_receive(ApplicationEvent* event)
	{
		/*
		* Validate if incoming event is a window resize event
		*/
		if (event->get_type() == ApplicationEventType::WindowResized)
		{
			/*
			* Get window resize evet
			*/
			WindowResizedEvent* wEvent = (WindowResizedEvent*)event;

			/*
			* Set framebuffer width
			*/
			_set_width(this, wEvent->get_width());
			_set_height(this, wEvent->get_height());

			/*
			* Call swapchain resize impl
			*/
			on_swapchain_resize_impl();
		}
	}
	OutputDescription SwapchainFramebuffer::get_output_desc() const
	{
		/*
		* Collect texture formats
		*/
		Array<TextureFormat> formats;
		for (unsigned int i = 0; i < CreateDesc.AttachmentDescriptions.get_cursor(); i++)
		{

			/*
			* Register format
			*/
			formats.add(CreateDesc.AttachmentDescriptions[i].Format);
		}

		return { 0,0,Width,Height,formats };
	}
}