#include "OpenGLRenderPass.h"
#include <Engine/Graphics/API/OpenGL/Shader/OpenGLShader.h>
#include <GLAD/glad.h>
namespace DopeEngine
{
	OpenGLRenderPass::OpenGLRenderPass(const RenderPassDesc& description,DEVICE device) : RenderPass(description)
	{
		/*
		* Initialize
		*/
		Device = device;

		/*
		* Create state
		*/
		create();
	}
	PROGRAM_HANDLE OpenGLRenderPass::get_program_handle() const
	{
		return ProgramHandle;
	}
	VERTEX_LAYOUT_HANDLE OpenGLRenderPass::get_vertex_layout_handle() const
	{
		return VertexLayoutHandle;
	}
	void OpenGLRenderPass::create()
	{
		/*
		* Create vertex array
		*/
		glGenVertexArrays(1, &VertexLayoutHandle);

		/*
		* Create shader program
		*/
		const Array<Shader*> shaders = get_shader_set();
		ProgramHandle = glCreateProgram();
		for (unsigned int i = 0; i < shaders.get_cursor(); i++)
		{
			/*
			* Get shader
			*/
			const OpenGLShader* shader = (const OpenGLShader*)shaders[i];
			const SHADER_HANDLE shaderHandle = shader->get_handle();

			/*
			* Attach shader
			*/
			glAttachShader(ProgramHandle, shaderHandle);
		}
		glLinkProgram(ProgramHandle);

	}
}