#pragma once
#include <Editor/GUI/EditorGUIModule.h>

namespace DopeEditor
{
	class DOPE_EDITOR_API EditorMainMenuGUIModule : public EditorGUIModule
	{
	public:
		EditorMainMenuGUIModule() = default;
		~EditorMainMenuGUIModule() = default;

		// Inherited via EditorGUIModule
		virtual void initialize() override;
		virtual void update() override;
		virtual void finalize() override;
	};


}