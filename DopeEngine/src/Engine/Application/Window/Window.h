#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Application/Window/WindowCreateDescription.h>
#include <Engine/Event/Delegate.h>

namespace DopeEngine
{
	
	class ApplicationEvent;
	class GraphicsDevice;

	/// <summary>
	/// Base window class for all Platforms to implement
	/// </summary>
	class DOPE_ENGINE_API Window
	{
	public:
		/// <summary>
		/// Creates platform agnostic window
		/// </summary>
		/// <param name="desc"></param>
		/// <param name="windowData"></param>
		/// <returns></returns>
		static Window* create_window(const WindowCreateDescription& desc,void* windowData = nullptr);

		/// <summary>
		/// Internal method for binding a window and a graphics device together
		/// </summary>
		/// <param name="window"></param>
		/// <param name="childGraphicsDevice"></param>
		static void bind_window_and_device(Window* window, GraphicsDevice* childGraphicsDevice);

		/// <summary>
		/// Returns the child graphics device which is authored by this window
		/// </summary>
		/// <returns></returns>
		FORCEINLINE GraphicsDevice* get_child_graphics_device() const;

		/// <summary>
		/// Returns the title of the window
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String get_title() const;

		/// <summary>
		/// Returns the window width in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_width() const;

		/// <summary>
		/// Returns the window height in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_height() const;

		/// <summary>
		/// Returns the position-x of the window in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_position_x() const;

		/// <summary>
		/// Returns the position-y of the window in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_position_y() const;

		/// <summary>
		/// Returns whether the window is currently is visible or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_visible() const;

		/// <summary>
		/// Returns whether the window has close request or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool has_close_request() const;

		/// <summary>
		/// Sets the title of this window
		/// </summary>
		/// <param name="title"></param>
		void set_title(const String& title);

		/// <summary>
		/// Sets the visibility of this window
		/// </summary>
		/// <param name="state"></param>
		void set_visibility(const bool state);

		/// <summary>
		/// Processes all the window messages
		/// </summary>
		void poll_messages();

		/// <summary>
		/// Presents the child swapchain image
		/// </summary>
		void present();

		/// <summary>
		/// Registers an event listener to the window message feed
		/// </summary>
		/// <param name="functionDelegate"></param>
		void register_event_feed_listener(const Delegate<void, ApplicationEvent*>& functionDelegate);

		/// <summary>
		/// Removes the existing listener fro mthe window message feed
		/// </summary>
		/// <param name="functionDelegate"></param>
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