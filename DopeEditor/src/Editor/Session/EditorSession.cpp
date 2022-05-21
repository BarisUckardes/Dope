#include "EditorSession.h"
#include <Editor/Painter/EditorGUIPainter.h>
#include <Engine/Application/Session/GameSession.h>
#include <Engine/Application/Window/Window.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>

namespace DopeEditor
{
	EditorSession::EditorSession(DopeEngine::GameSession* session)
	{
		/*
		* Initialize
		*/
		EngineSession = session;

		/*
		* Create editor gui painter
		*/
		DopeEngine::GraphicsDevice* device = EngineSession->get_window()->get_child_graphics_device();
		Painter = new EditorGUIPainter(device->get_api_type(), device);
	}

	EditorSession::~EditorSession()
	{

	}

	DopeEngine::GameSession* EditorSession::get_engine_session() const
	{
		return EngineSession;
	}

	EditorGUIPainter* EditorSession::get_editor_painter() const
	{
		return Painter;
	}

}