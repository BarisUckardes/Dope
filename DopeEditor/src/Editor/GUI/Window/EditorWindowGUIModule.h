#pragma once
#include <Editor/GUI/EditorGUIModule.h>
#include <Engine/Structures/Array.h>
#include <Engine/Math/Vector2f.h>
namespace DopeEditor
{
	class EditorGUIWindow;
	class DOPE_EDITOR_API EditorWindowGUIModule : public EditorGUIModule
	{
	public:
		EditorWindowGUIModule() = default;
		~EditorWindowGUIModule() = default;


		template<typename TWindow,typename... TArgs>
		FORCEINLINE TWindow* create_window(TArgs... args);
		template<typename TWindow,typename... TArgs>
		FORCEINLINE TWindow* create_predefined_window(const DopeEngine::Vector2f& position, const DopeEngine::Vector2f& size, TArgs... args);

		FORCEINLINE bool delete_window(EditorGUIWindow* window);

		// Inherited via EditorGUIModule
		virtual void initialize() override;
		virtual void update() override;
		virtual void finalize() override;
	private:
		DopeEngine::Array<EditorGUIWindow*> ActiveWindows;
	};


	template<typename TWindow, typename ...TArgs>
	inline TWindow* EditorWindowGUIModule::create_window(TArgs ...args)
	{
		TWindow* window = new TWindow(args...);
		
		window->_set_owner_session(get_owner_session());
		window->_set_position({ 50,50 });
		window->_set_size({ 128,128 });

		window->on_initialize();

		ActiveWindows.add(window);

		return window;
	}

	template<typename TWindow, typename ...TArgs>
	inline TWindow* EditorWindowGUIModule::create_predefined_window(const DopeEngine::Vector2f& position, const DopeEngine::Vector2f& size, TArgs ...args)
	{
		TWindow* window = new TWindow(args...);

		window->_set_owner_session(get_owner_session());
		window->_set_position(position);
		window->_set_size(size);

		window->on_initialize();

		ActiveWindows.add(window);

		return window;
	}

}