#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Application/Window/Window.h>
#include <Engine/Graphics/Texture/TextureFormat.h>
#include <Engine/Graphics/Framebuffer/SwapchainFramebufferDesc.h>
#include <Engine/Application/Events/Window/WindowResizedEvent.h>
namespace DopeEngine
{
	class ApplicationEvent;

	/// <summary>
	/// Specialized framebuffer class for Swapchains
	/// <para>Can receive window resize messages for resizing</para>
	/// </summary>
	class DOPE_ENGINE_API SwapchainFramebuffer : public Framebuffer
	{
		friend class Window;
	public:
		SwapchainFramebuffer(const SwapchainFramebufferDesc& desc,GraphicsDevice* device, Window* window);
		~SwapchainFramebuffer();

		/// <summary>
		/// Returns the buffer count for the swapchain backbuffers
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_swapchain_buffer_count() const;

		/// <summary>
		/// Returns the format of the backbuffers
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureFormat get_swapchain_buffer_format() const;

		/// <summary>
		/// Returns the format of the depth buffer
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureFormat get_swapchain_depth_buffer_format() const;

	protected:
		/// <summary>
		/// Called when swapchain is resized
		/// </summary>
		virtual void on_swapchain_resize_impl() = 0;

		/// <summary>
		/// Returns the owner graphics device
		/// </summary>
		/// <returns></returns>
		GraphicsDevice* get_owner_device() const;

		/// <summary>
		/// Returns the owner window
		/// </summary>
		/// <returns></returns>
		Window* get_owner_window() const;
	private:

		/// <summary>
		/// Internal method for receiving the window resized event
		/// </summary>
		/// <param name="event"></param>
		void on_window_resize(WindowResizedEvent* event);
	private:
		GraphicsDevice* OwnerDevice;
		Window* OwnerWindow;
		TextureFormat BufferFormat;
		TextureFormat DepthFormat;
		unsigned int BufferCount;

	};


}