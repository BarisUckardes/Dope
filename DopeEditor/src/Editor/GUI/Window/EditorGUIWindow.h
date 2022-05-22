#pragma once
#include <Editor/Core/Symbols.h>

namespace DopeEditor
{
	/// <summary>
	/// Represents a window created and authored by the editor
	/// <para>It's a base class for all the custom EditorWindows to implement </para>
	/// </summary>
	class DOPE_EDITOR_API EditorGUIWindow
	{
		friend class EditorWindowGUIModule;
	public:

		/// <summary>
		/// Returns whether this window is currently is visible or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_visible() const;

		/// <summary>
		/// Returns whether this window is currently is visible or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool is_collapsed() const;

		/// <summary>
		/// Called upon first creation
		/// </summary>
		virtual void on_initialize() = 0;

		/// <summary>
		/// Called everyframe Editor updates
		/// </summary>
		virtual void on_render() = 0;

		/// <summary>
		/// Called upon destroy
		/// </summary>
		virtual void on_finalize() = 0;

		/// <summary>
		/// Called when window switched to visible mode
		/// </summary>
		virtual void on_visible() = 0;

		/// <summary>
		/// Called when window switched to invisible mode
		/// </summary>
		virtual void on_invisible() = 0;

	private:
		/// <summary>
		/// Internal method for setting the Visible field
		/// </summary>
		/// <param name="state"></param>
		void _set_visiblity(const bool state);

		/// <summary>
		/// Internal method for setting the Collapsed field
		/// </summary>
		/// <param name="state"></param>
		void _set_collapsed(const bool state);
	private:
		bool Visible;
		bool Collapsed;
	};


}