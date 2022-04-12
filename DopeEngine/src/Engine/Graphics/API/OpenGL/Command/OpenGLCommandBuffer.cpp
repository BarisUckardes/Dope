#include "OpenGLCommandBuffer.h"
#include <Engine/Graphics/API/OpenGL/Device/OpenGLDeviceObjects.h>
#include <Glad/glad.h>
namespace DopeEngine
{
	void OpenGLCommandBuffer::set_vertex_buffer(const VertexBuffer& vertexBuffer)
	{

	}
	void OpenGLCommandBuffer::set_index_buffer(const IndexBuffer& indexBuffer)
	{

	}
	void OpenGLCommandBuffer::set_framebuffer(const Framebuffer& framebuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, ((const OpenGLFramebuffer&)framebuffer).get_handle());
	}
	void OpenGLCommandBuffer::set_pipeline(const Pipeline& pipeline)
	{

	}
	void OpenGLCommandBuffer::set_shader_set(const ShaderSet& shaderSet)
	{

	}
	void OpenGLCommandBuffer::set_vertex_layout(const VertexLayout& layout)
	{

	}
	void OpenGLCommandBuffer::clear_color(const ColorRgbaByte& color)
	{
		glClearColor(color.Red, color.Green, color.Blue, color.Alpha);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void OpenGLCommandBuffer::clear_depth(const float depth)
	{
		glClearDepth(depth);
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLCommandBuffer::lock_impl()
	{

	}
	void OpenGLCommandBuffer::unlock_impl()
	{

	}
}