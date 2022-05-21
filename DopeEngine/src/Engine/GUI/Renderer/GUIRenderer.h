#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/Device/GraphicsAPIType.h>
#include <Engine/GUI/Renderer/Flags/GUIRendererBackendFlags.h>
#include <Engine/GUI/Renderer/Flags/GUIRendererConfigFlags.h>
#include <Engine/GUI/Renderer/Theme/GUIRendererThemeDesc.h>
struct ImGuiContext;
namespace DopeEngine
{
	class GraphicsDevice;
	class GraphicsCommandBuffer;
	class ApplicationEvent;
	class KeyboardKeyDownEvent;
	class KeyboardKeyUpEvent;
	class KeyboardCharEvent;
	class MouseButtonDownEvent;
	class MouseButtonUpEvent;
	class MousePositionChangedEvent;
	class MouseScrolledEvent;
	class WindowResizedEvent;
	class WindowPositionChangedEvent;

	/// <summary>
	/// A graphics renderer specialized in GUI rendering
	/// <para>It uses IMGUI as backend renderer</api>
	/// </summary>
	class DOPE_ENGINE_API GUIRenderer
	{
	public:
		/// <summary>
		/// Creates api agnostic GUIRenderer
		/// </summary>
		/// <param name="type"></param>
		/// <param name="backendFlags"></param>
		/// <param name="configFlags"></param>
		/// <param name="device"></param>
		/// <returns></returns>
		static GUIRenderer* create(const GraphicsAPIType type, const GUIRendererBackendFlags backendFlags, const GUIRendererConfigFlags configFlags,const GraphicsDevice* device);
		~GUIRenderer() = default;

		/// <summary>
		/// Called when received an application event
		/// </summary>
		/// <param name="event"></param>
		void on_application_event(const ApplicationEvent* event);

		/// <summary>
		/// Begins the GUI rendering session
		/// </summary>
		/// <param name="deltaTimeInMilliseconds"></param>
		void begin_rendering(const float deltaTimeInMilliseconds);

		/// <summary>
		/// Renders the contents
		/// </summary>
		/// <param name="cmdBuffer"></param>
		void render(const GraphicsCommandBuffer* cmdBuffer);

		/// <summary>
		/// Sets anew gui theme
		/// </summary>
		/// <param name="desc"></param>
		void set_theme(const GUIRendererThemeDesc& desc);

		/// <summary>
		/// Returns the graphics api type
		/// </summary>
		/// <returns></returns>
		virtual FORCEINLINE GraphicsAPIType get_api_type() const = 0;

	protected:
		GUIRenderer(const GUIRendererBackendFlags backendFlags,const GUIRendererConfigFlags configFlags);
		

		virtual void begin_rendering_impl() = 0;
		virtual void render_impl(const GraphicsCommandBuffer* cmdbuffer) = 0;
	private:
		void on_keyboard_key_down(const KeyboardKeyDownEvent* event);
		void on_keyboard_key_up(const KeyboardKeyUpEvent* event);
		void on_keyboard_char(const KeyboardCharEvent* event);
		void on_mouse_button_down(const MouseButtonDownEvent* event);
		void on_mouse_button_up(const MouseButtonUpEvent* event);
		void on_mouse_position_changed(const MousePositionChangedEvent* event);
		void on_mouse_scrolled(const MouseScrolledEvent* event);
		void on_window_resized(const WindowResizedEvent* event);
		void on_window_position_changed(const WindowPositionChangedEvent* event);
	private:
		ImGuiContext* Context;
		GUIRendererThemeDesc ThemeDesc;
		unsigned int WindowWidth;
		unsigned int WindowHeight;
		unsigned int MousePositionX;
		unsigned int MousePositionY;
	};


}