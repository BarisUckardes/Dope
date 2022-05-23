#pragma once
#include <Editor/Core/Symbols.h>
#include <Editor/GUI/Window/EditorGUIWindow.h>
namespace DopeEditor
{
	class DOPE_EDITOR_API WorldObserverWindow : public EditorGUIWindow
	{
	public:
		WorldObserverWindow() = default;
		~WorldObserverWindow() = default;


		// Inherited via EditorGUIWindow
		virtual DopeEngine::String get_window_name() const override;

		virtual void on_initialize() override;

		virtual void on_render() override;

		virtual void on_finalize() override;

		virtual void on_visible() override;

		virtual void on_invisible() override;

	};


}