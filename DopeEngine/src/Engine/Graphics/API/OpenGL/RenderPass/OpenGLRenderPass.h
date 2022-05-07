#pragma once
#include <Engine/Graphics/RenderPass/RenderPass.h>
#include <Engine/Graphics/API/OpenGL/Core/OpenGLCore.h>
namespace DopeEngine
{
	class DOPE_ENGINE_API OpenGLRenderPass : public RenderPass
	{
	public:
		OpenGLRenderPass(const RenderPassDesc& desc,DEVICE device);
		virtual ~OpenGLRenderPass() final override = default;

		 PROGRAM_HANDLE get_program_handle() const;
		 VERTEX_LAYOUT_HANDLE get_vertex_layout_handle() const;
	private:
		void create();
	private:
		VERTEX_LAYOUT_HANDLE VertexLayoutHandle;
		PROGRAM_HANDLE ProgramHandle;
		DEVICE Device;
	};


}