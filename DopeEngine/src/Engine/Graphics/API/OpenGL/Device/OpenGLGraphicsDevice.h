#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>

#ifdef DOPE_OS_WINDOWS
#include <Windows.h>
#endif

namespace DopeEngine
{
	class OpenGLGraphicsDevice : public GraphicsDevice
	{
	public:
		OpenGLGraphicsDevice(Window* ownerWindow);
		virtual ~OpenGLGraphicsDevice() override;



		// Inherited via GraphicsDevice
		virtual GraphicsAPIType get_api_type() const override;
		virtual String get_version() const override;
	protected:
		virtual void make_current_impl() override;
	private:
		void _create_opengl_device();
		void _create_opengl_win32_device();
	private:
#ifdef DOPE_OS_WINDOWS
		HGLRC WindowOpenGLContext;
		HDC WindowDeviceContext;
#endif

	};


}