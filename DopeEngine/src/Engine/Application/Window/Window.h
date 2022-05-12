#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Application/Window/WindowCreateDescription.h>
#include <Engine/Event/Delegate.h>

namespace DopeEngine
{
	
	class ApplicationEvent;
	class GraphicsDevice;
	class DOPE_ENGINE_API Window
	{
	public:
		static Window* create_window(const WindowCreateDescription& desc,void* windowData = nullptr);
		static void bind_window_and_device(Window* window, GraphicsDevice* childGraphicsDevice);

		FORCEINLINE GraphicsDevice* get_child_graphics_device() const;
		FORCEINLINE String get_title() const;
		FORCEINLINE unsigned int get_width() const;
		FORCEINLINE unsigned int get_height() const;
		FORCEINLINE unsigned int get_position_x() const;
		FORCEINLINE unsigned int get_position_y() const;
		FORCEINLINE bool is_visible() const;
		FORCEINLINE bool has_close_request() const;

		void set_title(const String& title);
		void set_visibility(const bool state);
		void poll_messages();
		void register_event_feed_listener(const Delegate<void, ApplicationEvent*>& functionDelegate);
		void remove_event_feed_listener(const Delegate<void, ApplicationEvent*>& functionDelegate);

	protected:
		Window(const WindowCreateDescription& desc);
		virtual ~Window() = default;

		FORCEINLINE void set_child_graphics_device(GraphicsDevice* device);
		FORCEINLINE void set_width(const unsigned int width);
		FORCEINLINE void set_height(const unsigned int height);
		FORCEINLINE void set_position_x(const unsigned int x);
		FORCEINLINE void set_position_y(const unsigned int y);
		FORCEINLINE void set_close_request();
		FORCEINLINE void broadcast_window_event(ApplicationEvent* event);
		virtual void set_title_impl(const String& title) = 0;
		virtual void set_visibility_impl(const bool state) = 0;
		virtual void poll_messages_impl() = 0;
	private:
		Array<Delegate<void, ApplicationEvent*>> EventFeedListeners;
		GraphicsDevice* ChildGraphicsDevice;
		String Title;
		unsigned int Width;
		unsigned int Height;
		unsigned int PositionX;
		unsigned int PositionY;
		bool Visibility;
		bool CloseRequest;
	};
}