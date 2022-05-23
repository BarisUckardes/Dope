#include "EditorWindowGUIModule.h"
#include <Editor/GUI/Window/EditorGUIWindow.h>
#include <Editor/Session/EditorSession.h>
#include <Editor/Painter/EditorGUIPainter.h>
#include <Editor/GUI/Window/EditorGUIWindows.h>
#include <Engine/Core/ConsoleLog.h>
namespace DopeEditor
{
	void EditorWindowGUIModule::initialize()
	{
		/*
		* Register dummy
		*/
		ActiveWindows.add(new WorldObserverWindow());
	}

	void EditorWindowGUIModule::update()
	{
		const DopeEngine::GUIRenderingCommands* renderingCommands = get_owner_session()->get_editor_painter()->get_rendering_commands();

		for (unsigned int i = 0; i < ActiveWindows.get_cursor(); i++)
		{
			EditorGUIWindow* window = ActiveWindows[i];

			const bool formerCollapseState = window->is_collapsed();

			bool windowStillActive = true;
			const bool currentCollapseState = renderingCommands->create_window(*window->get_window_name(), &windowStillActive);

			renderingCommands->finalize_window();

			window->_set_collapsed(currentCollapseState);

			if (!windowStillActive)
			{
				window->on_invisible();
				window->on_finalize();

				delete window;

				ActiveWindows.remove_index(i);
				i--;
				continue;
			}

			if (!formerCollapseState && currentCollapseState) // just now unfold
			{
				window->on_visible();
			}

			else if (formerCollapseState && !currentCollapseState) // just now collapsed
			{
				window->on_invisible();
			}

		}
	}

	void EditorWindowGUIModule::finalize()
	{
		for (unsigned int i = 0; i < ActiveWindows.get_cursor(); i++)
		{
			EditorGUIWindow* window = ActiveWindows[i];

			window->on_invisible();
			window->on_finalize();

			delete window;
		}
		ActiveWindows.clear();
	}

}