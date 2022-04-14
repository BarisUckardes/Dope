#include "OpenGLPipeline.h"
#include <GLAD/glad.h>
namespace DopeEngine
{
	OpenGLPipeline::OpenGLPipeline(const PipelineDescription& description,DEVICE device) : Pipeline(description)
	{
		/*
		* Initialize
		*/
		Device = device;

		/*
		* Create state
		*/
		create_pipeline_state();
	}
	PROGRAM_HANDLE OpenGLPipeline::get_program_handle() const
	{
		return ProgramHandle;
	}
	VERTEX_LAYOUT_HANDLE OpenGLPipeline::get_vertex_layout_handle() const
	{
		return VertexLayoutHandle;
	}
	void OpenGLPipeline::create_pipeline_state()
	{
		/*
		* Create vertex array
		*/
		glGenVertexArrays(1, &VertexLayoutHandle);
	}
}