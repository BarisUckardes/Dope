#pragma once
#include <Editor/Core/Symbols.h>
#include <Engine/Structures/String.h>
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
		EditorGUIWindow();
		~EditorGUIWindow() = default;

		FORCEINLINE bool is_collapsed() const;

		virtual DopeEngine::String get_window_name() const = 0;

		virtual void on_initialize() = 0;
		virtual void on_render() = 0;
		virtual void on_finalize() = 0;
		virtual void on_visible() = 0;
		virtual void on_invisible() = 0;
	private:
		/// <summary>
		/// Internal method for setting the Collapsed field
		/// </summary>
		/// <param name="state"></param>
		void _set_collapsed(const bool state);
	private:
		bool Active;
		bool Collapsed;
	};


}