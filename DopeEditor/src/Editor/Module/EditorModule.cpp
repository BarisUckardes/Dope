#include "EditorModule.h"
#include <Editor/Session/EditorSession.h>
#include <Engine/Core/ConsoleLog.h>
#include <Editor/Painter/EditorGUIPainter.h>
#include <Engine/Application/Session/GameSession.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/GUI/Commands/GUIRenderingCommands.h>
#include <Engine/Graphics/Command/GraphicsCommandBuffer.h>
#include <Engine/GUI/Commands/GUIRenderingCommands.h>
#include <Editor/GUI/Window/EditorWindowGUIModule.h>
#include <Editor/GUI/EditorGUIModule.h>

namespace DopeEditor
{
	DopeEngine::String EditorModule::get_module_class_name() const
	{
		return "EditorModule";
	}

	void EditorModule::initialize()
	{
		/*
		* Create editor session
		*/
		Session = new EditorSession(get_owner_session());

		/*
		* Create command buffer
		*/
		GUICommandBuffer = get_owner_session()->get_window()->get_child_graphics_device()->create_command_buffer();

		/*
		* Create GUI modules
		*/
		GUIModules.add(new EditorWindowGUIModule());

		/*
		* Initialize GUI modules
		*/
		for (unsigned int i = 0; i < GUIModules.get_cursor(); i++)
		{
			/*
			* Get gui module
			*/
			EditorGUIModule* module = GUIModules[i];

			/*
			* Initialize
			*/
			module->_set_owner_session(Session);
			module->initialize();
		}
	}
	void EditorModule::update()
	{
		/*
		* Start gui rendering
		*/
		Session->get_editor_painter()->StartPainting();

		/*
		* Update GUI modules
		*/
		for (unsigned int i = 0; i < GUIModules.get_cursor(); i++)
		{
			/*
			* Update module
			*/
			GUIModules[i]->update();
		}

		/*
		* Finalize gui rendering
		*/
		Session->get_editor_painter()->FinalizePainting((const DopeEngine::GraphicsCommandBuffer*)GUICommandBuffer);
	}

	void EditorModule::finalize()
	{
		/*
		* Finalize GUI modules
		*/
		for (unsigned int i = 0; i < GUIModules.get_cursor(); i++)
		{
			/*
			* Get module
			*/
			EditorGUIModule* module = GUIModules[i];

			/*
			* Finalize
			*/
			module->finalize();

			/*
			* Free heap memory
			*/
			delete module;
		}
	}

	void EditorModule::on_receive_application_event(DopeEngine::ApplicationEvent* event)
	{
		Session->get_editor_painter()->on_painter_receive_event(event);
	}

}

