#include "EditorModule.h"
#include <Editor/Session/EditorSession.h>
#include <Engine/Core/ConsoleLog.h>
#include <Editor/Painter/EditorGUIPainter.h>
#include <Engine/Application/Session/GameSession.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/GUI/Commands/GUIRenderingCommands.h>
#include <Engine/Graphics/Command/GraphicsCommandBuffer.h>
#include <Engine/GUI/Commands/GUIRenderingCommands.h>
#include <Engine/GUI/Commands/GUILayoutCommands.h>
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
	bool dockspaceOpen = true;
	void EditorModule::update()
	{
		/*
		* Get painter
		*/
		EditorGUIPainter* painter = Session->get_editor_painter();

		/*
		* Start gui rendering
		*/
		painter->StartPainting();

		/*
		* Start docking
		*/
		const DopeEngine::GUIRenderingCommands* renderingCommands = painter->get_rendering_commands();
		const DopeEngine::GUILayoutCommands* layoutCommands = painter->get_layout_commands();
		const DopeEngine::GUIEventCommands* eventCommands = painter->get_event_commands();
		DopeEngine::GUIWindowFlags dockWindowFlags =
			DopeEngine::GUIWindowFlags::NoTitleBar |
			DopeEngine::GUIWindowFlags::NoCollapse |
			DopeEngine::GUIWindowFlags::NoMove |
			DopeEngine::GUIWindowFlags::NoBringToFrontOnFocus |
			DopeEngine::GUIWindowFlags::NoNavFocus |
			DopeEngine::GUIWindowFlags::MenuBar;
		
		layoutCommands->set_next_window_position(layoutCommands->get_main_viewport_position());
		layoutCommands->set_next_window_size(layoutCommands->get_main_viewport_size());
		layoutCommands->set_next_window_viewport(layoutCommands->get_main_viewport_id());

		layoutCommands->push_style(DopeEngine::GUIStyleVariableTypes::WindowPadding, { 0,0 });
		//layoutCommands->push_style(DopeEngine::GUIStyleFlags::WindowPadding, 0);

		renderingCommands->create_window("Dockspace", &dockspaceOpen, dockWindowFlags);

		layoutCommands->pop_style();

		GUIID dockspaceID = layoutCommands->get_id("EditorDockspace");
		layoutCommands->create_dockspace(dockspaceID, { 0,0 }, DopeEngine::GUIDockspaceFlags::None | DopeEngine::GUIDockspaceFlags::PassthruCentralNode);

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
		* Finalize dockspace
		*/
		renderingCommands->finalize_window();

		/*
		* Finalize gui rendering
		*/
		painter->FinalizePainting((const DopeEngine::GraphicsCommandBuffer*)GUICommandBuffer);
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

