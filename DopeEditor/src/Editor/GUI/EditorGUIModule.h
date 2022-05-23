#pragma once
#include <Editor/Core/Symbols.h>
#include <Engine/GUI/Commands/GUIRenderingCommands.h>
#include <Engine/GUI/Commands/GUIEventCommands.h>
namespace DopeEditor
{
	class EditorSession;

	/// <summary>
	/// These module will be executed between the GUI rendering states
	/// <para>Therefor only these classes can be rendered on the GUI</para>
	/// </summary>
	class DOPE_EDITOR_API EditorGUIModule
	{
		friend class EditorModule;
	public:
		virtual void initialize() = 0;
		virtual void update() = 0;
		virtual void finalize() = 0;
	protected:
		EditorGUIModule() : OwnerSession(nullptr) {}
		~EditorGUIModule() = default;

		FORCEINLINE EditorSession* get_owner_session() const;
	private:
		void _set_owner_session(EditorSession* ownerSession);
	private:
		EditorSession* OwnerSession;
	};


}