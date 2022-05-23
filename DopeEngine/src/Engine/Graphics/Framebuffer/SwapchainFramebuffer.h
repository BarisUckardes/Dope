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

		FORCEINLINE unsigned int get_swapchain_buffer_count() const;
		FORCEINLINE TextureFormat get_swapchain_buffer_format() const;
		FORCEINLINE TextureFormat get_swapchain_depth_buffer_format() const;

	protected:
		GraphicsDevice* get_owner_device() const;
		Window* get_owner_window() const;

		virtual void on_swapchain_resize_impl() = 0;
	private:
		void on_window_resize(WindowResizedEvent* event);
	private:
		GraphicsDevice* OwnerDevice;
		Window* OwnerWindow;
		TextureFormat BufferFormat;
		TextureFormat DepthFormat;
		unsigned int BufferCount;

	};


}