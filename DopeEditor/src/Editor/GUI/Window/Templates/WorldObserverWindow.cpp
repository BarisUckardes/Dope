#include "WorldObserverWindow.h"
#include <Editor/Session/EditorSession.h>
#include <Editor/Painter/EditorGUIPainter.h>
#include <Engine/Application/Session/GameSession.h>
#include <Engine/World/World.h>
#include <Engine/GUI/Commands/GUIRenderingCommands.h>
#include <Engine/World/Entity.h>
#include <Engine/Core/ConsoleLog.h>
namespace DopeEditor
{
	DopeEngine::String WorldObserverWindow::get_window_name() const
	{
		return "WorldObserver";
	}

	void WorldObserverWindow::on_initialize()
	{

	}

	void WorldObserverWindow::on_render()
	{
		EditorSession* editorSession = get_owner_session();

		DopeEngine::GUIRenderingCommands* renderingCommands = editorSession->get_editor_painter()->get_rendering_commands();

		DopeEngine::GameSession* engineSession = editorSession->get_engine_session();

		DopeEngine::World* currentWorld = engineSession->get_current_world();
	
		if (currentWorld == nullptr)
		{
			renderingCommands->create_text_label("There is no world that marked as <current>!");
			return;
		}

		if (renderingCommands->create_collapsing_segment(*currentWorld->get_name()))
		{
			const DopeEngine::Array<DopeEngine::Entity*>& entities = currentWorld->get_entities_fast();
			for (unsigned int i = 0; i < entities.get_cursor(); i++)
			{
				const DopeEngine::Entity* entity = entities[i];

				renderingCommands->create_text_label(*entity->get_name());
			}
		}
	}

	void WorldObserverWindow::on_finalize()
	{

	}

	void WorldObserverWindow::on_visible()
	{

	}

	void WorldObserverWindow::on_invisible()
	{

	}

}