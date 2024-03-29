#include "OpenGLSwapchainFramebuffer.h"

namespace DopeEngine
{
	OpenGLSwapchainFramebuffer::OpenGLSwapchainFramebuffer(const SwapchainFramebufferDesc& desc, DEVICE device,Window* window) :
		SwapchainFramebuffer(desc,(GraphicsDevice*)device,window)
	{

	}
	OpenGLSwapchainFramebuffer::~OpenGLSwapchainFramebuffer()
	{

	}
	void OpenGLSwapchainFramebuffer::on_swapchain_resize_impl()
	{
	}
}