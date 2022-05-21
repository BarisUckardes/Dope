#include "OpenGLGUIRenderer.h"
#include <IMGUI/imgui_impl_opengl3.h>


namespace DopeEngine
{
	OpenGLGUIRenderer::OpenGLGUIRenderer(const GUIRendererBackendFlags backendFlags, const GUIRendererConfigFlags configFlags) : GUIRenderer(backendFlags,configFlags)
	{
		/*
		* Initialize gl context
		*/
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	GraphicsAPIType OpenGLGUIRenderer::get_api_type() const
	{
		return GraphicsAPIType::OpenGL;
	}
	void OpenGLGUIRenderer::begin_rendering_impl()
	{
		ImGui_ImplOpenGL3_NewFrame();
	}

	void OpenGLGUIRenderer::render_impl(const GraphicsCommandBuffer* cmdbuffer)
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}