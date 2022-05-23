#include "OpenGLGraphicsDevice.h"
#include <Engine/Core/Assert.h>
#include <Engine/Graphics/API/OpenGL/Device/OpenGLDeviceObjects.h>
#include <Engine/Graphics/Device/GraphicsDeviceFeatures.h>
#include <GLAD/glad.h>
#include <gl/GL.h>

#ifdef DOPE_OS_WINDOWS
#include <Engine/Platform/Windows/Window/WindowsWindow.h>
#include <Engine/Memory/Memory.h>
#include <Engine/Graphics/Device/GraphicsDeviceFeaturesDesc.h>
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
		glDebugMessageCallback(
			[](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
			{
					printf("OPENGL ERROR: %s\n", message);
			}
		, nullptr);
#endif
	
		/*
		* Collect base graphics device features
		*/
		GraphicsDeviceFeaturesDesc baseFeaturesDesc = {};
		Memory::memory_set(&baseFeaturesDesc, 0, sizeof(GraphicsDeviceFeaturesDesc));
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, (GLint*)&baseFeaturesDesc.MaxColorAttachments);
		glGetBooleanv(GL_COMPUTE_SHADER, (GLboolean*)&baseFeaturesDesc.ComputeShader);
		glGetBooleanv(GL_GEOMETRY_SHADER, (GLboolean*)&baseFeaturesDesc.GeometryShader);
		glGetBooleanv(GL_TESS_CONTROL_SHADER, (GLboolean*)&baseFeaturesDesc.TesellationShader);
		//glGetBooleanv(GL_MAX_VIEWPORTS, (GLboolean*)&baseFeaturesDesc.MultipleViewports);
		glGetBooleanv(GL_COMPUTE_SHADER, (GLboolean*)&baseFeaturesDesc.ShadingRate);
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, (GLint*)&baseFeaturesDesc.MaxColorAttachments);
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, (GLint*)&baseFeaturesDesc.MaxColorAttachments);
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, (GLint*)&baseFeaturesDesc.MaxColorAttachments);
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, (GLint*)&baseFeaturesDesc.MaxColorAttachments);
		glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, (GLint*)&baseFeaturesDesc.MaxColorAttachments);
		GraphicsDeviceFeaturesDesc featuresDesc = {};
		GraphicsDeviceFeatures* features = new GraphicsDeviceFeatures(featuresDesc);
		set_features(features);

		const String vendor((const char*)glGetString(GL_VENDOR));
		const String model((const char*)glGetString(GL_RENDERER));
		GraphicsDeviceProperties properties(vendor, model);
		set_properties(properties);

	}
	void OpenGLGraphicsDevice::_create_opengl_win32_device()
	{
		/*
		* We will create an dummy opengl context, this dummy context is a very old version of OpenGL.
		* It's name goes as wGL(Windows GL) and it's the version which windows supports.
		* After creating the wGL context we will use the dummy context as a startup context and create our desired current OpenGL context which will be 4.6
		*/

		WindowAbstraction* winWindow = (WindowAbstraction*)get_owner_window();

		HWND windowHandle = winWindow->get_win32_window_handle();
		HDC windowDeviceContext = winWindow->get_win32_device_context();

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

		const int pixelFormatIndex = ChoosePixelFormat(windowDeviceContext, &pfd);
		ASSERT(pixelFormatIndex != 0, "GLAD", "Invalid pixel format");

		SetPixelFormat(windowDeviceContext, pixelFormatIndex, &pfd);

		HGLRC tempContext = wglCreateContext(windowDeviceContext);
		ASSERT(tempContext != NULL, "Win32 HGLRC", "Create wgl dummy context failed!");

		wglMakeCurrent(windowDeviceContext, tempContext);

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

		ASSERT(gladLoadGL() != 0, "GLAD", "Glad intialization failed!");
		LOG("GLAD", "%s", *get_version());

		WindowDeviceContext = windowDeviceContext;
		WindowOpenGLContext = gladHglrc;
	}
	void OpenGLGraphicsDevice::update_buffer_impl(GraphicsBuffer* buffer, const Byte* data)
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
		OpenGLTexture* glTexture = (OpenGLTexture*)texture;

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
	bool OpenGLGraphicsDevice::does_support_features(const GraphicsDeviceFeatures* features, Array<String>& messages)
	{
		return true;
	}
	GraphicsResource* OpenGLGraphicsDevice::create_resource_impl(const GraphicsResourceDesc& desc)
	{
		OpenGLResourceView* view = new OpenGLResourceView(desc);

		return view;
	}
	Framebuffer* OpenGLGraphicsDevice::create_window_swapchain_framebuffer_impl(const SwapchainFramebufferDesc* desc) const
	{
		return new OpenGLSwapchainFramebuffer(*desc,
			(DEVICE)this,
			(Window*)get_owner_window());
	}
	GraphicsCommandBuffer* OpenGLGraphicsDevice::create_command_buffer_impl()
	{
		return new OpenGLCommandBuffer();
	}
	void OpenGLGraphicsDevice::submit_command_buffer_impl(GraphicsCommandBuffer* GraphicsCommandBuffer)
	{

	}
	void OpenGLGraphicsDevice::delete_device_object_impl(GraphicsDeviceObject* object)
	{

	}
	GraphicsBuffer* OpenGLGraphicsDevice::create_buffer_impl(const BufferDescription& description)
	{
		const BufferType type = description.Type;
		switch (type)
		{
			case DopeEngine::BufferType::VertexBuffer:
				return new OpenGLVertexBuffer(description, (DEVICE)this);
				break;
			case DopeEngine::BufferType::IndexBuffer:
				return new OpenGLIndexBuffer(description, (DEVICE)this);
				break;
			case DopeEngine::BufferType::UniformBuffer:
				return new OpenGLUniformBuffer(description, (DEVICE)this);
				break;
			default:
				ASSERT(false,"OpenGLGraphicsDevice", "Invalid buffer type.Cannot create buffer");
				return nullptr;
				break;
		}
	}
	Framebuffer* OpenGLGraphicsDevice::create_framebuffer_impl(const FramebufferDescription& description)
	{
		OpenGLFramebuffer* framebuffer = new OpenGLFramebuffer(description, (DEVICE)this);

		return framebuffer;
	}
	RenderPass* OpenGLGraphicsDevice::create_render_pass_impl(const RenderPassDesc& desc)
	{
		return new OpenGLRenderPass(desc, (DEVICE)this);;
	}
	Shader* OpenGLGraphicsDevice::create_shader_impl(const ShaderDescription& description)
	{
		OpenGLShader* shader = new OpenGLShader(description,(DEVICE)this);

		return shader;
	}
	Texture* OpenGLGraphicsDevice::create_texture_impl(const TextureDescription& description)
	{
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