#pragma once
#include <Editor/Core/Symbols.h>

namespace DopeEngine
{
	class Window;
	class GameSession;
}
namespace DopeEditor
{
	class EditorGUIPainter;

	/// <summary>
	/// Represents the whole editor session
	/// </summary>
	class DOPE_EDITOR_API EditorSession
	{
		friend class EditorModule;
	public:

	private:
		EditorSession(DopeEngine::GameSession* session);
		~EditorSession();

		FORCEINLINE DopeEngine::GameSession* get_engine_session() const;
		FORCEINLINE EditorGUIPainter* get_editor_painter() const;
	private:
		DopeEngine::GameSession* EngineSession;
		EditorGUIPainter* Painter;
	};


}