#include "OpenGLShaderSet.h"
#include <Engine/Graphics/API/OpenGL/Shader/OpenGLShader.h>
#include <GLAD/glad.h>

namespace DopeEngine
{
	OpenGLShaderSet::OpenGLShaderSet(const Array<Shader*>& shaders, DEVICE device) : ShaderSet(shaders)
	{
		/*
		* Initialize
		*/
		Device = device;

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
		return PROGRAM_HANDLE();
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

		/*
		* Attach shaders
		*/
		const Array<Shader*> shaders = get_shaders_fast();
		for (unsigned int i = 0; shaders.get_cursor(); i++)
		{
			/*
			* Get shader
			*/
			const OpenGLShader* shader = (const OpenGLShader*)shaders[i];

			/*
			* Attach shader
			*/
			glAttachShader(Handle, shader->get_handle());
		}

		/*
		* Link the program
		*/
		glLinkProgram(Handle);
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