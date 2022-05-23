#include "OpenGLShader.h"
#include <Engine/Graphics/API/OpenGL/Shader/OpenGLShaderUtils.h>
#include <GLAD/glad.h>
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{
	void check_shader_compilation(SHADER_HANDLE handle)
	{
#ifdef _DEBUG
		GLint state = 0;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &state);
		if (state == GL_FALSE)
		{
			GLint maxLength = 255;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &maxLength);

			char* errorLog = new char[maxLength];
			glGetShaderInfoLog(handle, maxLength, &maxLength, errorLog);

			LOG("OpenGLShader", "Shader compile failed with logs: %s", errorLog);
			delete[] errorLog;
		}
#endif
	}
	OpenGLShader::OpenGLShader(const ShaderDescription& description, DEVICE device) : Shader(description)
	{
		Device = device;
		Handle = GL_NONE;

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
		invalidate();

		Handle = glCreateShader(OpenGLShaderUtils::get_type(get_type()));

		const String source = this->get_source();
		const GLchar* sourcePtr = *source;

		glShaderSource(Handle,1,&sourcePtr,0);
		CheckGLError();

		glCompileShader(Handle);
		CheckGLError();

		check_shader_compilation(Handle);
	}
	void OpenGLShader::invalidate()
	{
		if (Handle != GL_NONE)
			glDeleteShader(Handle);
		Handle = GL_NONE;
	}
}