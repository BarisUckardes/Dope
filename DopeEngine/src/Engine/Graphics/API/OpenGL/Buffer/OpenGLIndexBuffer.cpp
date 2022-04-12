#include "OpenGLIndexBuffer.h"
#include <GLAD/glad.h>


namespace DopeEngine
{

	OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned long range, const unsigned int elementSize, const unsigned long allocatedSize, DEVICE device) : IndexBuffer(range,elementSize,allocatedSize)
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
	void OpenGLIndexBuffer::update_impl(const Byte* data)
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
		glCreateBuffers(1, &Handle);
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