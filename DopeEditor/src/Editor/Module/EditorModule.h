#pragma once
#include <Editor/Core/Symbols.h>
#include <Engine/Application/ApplicationModule.h>
#include <Engine/Structures/Array.h>

namespace DopeEngine
{
	class GraphicsCommandBuffer;
}
namespace DopeEditor
{
	class EditorSession;
	class EditorGUIModule;

	/// <summary>
	/// The module which responsible for all the Editor state
	/// </summary>
	class DOPE_EDITOR_API EditorModule : public DopeEngine::ApplicationModule
	{
	public:

		// Inherited via ApplicationModule
		virtual DopeEngine::String get_module_class_name() const override;
		virtual void initialize() override;
		virtual void update() override;
		virtual void finalize() override;
		virtual void on_receive_application_event(DopeEngine::ApplicationEvent* event) override;

	private:
		EditorSession* Session;
		DopeEngine::GraphicsCommandBuffer* GUICommandBuffer;
		DopeEngine::Array<EditorGUIModule*> GUIModules;
	};
}