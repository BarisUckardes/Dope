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
		/*
		* Get rendering commands
		*/
		const DopeEngine::GUIRenderingCommands* renderingCommands = get_owner_session()->get_editor_painter()->get_rendering_commands();

		/*
		* Iterate each GUIWindow and update
		*/
		for (unsigned int i = 0; i < ActiveWindows.get_cursor(); i++)
		{
			/*
			* Get active window
			*/
			EditorGUIWindow* window = ActiveWindows[i];

			/*
			* Render
			*/
			const bool formerCollapseState = window->is_collapsed();
			bool windowStillActive = true;
			const bool currentCollapseState = renderingCommands->create_window(*window->get_window_name(), &windowStillActive);
			renderingCommands->finalize_window();

			/*
			* Set collapse state
			*/
			window->_set_collapsed(currentCollapseState);

			/*
			* Validate close request
			*/
			if (!windowStillActive)
			{
				/*
				* Finalize window
				*/
				window->on_invisible();
				window->on_finalize();

				/*
				* Free window heap
				*/
				delete window;

				/*
				* Remove from active windows
				*/
				ActiveWindows.remove_index(i);
				i--;
				continue;
			}

			/*
			* Validate visibility change
			*/
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
		/*
		* Finalize all windows
		*/
		for (unsigned int i = 0; i < ActiveWindows.get_cursor(); i++)
		{
			/*
			* Get window
			*/
			EditorGUIWindow* window = ActiveWindows[i];

			/*
			* Finalize
			*/
			window->on_invisible();
			window->on_finalize();

			/*
			* Free heap memory
			*/
			delete window;
		}
		ActiveWindows.clear();
	}

}