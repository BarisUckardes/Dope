#include "GUILayoutCommands.h"
#include <IMGUI/imgui.h>

namespace DopeEngine
{
    void GUILayoutCommands::set_next_window_position(const Vector2f& position) const
    {
        ImGui::SetNextWindowPos({position.X,position.Y});
    }

    void GUILayoutCommands::set_next_window_size(const Vector2f& size) const
    {
        ImGui::SetNextWindowSize({ size.X,size.Y });
    }

    void GUILayoutCommands::set_next_window_viewport(const GUIID id) const
    {
        ImGui::SetNextWindowViewport(id);
    }

    void GUILayoutCommands::push_style(const GUIStyleVariableTypes flag, const Vector2f& value) const
    {
        ImGui::PushStyleVar((ImGuiStyleVar)flag, { value.X,value.Y });
    }

    void GUILayoutCommands::push_style(const GUIStyleVariableTypes flag, const float value) const
    {
        ImGui::PushStyleVar((ImGuiStyleVar)flag, value);
    }

    void GUILayoutCommands::push_color_style(const GUIStyleColorTypes type, const ColorRgbaFloat& color) const
    {
        ImGui::PushStyleColor((ImGuiCol)type, { color.Red,color.Green,color.Blue,color.Alpha });
    }

    void GUILayoutCommands::pop_color_style() const
    {
        ImGui::PopStyleColor();
    }

    void GUILayoutCommands::pop_style() const
    {
        ImGui::PopStyleVar();
    }

 
    GUIID GUILayoutCommands::get_main_viewport_id() const
    {
        return ImGui::GetMainViewport()->ID;
    }

    GUIID GUILayoutCommands::get_id(const String& name) const
    {
        return ImGui::GetID(*name);
    }

    void GUILayoutCommands::create_dockspace(const GUIID dockspaceID, const Vector2f& size, const GUIDockspaceFlags flags) const
    {
        ImGui::DockSpace(dockspaceID,{size.X,size.Y},(ImGuiDockNodeFlags)flags);
    }

    Vector2f GUILayoutCommands::get_main_viewport_position() const
    {
        return { ImGui::GetMainViewport()->Pos.x,ImGui::GetMainViewport()->Pos.y};
    }

    Vector2f GUILayoutCommands::get_main_viewport_size() const
    {
        return {ImGui::GetMainViewport()->Size.x,ImGui::GetMainViewport()->Size.y};
    }

}