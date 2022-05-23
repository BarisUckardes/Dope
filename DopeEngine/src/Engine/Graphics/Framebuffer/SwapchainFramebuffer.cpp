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
		OwnerDevice = device;
		OwnerWindow = window;
		BufferCount = desc.BufferCount;
		BufferFormat = desc.Format;
		DepthFormat = desc.DepthFormat;

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
		const WindowResizedEvent* wEvent = (const WindowResizedEvent*)event;

		_set_width(this, wEvent->get_width());
		_set_height(this, wEvent->get_height());

		on_swapchain_resize_impl();
	}
	
	TextureFormat SwapchainFramebuffer::get_swapchain_depth_buffer_format() const
	{
		return DepthFormat;
	}
}