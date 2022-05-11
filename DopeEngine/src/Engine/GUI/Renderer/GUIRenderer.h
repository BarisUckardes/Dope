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
	class CommandBuffer;
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
	class DOPE_ENGINE_API GUIRenderer
	{
	public:
		static GUIRenderer* create(const GraphicsAPIType type, const GUIRendererBackendFlags backendFlags, const GUIRendererConfigFlags configFlags,const GraphicsDevice* device);

		virtual FORCEINLINE GraphicsAPIType get_api_type() const = 0;

		void on_application_event(ApplicationEvent* event);
		void begin_rendering(const float deltaTimeInMilliseconds);
		void render(CommandBuffer* cmdBuffer);
		void set_theme(const GUIRendererThemeDesc& desc);
	protected:
		GUIRenderer(const GUIRendererBackendFlags backendFlags,const GUIRendererConfigFlags configFlags);
		~GUIRenderer() = default;

		virtual void begin_rendering_impl() = 0;
		virtual void render_impl(CommandBuffer* cmdbuffer) = 0;
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