#include "OpenGLUniformBuffer.h"
#include <GLAD/glad.h>

namespace DopeEngine
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(const String& name,const unsigned long allocatedSize, DEVICE device) : UniformBuffer(name,allocatedSize)
	{
		/*
		* Initialize
		*/
		Device = device;
		Handle = GL_NONE;
	}
	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		invalidate();
		Device = GL_NONE;
	}
	UNIFORM_BUFFER_HANDLE OpenGLUniformBuffer::get_handle() const
	{
		return Handle;
	}
	void OpenGLUniformBuffer::update_impl(const Byte* data)
	{
		/*
		* Update
		*/
		glBindBuffer(GL_UNIFORM_BUFFER, Handle);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, get_allocated_size(), data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
	void OpenGLUniformBuffer::create()
	{
		/*
		* First invalidate
		*/
		invalidate();

		/*
		* Create
		*/
		glCreateBuffers(1, &Handle);
		glBindBuffer(GL_UNIFORM_BUFFER, Handle);
		glBufferData(GL_UNIFORM_BUFFER, get_allocated_size(), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
	void OpenGLUniformBuffer::invalidate()
	{
		/*
		* Validate and delete
		*/
		if (Handle != GL_NONE)
		{
			glDeleteBuffers(1, &Handle);
			Handle = GL_NONE;
		}
	}
}