#pragma once
#include <Editor/GUI/EditorGUIModule.h>
#include <Engine/Structures/Array.h>
namespace DopeEditor
{
	class EditorGUIWindow;
	class DOPE_EDITOR_API EditorWindowGUIModule : public EditorGUIModule
	{
	public:
		EditorWindowGUIModule() = default;
		~EditorWindowGUIModule() = default;


		// Inherited via EditorGUIModule
		virtual void initialize() override;
		virtual void update() override;
		virtual void finalize() override;
	private:
		DopeEngine::Array<EditorGUIWindow*> ActiveWindows;
	};


}