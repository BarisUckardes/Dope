#include "OpenGLShaderSet.h"
#include <Engine/Graphics/API/OpenGL/Shader/OpenGLShader.h>
#include <GLAD/glad.h>
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{
	void check_program_link(PROGRAM_HANDLE handle)
	{
#ifdef _DEBUG
		GLint state = 0;
		glGetProgramiv(handle, GL_LINK_STATUS, (int*)&state);
		if (state == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &maxLength);

			char* errorLog = new char[maxLength];
			glGetProgramInfoLog(handle, maxLength, &maxLength, errorLog);

			LOG("OpenGLShaderSet", "Program link failed with logs: %s", errorLog);
			delete[] errorLog;
		}
#endif
	}
	OpenGLShaderSet::OpenGLShaderSet(const Array<Shader*>& shaders, DEVICE device) : ShaderSet(shaders)
	{
		/*
		* Initialize
		*/
		Device = device;
		Handle = GL_NONE;

		/*
		* Create shader set (OpenGL shader program)
		*/
		create_set();
	}
	OpenGLShaderSet::~OpenGLShaderSet()
	{

	}
	PROGRAM_HANDLE OpenGLShaderSet::get_handle() const
	{
		return Handle;
	}
	void OpenGLShaderSet::create_set()
	{
		/*
		* First invalidates
		*/
		invalidate();

		/*
		* Create new program
		*/
		Handle = glCreateProgram();
		CheckGLError();

		/*
		* Attach shaders
		*/
		const Array<Shader*>& shaders = get_shaders_fast();
		for (unsigned int i = 0; i < shaders.get_cursor(); i++)
		{
			/*
			* Get shader
			*/
			const OpenGLShader* shader = (const OpenGLShader*)shaders[i];

			/*
			* Attach shader
			*/
			glAttachShader(Handle, shader->get_handle());
			CheckGLError();
		}

		/*
		* Link the program
		*/
		glLinkProgram(Handle);
		CheckGLError();

		/*
		* Check
		*/
		check_program_link(Handle);
	}
	void OpenGLShaderSet::invalidate()
	{
		/*
		* Validate and delete
		*/
		if (Handle != GL_NONE)
		{
			glDeleteProgram(Handle);
			Handle = GL_NONE;
		}
	}
}