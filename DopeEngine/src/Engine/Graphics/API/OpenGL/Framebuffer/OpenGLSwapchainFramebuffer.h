#pragma once
#include <Engine/Graphics/Framebuffer/SwapchainFramebuffer.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>

namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLSwapchainFramebuffer : public SwapchainFramebuffer
	{
	public:
		OpenGLSwapchainFramebuffer(const unsigned int width, unsigned int height, DEVICE device,Window* window);
		~OpenGLSwapchainFramebuffer();

	private:
	};


}