#pragma once
#include <Engine/Structures/String.h>
#include <Engine/Math/Vector2f.h>
#include <Engine/Math/Vector3f.h>
#include <Engine/GUI/Flags/GUIWindowFlags.h>
#include <Engine/GUI/Flags/GUITreeFlags.h>
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

	private:
		GUIRenderingCommands() = default;
		~GUIRenderingCommands() = default;
	private:
	};


}