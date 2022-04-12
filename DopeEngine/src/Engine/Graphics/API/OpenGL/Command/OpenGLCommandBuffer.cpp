#include "OpenGLCommandBuffer.h"
#include <Engine/Graphics/API/OpenGL/Device/OpenGLDeviceObjects.h>
#include <Glad/glad.h>
#include <Engine/Graphics/API/OpenGL/Pipeline/OpenGLPipelineUtils.h>
namespace DopeEngine
{
	void OpenGLCommandBuffer::set_vertex_buffer(const VertexBuffer& vertexBuffer)
	{
		glBindBuffer(GL_ARRAY_BUFFER, ((const OpenGLVertexBuffer&)vertexBuffer).get_handle());
	}
	void OpenGLCommandBuffer::set_index_buffer(const IndexBuffer& indexBuffer)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ((const OpenGLIndexBuffer&)indexBuffer).get_handle());
	}
	void OpenGLCommandBuffer::set_framebuffer(const Framebuffer& framebuffer)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, ((const OpenGLFramebuffer&)framebuffer).get_handle());
	}
	void OpenGLCommandBuffer::set_pipeline(const Pipeline& pipeline)
	{
		/*
		* Blending
		*/

		/*
		* Depth
		*/
		if (pipeline.is_depth_test_enabled())
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);

		if (pipeline.is_depth_write_enabled())
			glEnable(GL_DEPTH_WRITEMASK);
		else
			glDisable(GL_DEPTH_WRITEMASK);

		glDepthFunc(OpenGLPipelineUtils::get_depth_function(pipeline.get_depth_function()));

		/*
		* Face culling
		*/
		if (pipeline.get_cull_mode() != FaceCullMode::DontCull)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);

		glFrontFace(OpenGLPipelineUtils::get_front_face(pipeline.get_front_face()));
		glCullFace(OpenGLPipelineUtils::get_cull_mode(pipeline.get_cull_mode()));

		/*
		* Polygon fill mode
		*/
		glPolygonMode(OpenGLPipelineUtils::get_front_face(pipeline.get_front_face()), OpenGLPipelineUtils::get_fill_mode(pipeline.get_fill_mode()));

		/*
		* Set primitive
		*/
		CurrentPrimitive = OpenGLPipelineUtils::get_primitive(pipeline.get_primitives());
	}
	void OpenGLCommandBuffer::set_shader_set(const ShaderSet& shaderSet)
	{
		CurrentProgram = ((const OpenGLShaderSet&)shaderSet).get_handle();
		glUseProgram(CurrentProgram);
	}
	void OpenGLCommandBuffer::set_vertex_layout(const VertexLayout& layout)
	{
		glBindVertexArray(((const OpenGLShaderSet&)layout).get_handle());
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
	
	void OpenGLCommandBuffer::indexed_draw_call(const unsigned int count)
	{
		glDrawElements(CurrentPrimitive, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLCommandBuffer::lock_impl()
	{

	}
	void OpenGLCommandBuffer::unlock_impl()
	{

	}
}