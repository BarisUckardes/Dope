#include "OpenGLSwapchainFramebuffer.h"

namespace DopeEngine
{
	OpenGLSwapchainFramebuffer::OpenGLSwapchainFramebuffer(const unsigned int width, unsigned int height, DEVICE device,Window* window) : SwapchainFramebuffer(width,height,(GraphicsDevice*)device,window)
	{

	}
	OpenGLSwapchainFramebuffer::~OpenGLSwapchainFramebuffer()
	{

	}
}