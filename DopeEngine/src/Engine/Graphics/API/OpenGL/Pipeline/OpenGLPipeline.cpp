#include "OpenGLPipeline.h"
namespace DopeEngine
{
	OpenGLPipeline::OpenGLPipeline(const PipelineDescription& description,DEVICE device) : Pipeline(description)
	{
		/*
		* Initialize
		*/
		Device = device;
	}
}