#include "OpenGLVertexBuffer.h"
#include <GLAD/glad.h>
#include <Engine/Core/ConsoleLog.h>
namespace DopeEngine
{

	OpenGLVertexBuffer::OpenGLVertexBuffer(const BufferDescription& desc, DEVICE device) : VertexBuffer(desc)
	{
		Device = device;

		create();
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		invalidate();
		Device = nullptr;
	}
	VERTEX_BUFFER_HANDLE OpenGLVertexBuffer::get_handle() const
	{
		return Handle;
	}
	void OpenGLVertexBuffer::update(const Byte* data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, Handle);
		glBufferSubData(GL_ARRAY_BUFFER, 0, get_allocated_size(), data);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}
	void OpenGLVertexBuffer::create()
	{
		invalidate();

		glGenBuffers(1, &Handle);
		glBindBuffer(GL_ARRAY_BUFFER, Handle);
		glBufferData(GL_ARRAY_BUFFER, get_allocated_size(), nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void OpenGLVertexBuffer::invalidate()
	{
		if (Handle == GL_NONE)
		{
			glDeleteBuffers(1, &Handle);
			Handle = GL_NONE;
		}
	}
}