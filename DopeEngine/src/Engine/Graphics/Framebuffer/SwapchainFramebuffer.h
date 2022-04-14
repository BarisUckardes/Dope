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
		SwapchainFramebuffer(const unsigned int initialWidth, const unsigned int initialHeight,GraphicsDevice* device, Window* window);
		~SwapchainFramebuffer() = default;

	private:
		void on_event_receive(ApplicationEvent* event);

	};


}