#include "OpenGLGraphicsDevice.h"
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/OpenGL/Device/OpenGLDeviceObjects.h>
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

#ifdef _DEBUG
		glEnable(GL_DEBUG_OUTPUT);

		/*
		* Create debug
		*/
		glDebugMessageCallback(
			[](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
			{
					printf("OPENGL ERROR: %s\n", message);
			}
		, nullptr);
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
		ASSERT(gladLoadGL() != 0, "GLAD", "Glad intialization failed!");
		LOG("GLAD", "%s", *get_version());

		/*
		* Validate glad
		*/
		

		/*
		* Initialize
		*/
		WindowDeviceContext = windowDeviceContext;
		WindowOpenGLContext = gladHglrc;
	}
	void OpenGLGraphicsDevice::update_buffer_impl(Buffer* buffer, const Byte* data)
	{
		const BufferType type = buffer->get_buffer_type();
		switch (type)
		{
			case DopeEngine::BufferType::VertexBuffer:
				((OpenGLVertexBuffer*)buffer)->update(data);
				break;
			case DopeEngine::BufferType::IndexBuffer:
				((OpenGLIndexBuffer*)buffer)->update(data);
				break;
			case DopeEngine::BufferType::UniformBuffer:
				((OpenGLUniformBuffer*)buffer)->update(data);
				break;
			default:
				ASSERT(false, "OpenGLGraphicsDevice", "Invalid buffer type, cannot update the buffer!");
				break;

		}
	}
	void OpenGLGraphicsDevice::update_texture_impl(Texture* texture, const Byte* data)
	{
		/*
		* Get gl texture
		*/
		OpenGLTexture* glTexture = (OpenGLTexture*)texture;

		/*
		* Update texture data region
		*/
		const TextureFormat format = glTexture->get_format();
		const TEXTURE_HANDLE handle = glTexture->get_handle();
		glBindTexture(GL_TEXTURE_2D, handle);
		glTextureSubImage2D(handle, 0, 0, 0, glTexture->get_width(), glTexture->get_height(), OpenGLTextureUtils::get_format(format), OpenGLTextureUtils::get_data_type(format), data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void OpenGLGraphicsDevice::swap_swapchain_buffers_impl(const SwapchainFramebuffer* framebuffer)
	{
#ifdef DOPE_OS_WINDOWS
		SwapBuffers(WindowDeviceContext);
#endif
	}
	void OpenGLGraphicsDevice::wait_for_finish_impl()
	{

	}
	ResourceLayout* OpenGLGraphicsDevice::create_resource_layout_impl(const ResourceDescription& description)
	{
		/*
		* Create new opengl resource layout
		*/
		OpenGLResourceLayout* layout = new OpenGLResourceLayout(description);

		return layout;
	}
	ResourceView* OpenGLGraphicsDevice::create_resource_view_impl(const ResourceViewDescription& description)
	{
		/*
		* Create new opengl resource view
		*/
		OpenGLResourceView* view = new OpenGLResourceView(description);

		return view;
	}
	Framebuffer* OpenGLGraphicsDevice::create_window_swapchain_framebuffer_impl(const unsigned int width, const unsigned int height) const
	{
		return new OpenGLSwapchainFramebuffer(width,height,(DEVICE)this,(Window*)get_owner_window());
	}
	CommandBuffer* OpenGLGraphicsDevice::create_command_buffer_impl()
	{
		return new OpenGLCommandBuffer();
	}
	void OpenGLGraphicsDevice::submit_command_buffer_impl(CommandBuffer* commandBuffer)
	{

	}
	void OpenGLGraphicsDevice::delete_device_object_impl(DeviceObject* object)
	{

	}
	Buffer* OpenGLGraphicsDevice::create_buffer_impl(const BufferDescription& description)
	{
		/*
		* Create OpenGLBuffer
		*/
		const BufferType type = description.Type;
		switch (type)
		{
			case DopeEngine::BufferType::VertexBuffer:
				return new OpenGLVertexBuffer(description.AllocatedSize,1u,(DEVICE)this);
				break;
			case DopeEngine::BufferType::IndexBuffer:
				return new OpenGLIndexBuffer(1u,description.AllocatedSize,(DEVICE)this);
				break;
			case DopeEngine::BufferType::UniformBuffer:
				return new OpenGLUniformBuffer(description.Name,description.AllocatedSize, (DEVICE)this);
				break;
			default:
				ASSERT(false,"OpenGLGraphicsDevice", "Invalid buffer type.Cannot create buffer");
				return nullptr;
				break;
		}
	}
	Framebuffer* OpenGLGraphicsDevice::create_framebuffer_impl(const FramebufferDescription& description)
	{
		/*
		* Create OpeGL framebuffer
		*/
		OpenGLFramebuffer* framebuffer = new OpenGLFramebuffer(description, (DEVICE)this);

		return framebuffer;
	}
	Pipeline* OpenGLGraphicsDevice::create_pipeline_impl(const PipelineDescription& description)
	{
		/*
		* Create OpenGL pipeline
		*/
		OpenGLPipeline* pipeline = new OpenGLPipeline(description, (DEVICE)this);

		return pipeline;
	}
	Shader* OpenGLGraphicsDevice::create_shader_impl(const ShaderDescription& description)
	{
		/*
		* Create OpenGL shader
		*/
		OpenGLShader* shader = new OpenGLShader(description,(DEVICE)this);

		return shader;
	}
	ShaderSet* OpenGLGraphicsDevice::create_shader_set_impl(const Array<Shader*>& shaders)
	{
		/*
		* Create OpenGL shader set
		*/
		OpenGLShaderSet* shaderSet = new OpenGLShaderSet(shaders, (DEVICE)this);

		return shaderSet;
	}
	Texture* OpenGLGraphicsDevice::create_texture_impl(const TextureDescription& description)
	{
		/*
		* Create OpenGL texture
		*/
		const TextureType type = description.Type;
		switch (type)
		{
			case DopeEngine::TextureType::Texture1D:
				return nullptr;
				break;
			case DopeEngine::TextureType::Texture2D:
				return new OpenGLTexture(description, (DEVICE)this);
				break;
			case DopeEngine::TextureType::Texture3D:
				break;
				return nullptr;
			case DopeEngine::TextureType::CubeTexture:
				return nullptr;
				break;
			default:
				ASSERT(false, "OpenGLGraphicsDevice", "Cannot create texture because given texture type is invalid");
				return nullptr;
				break;
		}

	}
}