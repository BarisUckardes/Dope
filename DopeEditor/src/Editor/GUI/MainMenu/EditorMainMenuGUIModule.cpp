#include "EditorMainMenuGUIModule.h"
#include <Editor/Painter/EditorGUIPainter.h>
#include <Editor/Session/EditorSession.h>
#include <Engine/GUI/Commands/GUIRenderingCommands.h>
#include <Engine/Core/ConsoleLog.h>
namespace DopeEditor
{
	void EditorMainMenuGUIModule::initialize()
	{

	}

	void EditorMainMenuGUIModule::update()
	{
		DopeEngine::GUIRenderingCommands* renderingCommands = get_owner_session()->get_editor_painter()->get_rendering_commands();

		renderingCommands->start_main_menu_bar();
		
		renderingCommands->finalize_main_menu_bar();
	}

	void EditorMainMenuGUIModule::finalize()
	{

	}

}

