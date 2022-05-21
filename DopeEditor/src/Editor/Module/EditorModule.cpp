#include "EditorModule.h"
#include <Editor/Session/EditorSession.h>
#include <Engine/Core/ConsoleLog.h>
#include <Editor/Painter/EditorGUIPainter.h>
#include <Engine/Application/Session/GameSession.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/GUI/Commands/GUIRenderingCommands.h>
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
	}

	void EditorModule::update()
	{
		/*
		* Start gui rendering
		*/
		Session->get_editor_painter()->StartRendering();

		DopeEngine::GUIRenderingCommands::test_window();

		/*
		* Finalize gui rendering
		*/
		Session->get_editor_painter()->FinalizeRendering((const DopeEngine::GraphicsCommandBuffer*)GUICommandBuffer);

	}

	void EditorModule::finalize()
	{

	}

	void EditorModule::on_receive_application_event(DopeEngine::ApplicationEvent* event)
	{

	}

}

