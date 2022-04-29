#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Application/Window/Window.h>
namespace DopeEngine
{
	class ApplicationEvent;
	class DOPE_ENGINE_API SwapchainFramebuffer : public Framebuffer
	{
	public:
		SwapchainFramebuffer(const FramebufferDescription& desc,GraphicsDevice* device, Window* window);
		~SwapchainFramebuffer();

		virtual OutputDescription get_output_desc() const override;
	protected:
		/// <summary>
		/// Called when swapchain is resized
		/// </summary>
		virtual void on_swapchain_resize_impl() = 0;

		GraphicsDevice* get_owner_device() const;
		Window* get_owner_window() const;
	private:
		void on_event_receive(ApplicationEvent* event);
	private:
		GraphicsDevice* OwnerDevice;
		Window* OwnerWindow;
		FramebufferDescription CreateDesc;

	};


}