#pragma once
#include <Engine/Core/Symbols.h>
#include <Engine/Structures/String.h>
namespace DopeEngine
{
	/// <summary>
	/// Window OS abstraction class
	/// </summary>
	class DOPE_ENGINE_API Window
	{
	public:
		static Window* create(const String& title,const unsigned int width,const unsigned int height);

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
	protected:
		Window(const String& title, const unsigned int width, const unsigned int height);
		virtual ~Window() = default;

		virtual void set_visibility_impl(const bool state) = 0;
		virtual void set_title_impl(const String& title) = 0;
		virtual void swap_buffers_impl() = 0;
		virtual void poll_messages_impl() = 0;
	private:
		String Title;
		unsigned int Width;
		unsigned int Height;
		bool Visibility;
	};
}