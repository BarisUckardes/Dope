#include "EditorWindowGUIModule.h"
#include <Editor/GUI/Window/EditorGUIWindow.h>
#include <Editor/Session/EditorSession.h>
#include <Editor/Painter/EditorGUIPainter.h>
#include <Editor/GUI/Window/EditorGUIWindows.h>
#include <Engine/Core/ConsoleLog.h>
#include <Engine/Core/Assert.h>
#include <Engine/GUI/Commands/GUILayoutCommands.h>
namespace DopeEditor
{
	bool EditorWindowGUIModule::delete_window(EditorGUIWindow* window)
	{
		const int index = ActiveWindows.find_index(window);

		ASSERT(index != -1, "EditorWindowGUIModule", "Unexpected behaviour occured!, there is a GUIWindow but its not registered to EditorWindowGUIModule class!");

		window->on_invisible();
		window->on_finalize();
		window->_set_owner_session(nullptr);

		delete window;

		ActiveWindows.remove_index(index);

		return true;
	}
	void EditorWindowGUIModule::initialize()
	{
		/*
		* Register dummy
		*/
		create_window<WorldObserverWindow>();
	}

	void EditorWindowGUIModule::update()
	{
		DopeEngine::GUIRenderingCommands* renderingCommands = get_owner_session()->get_editor_painter()->get_rendering_commands();
		DopeEngine::GUILayoutCommands* layoutCommands = get_owner_session()->get_editor_painter()->get_layout_commands();

		for (unsigned int i = 0; i < ActiveWindows.get_cursor(); i++)
		{
			EditorGUIWindow* window = ActiveWindows[i];

			if (window->is_first_draw())
			{
				layoutCommands->set_next_window_position(window->get_position());
				layoutCommands->set_next_window_size(window->get_size());
				
				window->_mark_first_draw();
			}

			const bool formerCollapseState = window->is_collapsed();
			bool windowStillActive = true;
			const bool currentCollapseState = renderingCommands->start_window(*window->get_window_name(), &windowStillActive);

			window->on_render();

			const DopeEngine::Vector2f currentWindowPosition = layoutCommands->get_window_positon();
			const DopeEngine::Vector2f currentWindowSize = layoutCommands->get_window_size();

			renderingCommands->finalize_window();

			window->_set_position(currentWindowPosition);
			window->_set_size(currentWindowSize);
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
			window->_set_owner_session(nullptr);

			delete window;
		}
		ActiveWindows.clear();
	}

}