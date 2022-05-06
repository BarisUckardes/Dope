#include "OpenGLIndexBuffer.h"
#include <GLAD/glad.h>
#include <Engine/Core/ConsoleLog.h>


namespace DopeEngine
{

	OpenGLIndexBuffer::OpenGLIndexBuffer(const BufferDescription& desc, DEVICE device) : IndexBuffer(desc)
	{
		/*
		* Initialize
		*/
		Device = device;
		Handle = GL_NONE;

		/*
		* create
		*/
		create();
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		invalidate();
	}
	INDEX_BUFFER_HANDLE OpenGLIndexBuffer::get_handle() const
	{
		return Handle;
	}
	void OpenGLIndexBuffer::update(const Byte* data)
	{
		/*
		* Update buffer data
		*/
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Handle);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, get_allocated_size(), data);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void OpenGLIndexBuffer::create()
	{
		/*
		* First invalidate
		*/
		invalidate();

		/*
		* Create buffer
		*/
		glGenBuffers(1, &Handle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Handle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, get_allocated_size(), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
	void OpenGLIndexBuffer::invalidate()
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