#include "EditorWindowGUIModule.h"
#include <Editor/GUI/Window/EditorGUIWindow.h>
#include <Editor/Session/EditorSession.h>
#include <Editor/Painter/EditorGUIPainter.h>
namespace DopeEditor
{
	void EditorWindowGUIModule::initialize()
	{

	}

	void EditorWindowGUIModule::update()
	{
		/*
		* Get rendering commands
		*/
		const DopeEngine::GUIRenderingCommands* renderingCommands = get_owner_session()->get_editor_painter()->get_rendering_commands();

		renderingCommands->create_demo_window();
	}

	void EditorWindowGUIModule::finalize()
	{

	}

}