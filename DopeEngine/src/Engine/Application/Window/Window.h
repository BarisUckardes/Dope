#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Application/Window/WindowCreateDescription.h>
namespace DopeEngine
{
	class GraphicsDevice;
	/// <summary>
	/// Window OS abstraction class
	/// </summary>
	class DOPE_ENGINE_API Window
	{
	public:
		static Window* create(const WindowCreateDescription& description);

		/// <summary>
		/// Returns the assinged graphics device to this window(if any)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE GraphicsDevice* get_graphics_device() const;

		/// <summary>
		/// Returns the width of this window in pixels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int get_width() const;

		/// <summary>
		/// Returns the height of this window in pixels
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
		/// Returns the title of this window
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String get_title() const;

		/// <summary>
		/// Returns whether this window is visible or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_visible() const;

		/// <summary>
		/// Swaps the window backbuffers
		/// </summary>
		FORCEINLINE void swap_buffers();

		/// <summary>
		/// Collects the pending window messages
		/// </summary>
		FORCEINLINE void poll_messages();
	
		/// <summary>
		/// Sets the title of this window
		/// </summary>
		/// <param name="title"></param>
		FORCEINLINE void set_title(const String& title);

		/// <summary>
		/// Changesthe visibility state of this window
		/// </summary>
		void set_window_visibility(const bool state);

		/// <summary>
		/// Assinges anew graphics device
		/// </summary>
		/// <param name="device"></param>
		void assing_graphics_device(GraphicsDevice* device);
	protected:
		Window(const WindowCreateDescription& description);
		virtual ~Window() = default;

		virtual void set_visibility_impl(const bool state) = 0;
		virtual void set_title_impl(const String& title) = 0;
		virtual void swap_buffers_impl() = 0;
		virtual void poll_messages_impl() = 0;
	private:
		GraphicsDevice* GDevice;
		String Title;
		unsigned int Width;
		unsigned int Height;
		unsigned int PositionX;
		unsigned int PositionY;
		bool Visibility;
	};
}