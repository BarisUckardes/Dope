#pragma once
#include <Engine/Graphics/Framebuffer/Framebuffer.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>

namespace DopeEngine
{
	/// <summary>
	/// OpenGL implementation of a framebuffer
	/// </summary>
	class DOPE_ENGINE_API OpenGLFramebuffer final : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferDescription& description, DEVICE device);
		virtual ~OpenGLFramebuffer() final override;

		/// <summary>
		/// Returns the framebuffer handle
		/// </summary>
		/// <returns></returns>
		FORCEINLINE FRAMEBUFFER_HANDLE get_handle() const;
	private:
		void invalidate();
		void create();
	private:
		FRAMEBUFFER_HANDLE Handle;
		DEVICE Device;
	};


}