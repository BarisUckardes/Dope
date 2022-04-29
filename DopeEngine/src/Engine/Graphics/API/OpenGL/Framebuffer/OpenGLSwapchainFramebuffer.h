#pragma once
#include <Engine/Graphics/Framebuffer/SwapchainFramebuffer.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLSwapchainFramebuffer : public SwapchainFramebuffer
	{
	public:
		OpenGLSwapchainFramebuffer(const FramebufferDescription& desc, DEVICE device,Window* window);
		~OpenGLSwapchainFramebuffer();

	protected:
		virtual void on_swapchain_resize_impl() override;
	private:
	};


}