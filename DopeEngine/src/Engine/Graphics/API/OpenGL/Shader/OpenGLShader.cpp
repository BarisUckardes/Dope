#include "OpenGLShader.h"
#include <Engine/Graphics/API/OpenGL/Shader/OpenGLShaderUtils.h>
#include <GLAD/glad.h>

namespace DopeEngine
{
	OpenGLShader::OpenGLShader(const ShaderDescription& description, DEVICE device) : Shader(description)
	{
		/*
		* Initialize
		*/
		Device = device;
		Handle = GL_NONE;

		/*
		* Compile
		*/
		compile();
	}
	OpenGLShader::~OpenGLShader()
	{
		invalidate();
	}
	SHADER_HANDLE OpenGLShader::get_handle() const
	{
		return Handle;
	}
	void OpenGLShader::compile()
	{
		/*
		* First invalidate
		*/
		invalidate();

		/*
		* Create anew shader
		*/
		Handle = glCreateShader(OpenGLShaderUtils::get_type(get_type()));

		/*
		* Set shader source
		*/
		const GLchar* sourcePtr = get_source().get_source();
		glShaderSource(Handle,1,&sourcePtr,0);

		/*
		* Compile
		*/
		glCompileShader(Handle);
	}
	void OpenGLShader::invalidate()
	{
		/*
		* Validate and delete
		*/
		if (Handle != GL_NONE)
			glDeleteShader(Handle);
		Handle = GL_NONE;
	}
}