#include "GUIRenderer.h"
#include <Engine/Core/Assert.h>
#include <Engine/GUI/Renderer/API/OpenGL/OpenGLGUIRenderer.h>
#include <Engine/GUI/Renderer/API/Directx11/DX11GUIRenderer.h>
#include <Engine/GUI/Renderer/API/Directx12/DX12GUIRenderer.h>
#include <Engine/Application/Events/Events.h>
#include <Engine/Input/Keys.h>
#include <IMGUI/imgui.h>
namespace DopeEngine
{
	GUIRenderer* GUIRenderer::create(const GraphicsAPIType type, const GUIRendererBackendFlags backendFlags, const GUIRendererConfigFlags configFlags, const GraphicsDevice* device)
	{
		switch (type)
		{
			case DopeEngine::GraphicsAPIType::Undefined:
				ASSERT(false, "GUIRenderer", "Invalid GraphicsApiType::Undefined, couldnt create the requested GUIRenderer");
				break;
			case DopeEngine::GraphicsAPIType::OpenGL:
				return new OpenGLGUIRenderer(backendFlags,configFlags);
				break;
			case DopeEngine::GraphicsAPIType::Directx11:
				return new DX11GUIRenderer(backendFlags, configFlags,device);
				break;
			case DopeEngine::GraphicsAPIType::Directx12:
				return new DX12GUIRenderer(backendFlags, configFlags,device);
				break;
			case DopeEngine::GraphicsAPIType::Vulkan:
				break;
			default:
				ASSERT(false, "GUIRenderer", "Invalid GraphicsApiType, couldnt create the requested GUIRenderer");
				break;
		}
	}

	GUIRenderer::GUIRenderer(const GUIRendererBackendFlags backendFlags, const GUIRendererConfigFlags configFlags)
	{
		/*
		* Create new imgui context
		*/
		Context = ImGui::CreateContext();

		/*
		* Set current
		*/
		ImGui::SetCurrentContext(Context);

		/*
		* Create io flags
		*/
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags = backendFlags;
		io.ConfigFlags = configFlags;

		/*
		* Set key mappings
		*/
		io.KeyMap[ImGuiKey_Tab] = DOPE_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = DOPE_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = DOPE_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = DOPE_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = DOPE_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = DOPE_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = DOPE_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = DOPE_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = DOPE_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = DOPE_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = DOPE_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = DOPE_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = DOPE_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = DOPE_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = DOPE_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = DOPE_KEY_A;
		io.KeyMap[ImGuiKey_C] = DOPE_KEY_C;
		io.KeyMap[ImGuiKey_V] = DOPE_KEY_V;
		io.KeyMap[ImGuiKey_X] = DOPE_KEY_X;
		io.KeyMap[ImGuiKey_Y] = DOPE_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = DOPE_KEY_Z;

		/*
		* Set default theme
		*/
		GUIRendererThemeDesc defaultThemeDesc = {};
		set_theme(defaultThemeDesc);
	}

	void GUIRenderer::on_application_event(ApplicationEvent* event)
	{
		/*
		* Get event type
		*/
		ApplicationEventType eventType = event->get_type();

		/*
		* catch event
		*/
		switch (eventType)
		{
			case DopeEngine::ApplicationEventType::Undefined:
				break;
			case DopeEngine::ApplicationEventType::KeyboardKeyDown:
				on_keyboard_key_down((const KeyboardKeyDownEvent*)event);
				break;
			case DopeEngine::ApplicationEventType::KeyboardKeyUp:
				on_keyboard_key_up((const KeyboardKeyUpEvent*)event);
				break;
			case DopeEngine::ApplicationEventType::KeyboardChar:
				on_keyboard_char((const KeyboardCharEvent*)event);
				break;
			case DopeEngine::ApplicationEventType::WindowResized:
				on_window_resized((const WindowResizedEvent*)event);
				break;
			case DopeEngine::ApplicationEventType::WindowClosed:
				break;
			case DopeEngine::ApplicationEventType::WindowPositionChanged:
				on_window_position_changed((const WindowPositionChangedEvent*)event);
				break;
			case DopeEngine::ApplicationEventType::MouseButtonDown:
				on_mouse_button_down((const MouseButtonDownEvent*)event);
				break;
			case DopeEngine::ApplicationEventType::MouseButtonUp:
				on_mouse_button_up((const MouseButtonUpEvent*)event);
				break;
			case DopeEngine::ApplicationEventType::MouseScrolled:
				on_mouse_scrolled((const MouseScrolledEvent*)event);
				break;
			case DopeEngine::ApplicationEventType::MousePositionChanged:
				on_mouse_position_changed((const MousePositionChangedEvent*)event);
				break;
			case DopeEngine::ApplicationEventType::WindowFileDrop:
				break;
			default:
				ASSERT(false, "GUIRenderer", "Received invalid application event type!");
				break;
		}
	}

