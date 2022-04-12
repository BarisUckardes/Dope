#include "OpenGLVertexBuffer.h"
#include <GLAD/glad.h>
namespace DopeEngine
{

	OpenGLVertexBuffer::OpenGLVertexBuffer(const unsigned long allocatedSize, const unsigned int perVertexSize, DEVICE device) : VertexBuffer(perVertexSize,allocatedSize)
	{
		/*
		* Initialize
		*/
		Device = device;

		/*
		* Create
		*/
		create();
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		invalidate();
		Device = nullptr;
	}
	void OpenGLVertexBuffer::update_impl(const Byte* data)
	{
		/*
		* Update buffer data
		*/
		glBindBuffer(GL_ARRAY_BUFFER, Handle);
		glBufferSubData(GL_ARRAY_BUFFER, 0, get_allocated_size(), data);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void OpenGLVertexBuffer::create()
	{
		/*
		* Invalidate
		*/
		invalidate();

		/*
		* Create vertex buffer
		*/
		glDeleteBuffers(1, &Handle);

		/*
		* Allocate buffer
		*/
		glBindBuffer(GL_ARRAY_BUFFER, Handle);
		glBufferData(GL_ARRAY_BUFFER, get_allocated_size(), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void OpenGLVertexBuffer::invalidate()
	{
		/*
		* Validate and delete
		*/
		if (Handle == GL_NONE)
		{
			glDeleteBuffers(1, &Handle);
			Handle = GL_NONE;
		}
	}
}