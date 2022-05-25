#include "EditorGUIPainter.h"
#include <Engine/GUI/Renderer/GUIRenderer.h>

namespace DopeEditor
{
	EditorGUIPainter::EditorGUIPainter(DopeEngine::GraphicsDevice* device)
	{
		DopeEngine::GUIRendererBackendFlags backendFlags = {};
		DopeEngine::GUIRendererConfigFlags configFlags = {};
		backendFlags = DopeEngine::GUIRendererBackendFlags::None;
		configFlags = DopeEngine::GUIRendererConfigFlags::DockingEnabled;

		Renderer = DopeEngine::GUIRenderer::create(backendFlags, configFlags, device);
	}

	EditorGUIPainter::~EditorGUIPainter()
	{
		delete Renderer;
	}

	DopeEngine::GUIRenderingCommands* EditorGUIPainter::get_rendering_commands() const
	{
		return Renderer->get_rendering_commands();
	}

	DopeEngine::GUIEventCommands* EditorGUIPainter::get_event_commands() const
	{
		return Renderer->get_event_commands();
	}

	DopeEngine::GUILayoutCommands* EditorGUIPainter::get_layout_commands() const
	{
		return Renderer->get_layout_commands();
	}

	void EditorGUIPainter::StartPainting()
	{
		Renderer->begin_rendering(1.0f / 60.0f);
	}

	void EditorGUIPainter::FinalizePainting(const DopeEngine::GraphicsCommandBuffer* targetCommandBuffer)
	{
		Renderer->finalize_rendering(targetCommandBuffer);
	}

	void EditorGUIPainter::on_painter_receive_event(const DopeEngine::ApplicationEvent* event)
	{
		Renderer->on_application_event(event);
	}

}