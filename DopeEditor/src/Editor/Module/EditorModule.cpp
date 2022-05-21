#include "EditorModule.h"
#include <Editor/Session/EditorSession.h>
#include <Engine/Core/ConsoleLog.h>
#include <Editor/Painter/EditorGUIPainter.h>
#include <Engine/Application/Session/GameSession.h>
#include <Engine/Graphics/Device/GraphicsDevice.h>
#include <Engine/GUI/Commands/GUIRenderingCommands.h>
#include <Engine/Graphics/Command/GraphicsCommandBuffer.h>
DopeEngine::ViewportDesc viewportDesc;
DopeEngine::ScissorsDesc scissorsDesc;
DopeEngine::RenderPass* renderPass;
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
		/*viewportDesc = {};
		viewportDesc.OffsetX = 0;
		viewportDesc.OffsetY = 0;
		viewportDesc.Width = get_owner_session()->get_window()->get_child_graphics_device()->get_swapchain_framebuffer()->get_width();
		viewportDesc.Height = get_owner_session()->get_window()->get_child_graphics_device()->get_swapchain_framebuffer()->get_height();
		viewportDesc.MinDepth = 0.0f;
		viewportDesc.MaxDepth = 1.0f;

		scissorsDesc = {};
		scissorsDesc.OffsetX = 0;
		scissorsDesc.OffsetY = 0;
		scissorsDesc.Width = get_owner_session()->get_window()->get_child_graphics_device()->get_swapchain_framebuffer()->get_width();
		scissorsDesc.Height = get_owner_session()->get_window()->get_child_graphics_device()->get_swapchain_framebuffer()->get_height();

		DopeEngine::RenderPassDesc renderPassDesc;
		renderPassDesc.BlendingState = DopeEngine::BlendState::SingleOverride;
		renderPassDesc.CullFace = DopeEngine::FaceCullMode::Back;
		renderPassDesc.DepthClip = false;
		renderPassDesc.DepthComparision = DopeEngine::DepthComparisionKind::Always;
		renderPassDesc.DepthTest = false;
		renderPassDesc.DepthWrite = false;
		renderPassDesc.FillMode = DopeEngine::PolygonFillMode::Fill;
		renderPassDesc.FrontFace = DopeEngine::FrontFaceMode::CounterClockwise;
		renderPassDesc.LayoutDescription = {};
		renderPassDesc.Primitives = DopeEngine::PrimitiveTopology::Triangles;
		renderPassDesc.ScissorTest = false;
		renderPassDesc.ShaderSet = {};
		renderPassDesc.ResourceSlots = { };
		renderPassDesc.TargetFramebuffer = get_owner_session()->get_window()->get_child_graphics_device()->get_swapchain_framebuffer();
		renderPass = get_owner_session()->get_window()->get_child_graphics_device()->create_render_pass(renderPassDesc);*/
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
		//Session->get_editor_painter()->on_painter_receive_event(event);
	}

}

