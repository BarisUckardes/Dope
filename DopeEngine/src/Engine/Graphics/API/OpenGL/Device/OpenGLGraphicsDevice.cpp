#include "OpenGLGraphicsDevice.h"
#include <Engine/Core/Assert.h>
#include <GLAD/glad.h>
#include <gl/GL.h>

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Window/WindowsWindow.h>
typedef DopeEngine::WindowsWindow WindowAbstraction;
typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int* attribList);
typedef const char* (WINAPI* PFNWGLGETEXTENSIONSSTRINGEXTPROC)(void);
typedef BOOL(WINAPI* PFNWGLSWAPINTERVALEXTPROC)(int);
typedef int (WINAPI* PFNWGLGETSWAPINTERVALEXTPROC) (void);
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0X2092
#define WGL_CONTEXT_FLAGS_ARB 0X2094
#define WGL_CONTEXT_COREPROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#endif

namespace DopeEngine
{
	

	OpenGLGraphicsDevice::OpenGLGraphicsDevice(Window* ownerWindow) : GraphicsDevice(ownerWindow)
	{
		_create_opengl_device();
	}
	OpenGLGraphicsDevice::~OpenGLGraphicsDevice()
	{

	}
	GraphicsAPIType OpenGLGraphicsDevice::get_api_type() const
	{
		return GraphicsAPIType::OpenGL;
	}
	String OpenGLGraphicsDevice::get_version() const
	{
		return (const char*)glGetString(GL_VERSION);
	}
	void OpenGLGraphicsDevice::make_current_impl()
	{
		wglMakeCurrent(WindowDeviceContext, WindowOpenGLContext);
	}
	void OpenGLGraphicsDevice::_create_opengl_device()
	{
		
#ifdef DOPE_OS_WINDOWS
		_create_opengl_win32_device();
#endif

	}
	void OpenGLGraphicsDevice::_create_opengl_win32_device()
	{
		/*
		* Get required variables
		*/
		WindowAbstraction* winWindow = (WindowAbstraction*)get_owner_window();
		HWND windowHandle = winWindow->get_win32_window_handle();
		HDC windowDeviceContext = winWindow->get_win32_device_context();

		/*
		* Create pixel format desc
		*/
		PIXELFORMATDESCRIPTOR pfd = { sizeof(pfd),1 };
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.nVersion = 1;
		pfd.cColorBits = 32;
		pfd.cAlphaBits = 8;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		/*
		* Get pixel format
		*/
		const int pixelFormatIndex = ChoosePixelFormat(windowDeviceContext, &pfd);

		/*
		* Validate format
		*/
		ASSERT(pixelFormatIndex != 0, "GLAD", "Invalid pixel format");

		/*
		* Set pixel format
		*/
		SetPixelFormat(windowDeviceContext, pixelFormatIndex, &pfd);

		/*
		* Setup temp context
		*/
		HGLRC tempContext = wglCreateContext(windowDeviceContext);

		/*
		* Validate temp context
		*/
		ASSERT(tempContext != NULL, "Win32 HGLRC", "Create wgl dummy context failed!");

		/*
		* Make context current
		*/
		wglMakeCurrent(windowDeviceContext, tempContext);

		/*
		* Create actual context
		*/
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

		const int attribList[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 5,
			WGL_CONTEXT_FLAGS_ARB, 0,
			WGL_CONTEXT_PROFILE_MASK_ARB,
			WGL_CONTEXT_COREPROFILE_BIT_ARB, 0,
		};

		HGLRC gladHglrc = wglCreateContextAttribsARB(windowDeviceContext, 0, attribList);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempContext);
		wglMakeCurrent(windowDeviceContext, gladHglrc);


		/*
		* Init glad
		*/
		int gladInitState = gladLoadGL();
		LOG("GLAD", "%s", *get_version());

		/*
		* Validate glad
		*/
		ASSERT(gladInitState != 0, "GLAD", "Glad intialization failed!");

		/*
		* Initialize
		*/
		WindowDeviceContext = windowDeviceContext;
		WindowOpenGLContext = gladHglrc;
	}
}