#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Math/Vector2f.h>
#include <Engine/Math/Vector3f.h>
#include <Engine/GUI/Flags/GUIWindowFlags.h>
#include <Engine/GUI/Flags/GUITreeFlags.h>
#include <Engine/GUI/Flags/GUISelectableFlags.h>
#include <Engine/GUI/GUICore.h>
namespace DopeEngine
{
	/// <summary>
	/// Represents the gui rendering commands of an GUIRenderer instance
	/// </summary>
	class DOPE_ENGINE_API GUIRenderingCommands
	{
		friend class GUIRenderer;
	public:
		FORCEINLINE void start_rendering_id(const GUIID renderingID);
		FORCEINLINE void finalize_rendering_id();

		FORCEINLINE bool start_window(const String& title,bool* isOpen,const GUIWindowFlags flags = GUIWindowFlags::None);
		FORCEINLINE void finalize_window();
		FORCEINLINE void create_demo_window();

		FORCEINLINE void create_text_label(const String& text);

		FORCEINLINE bool create_collapsing_segment(const String& text,const GUITreeFlags flags = GUITreeFlags::None);

		FORCEINLINE bool create_selectable(const String& text,const bool isSelected,const GUISelectableFlags flags = GUISelectableFlags::None,const Vector2f& size = {64,64});

		FORCEINLINE bool start_tree_node(const String& text,const GUITreeFlags flags = GUITreeFlags::None);
		FORCEINLINE void finalize_tree_node();

		FORCEINLINE bool create_menu_item(const String& text);
		FORCEINLINE bool start_menu(const String& text);
		FORCEINLINE void finalize_menu();
		FORCEINLINE bool start_menu_bar();
		FORCEINLINE void finalize_menu_bar();
		FORCEINLINE bool start_main_menu_bar();
		FORCEINLINE void finalize_main_menu_bar();
		
	private:
		GUIRenderingCommands() = default;
		~GUIRenderingCommands() = default;
	private:
	};


}