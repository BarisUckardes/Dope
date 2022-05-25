#pragma once
#include <Editor/Core/Symbols.h>
#include <Engine/Structures/String.h>
#include <Engine/Math/Vector2f.h>
namespace DopeEditor
{
	class EditorSession;
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
		FORCEINLINE DopeEngine::Vector2f get_position() const;
		FORCEINLINE DopeEngine::Vector2f get_size() const;
		FORCEINLINE bool is_first_draw() const;

		virtual DopeEngine::String get_window_name() const = 0;

		virtual void on_initialize() = 0;
		virtual void on_render() = 0;
		virtual void on_finalize() = 0;
		virtual void on_visible() = 0;
		virtual void on_invisible() = 0;
	protected:
		FORCEINLINE EditorSession* get_owner_session() const;
	private:
		FORCEINLINE void _set_collapsed(const bool state);
		FORCEINLINE void _set_position(const DopeEngine::Vector2f& position);
		FORCEINLINE void _set_size(const DopeEngine::Vector2f& size);
		void _mark_first_draw();

		void _set_owner_session(EditorSession* ownerSession);
	private:
		EditorSession* OwnerSession;
		DopeEngine::Vector2f Position;
		DopeEngine::Vector2f Size;
		bool FirstDraw;
		bool Active;
		bool Collapsed;
	};
}