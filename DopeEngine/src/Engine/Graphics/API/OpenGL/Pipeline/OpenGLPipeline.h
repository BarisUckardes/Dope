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

		FORCEINLINE PROGRAM_HANDLE get_program_handle() const;
		FORCEINLINE VERTEX_LAYOUT_HANDLE get_vertex_layout_handle() const;
	private:
		void create_pipeline_state();
	private:
		VERTEX_LAYOUT_HANDLE VertexLayoutHandle;
		PROGRAM_HANDLE ProgramHandle;
		DEVICE Device;
	};


}