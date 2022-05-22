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
		/// <summary>
		/// Called upon initialization of the EditorModule
		/// </summary>
		virtual void initialize() = 0;

		/// <summary>
		/// Called upon every Editor update
		/// </summary>
		virtual void update() = 0;

		/// <summary>
		/// Called upon finalization of the EditorModule
		/// </summary>
		virtual void finalize() = 0;
	protected:
		EditorGUIModule() : OwnerSession(nullptr) {}
		~EditorGUIModule() = default;

		/// <summary>
		/// Returns the owner session which this GUI module is authored by
		/// </summary>
		/// <returns></returns>
		FORCEINLINE EditorSession* get_owner_session() const;
	private:

		/// <summary>
		/// Internal method for setting the owner session
		/// </summary>
		/// <param name="ownerSession"></param>
		void _set_owner_session(EditorSession* ownerSession);
	private:
		EditorSession* OwnerSession;
	};


}