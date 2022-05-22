#include "EditorGUIPainter.h"
#include <Engine/GUI/Renderer/GUIRenderer.h>

namespace DopeEditor
{
	EditorGUIPainter::EditorGUIPainter(DopeEngine::GraphicsDevice* device)
	{
	
		/*
		* Create renderer initialization flags
		*/
		DopeEngine::GUIRendererBackendFlags backendFlags = {};
		DopeEngine::GUIRendererConfigFlags configFlags = {};
		backendFlags = DopeEngine::GUIRendererBackendFlags::None;
		configFlags = DopeEngine::GUIRendererConfigFlags::DockingEnabled;

		/*
		* Create renderer
		*/
		Renderer = DopeEngine::GUIRenderer::create(backendFlags, configFlags, device);
	}

	EditorGUIPainter::~EditorGUIPainter()
	{
		delete Renderer;
	}

	const DopeEngine::GUIRenderingCommands* EditorGUIPainter::get_rendering_commands() const
	{
		return Renderer->get_rendering_commands();
	}

	const DopeEngine::GUIEventCommands* EditorGUIPainter::get_event_commands() const
	{
		return Renderer->get_event_commands();
	}

	void EditorGUIPainter::StartPainting()
	{
		Renderer->begin_rendering(1.0f / 60.0f);
	}

	void EditorGUIPainter::FinalizePainting(const DopeEngine::GraphicsCommandBuffer* targetCommandBuffer)
	{
		Renderer->render(targetCommandBuffer);
	}

	void EditorGUIPainter::on_painter_receive_event(const DopeEngine::ApplicationEvent* event)
	{
		Renderer->on_application_event(event);
	}

}