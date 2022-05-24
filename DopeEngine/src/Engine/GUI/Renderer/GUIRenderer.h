#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Graphics/API/GraphicsAPIType.h>
#include <Engine/GUI/Flags/GUIRendererBackendFlags.h>
#include <Engine/GUI/Flags/GUIRendererConfigFlags.h>
#include <Engine/GUI/Renderer/Theme/GUIRendererThemeDesc.h>
#include <Engine/GUI/Commands/GUIRenderingCommands.h>
#include <Engine/GUI/Commands/GUIEventCommands.h>
#include <Engine/GUI/Commands/GUILayoutCommands.h>
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
		static GUIRenderer* create(const GUIRendererBackendFlags backendFlags, const GUIRendererConfigFlags configFlags,const GraphicsDevice* device);
		~GUIRenderer();

		FORCEINLINE const GUIRenderingCommands* get_rendering_commands() const;
		FORCEINLINE const GUIEventCommands* get_event_commands() const;
		FORCEINLINE const GUILayoutCommands* get_layout_commands() const;
		void on_application_event(const ApplicationEvent* event);
		void begin_rendering(const float deltaTimeInMilliseconds);
		void finalize_rendering(const GraphicsCommandBuffer* cmdBuffer);
		void set_theme(const GUIRendererThemeDesc& desc);
		virtual FORCEINLINE GraphicsAPIType get_api_type() const = 0;
	protected:
		GUIRenderer(const GUIRendererBackendFlags backendFlags,const GUIRendererConfigFlags configFlags);
		
		virtual void begin_rendering_impl() = 0;
		virtual void finalize_rendering_impl(const GraphicsCommandBuffer* cmdbuffer) = 0;
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
		GUIRenderingCommands* RenderingCommands;
		GUIEventCommands* EventCommands;
		GUILayoutCommands* LayoutCommands;
		GUIRendererThemeDesc ThemeDesc;
		unsigned int WindowWidth;
		unsigned int WindowHeight;
		unsigned int MousePositionX;
		unsigned int MousePositionY;
	};


}