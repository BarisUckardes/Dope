#include "EditorGUIPainter.h"
#include <Engine/GUI/Renderer/GUIRenderer.h>

namespace DopeEditor
{
	EditorGUIPainter::EditorGUIPainter(const DopeEngine::GraphicsAPIType requestedApiType, DopeEngine::GraphicsDevice* device)
	{
	
		/*
		* Create renderer initialization flags
		*/
		DopeEngine::GUIRendererBackendFlags backendFlags = {};
		DopeEngine::GUIRendererConfigFlags configFlags = {};

		/*
		* Create renderer
		*/
		Renderer = DopeEngine::GUIRenderer::create(requestedApiType, backendFlags, configFlags, device);
	}

	EditorGUIPainter::~EditorGUIPainter()
	{
		delete Renderer;
	}

	void EditorGUIPainter::StartRendering()
	{
		Renderer->begin_rendering(1.0f / 60.0f);
	}

	void EditorGUIPainter::FinalizeRendering(const DopeEngine::GraphicsCommandBuffer* targetCommandBuffer)
	{
		Renderer->render(targetCommandBuffer);
	}

	void EditorGUIPainter::on_painter_receive_event(const DopeEngine::ApplicationEvent* event)
	{
		Renderer->on_application_event(event);
	}

}