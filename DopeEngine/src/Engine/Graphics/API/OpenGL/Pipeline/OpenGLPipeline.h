#pragma once
#include <Engine/Graphics/Pipeline/Pipeline.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLPipeline : public Pipeline
	{
	public:
		OpenGLPipeline(const PipelineDescription& description,DEVICE device);
		virtual ~OpenGLPipeline() final override = default;

	private:
		DEVICE Device;
	};


}