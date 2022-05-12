#include "SwapchainFramebuffer.h"
#include <Engine/Application/Events/ApplicationEvent.h>
#include <Engine/Application/Events/Window/WindowResizedEvent.h>
#include <Engine/Application/Window/Window.h>
#include <Engine/Event/Event.h>
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{
	SwapchainFramebuffer::SwapchainFramebuffer(const SwapchainFramebufferDesc& desc,GraphicsDevice* device,Window* window) :
		Framebuffer(FramebufferDescription(desc.Width,desc.Height,desc.GenerateDepth,desc.DepthFormat,Array<FramebufferAttachmentDescription>()))
	{
		/*
		* Intialize
		*/
		OwnerDevice = device;
		OwnerWindow = window;
		BufferCount = desc.Count;
		BufferFormat = desc.Format;
		DepthFormat = desc.DepthFormat;

		/*
		* Set event feed listener
		*/
		//window->set_event_feed_listener(Delegate<void,ApplicationEvent*>(BIND_TARGET_EVENT(this, SwapchainFramebuffer::on_event_receive)));

		/*
		* Set initial size
		*/
		_mark_swapchain(this);
	}
	SwapchainFramebuffer::~SwapchainFramebuffer()
	{
		OwnerDevice = nullptr;
		OwnerWindow = nullptr;
	}
	unsigned int SwapchainFramebuffer::get_swapchain_buffer_count() const
	{
		return BufferCount;
	}
	TextureFormat SwapchainFramebuffer::get_swapchain_buffer_format() const
	{
		return BufferFormat;
	}
	GraphicsDevice* SwapchainFramebuffer::get_owner_device() const
	{
		return OwnerDevice;
	}
	Window* SwapchainFramebuffer::get_owner_window() const
	{
		return OwnerWindow;
	}
	void SwapchainFramebuffer::on_window_resize(WindowResizedEvent* event)
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
	
	TextureFormat SwapchainFramebuffer::get_swapchain_depth_buffer_format() const
	{
		return DepthFormat;
	}
}