	void GUIRenderer::begin_rendering(const float deltaTimeInMilliseconds)
	{
		/*
		* Get imgui io
		*/
		ImGuiIO& io = ImGui::GetIO();


		/*
		* Set display size
		*/
		io.DisplaySize = ImVec2(WindowWidth, WindowHeight);
		io.DeltaTime = deltaTimeInMilliseconds;

		/*
		* Call rendering squence
		*/
		begin_rendering_impl();
		ImGui::NewFrame();
	}

	void GUIRenderer::render(GraphicsCommandBuffer* cmdBuffer)
	{
		ImGui::Render();
		render_impl(cmdBuffer);
	}

	void GUIRenderer::set_theme(const GUIRendererThemeDesc& desc)
	{
		/*
		* TODO: Active imgui theme
		*/

		/*
		* Set renderer theme
		*/
		ThemeDesc = desc;
	}

	void GUIRenderer::on_keyboard_key_down(const KeyboardKeyDownEvent* event)
	{
		/*
		* Get io
		*/
		ImGuiIO& io = ImGui::GetIO();

		/*
		* Set keys down
		*/
		io.KeysDown[event->get_key()] = true;
		io.KeyCtrl = io.KeysDown[DOPE_KEY_LEFT_CONTROL] || io.KeysDown[DOPE_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[DOPE_KEY_LEFT_SHIFT] || io.KeysDown[DOPE_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[DOPE_KEY_LEFT_ALT] || io.KeysDown[DOPE_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[DOPE_KEY_LEFT_SUPER] || io.KeysDown[DOPE_KEY_RIGHT_SUPER];
	}

	void GUIRenderer::on_keyboard_key_up(const KeyboardKeyUpEvent* event)
	{
		/*
		* Get io
		*/
		ImGuiIO& io = ImGui::GetIO();

		/*
		* Set up keys
		*/
		io.KeysDown[event->get_key()] = false;
	}

	void GUIRenderer::on_keyboard_char(const KeyboardCharEvent* event)
	{
		/*
		* Get io
		*/
		ImGuiIO& io = ImGui::GetIO();

		/*
		* Set char
		*/
		const unsigned int keyCode = event->get_key();
		if (keyCode > 0 && keyCode < 0x10000)
			io.AddInputCharacter((unsigned short)keyCode);
	}

	void GUIRenderer::on_mouse_button_down(const MouseButtonDownEvent* event)
	{
		/*
		* Get io
		*/
		ImGuiIO& io = ImGui::GetIO();

		/*
		* Set mouse button down
		*/
		io.MouseDown[event->get_button()] = true;

	}

	void GUIRenderer::on_mouse_button_up(const MouseButtonUpEvent* event)
	{
		/*
		* Get io
		*/
		ImGuiIO& io = ImGui::GetIO();

		/*
		* Set mouse button up
		*/
		io.MouseDown[event->get_button()] = false;
	}

	void GUIRenderer::on_mouse_position_changed(const MousePositionChangedEvent* event)
	{
		/*
		* Get io
		*/
		ImGuiIO& io = ImGui::GetIO();

		/*
		* Set mouse position
		*/
		const unsigned int positionX = event->get_x();
		const unsigned int positionY = event->get_y();
		io.MousePos = ImVec2(positionX, positionY);

		/*
		* Set renderer mouse position
		*/
		MousePositionX = positionX;
		MousePositionY = positionY;
	}

	void GUIRenderer::on_mouse_scrolled(const MouseScrolledEvent* event)
	{
		/*
		* Get io
		*/
		ImGuiIO& io = ImGui::GetIO();

		/*
		* Set scroll
		*/
		//io.MouseWheel += event->get_amount();
	}

	void GUIRenderer::on_window_resized(const WindowResizedEvent* event)
	{
		/*
		* Get io
		*/
		ImGuiIO& io = ImGui::GetIO();

		/*
		* Set new window size
		*/
		const unsigned int width = event->get_width();
		const unsigned int height = event->get_height();
		io.DisplaySize = ImVec2(width,height);
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		/*
		* Set renderer window size
		*/
		WindowWidth = width;
		WindowHeight = height;
	}

	void GUIRenderer::on_window_position_changed(const WindowPositionChangedEvent* event)
	{

	}


}