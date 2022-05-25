#pragma once
#include <Engine/Math/Vector2f.h>
#include <Engine/Structures/String.h>
#include <Engine/GUI/GUICore.h>
#include <Engine/GUI/Flags/GUIDockspaceFlags.h>
#include <Engine/GUI/Flags/GUIStyleVariableTypes.h>
#include <Engine/GUI/Flags/GUIStyleColorTypes.h>
#include <Engine/Math/ColorRgbaFloat.h>
namespace DopeEngine
{
	/// <summary>
	/// Represents the gui layout commands of a GUIRenderer instance
	/// </summary>
	class DOPE_ENGINE_API GUILayoutCommands
	{
		friend class GUIRenderer;
	public:
		FORCEINLINE GUIID get_main_viewport_id() const;
		FORCEINLINE GUIID get_id(const String& name) const;

		FORCEINLINE Vector2f get_main_viewport_position() const;
		FORCEINLINE Vector2f get_main_viewport_size() const;

		FORCEINLINE Vector2f get_window_positon() const;
		FORCEINLINE Vector2f get_window_size() const;

		FORCEINLINE void create_dockspace(const GUIID dockspaceID, const Vector2f& size, const GUIDockspaceFlags flags = GUIDockspaceFlags::None) const;

		FORCEINLINE void set_next_window_position(const Vector2f& position) const;
		FORCEINLINE void set_next_window_size(const Vector2f& size) const;
		FORCEINLINE void set_next_window_viewport(const GUIID id) const;

		FORCEINLINE void push_variable_style(const GUIStyleVariableTypes flag,const Vector2f& value) const;
		FORCEINLINE void push_variable_style(const GUIStyleVariableTypes flag, const float value) const;
		FORCEINLINE void pop_variable_style() const;

		FORCEINLINE void push_color_style(const GUIStyleColorTypes type,const ColorRgbaFloat& color) const;
		FORCEINLINE void pop_color_style() const;
	private:
		GUILayoutCommands() = default;
		~GUILayoutCommands() = default;

	};


}