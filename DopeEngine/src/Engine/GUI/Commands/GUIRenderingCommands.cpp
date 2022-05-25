#include "GUIRenderingCommands.h"
#include <IMGUI/imgui.h>
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{

    bool GUIRenderingCommands::start_window(const String& title,bool* isOpen, const GUIWindowFlags flags)
    {
        /*
        * Begin imgui window
        */
        return ImGui::Begin(*title, isOpen,(ImGuiWindowFlags)flags);
    }

    void GUIRenderingCommands::start_rendering_id(const GUIID renderingID)
    {
        ImGui::PushID(renderingID);
    }

    void GUIRenderingCommands::finalize_rendering_id()
    {
        ImGui::PopID();
    }

    void GUIRenderingCommands::finalize_window()
    {
        ImGui::End();
    }

    void GUIRenderingCommands::create_demo_window()
    {
        ImGui::ShowDemoWindow();
    }

    void GUIRenderingCommands::create_text_label(const String& text)
    {
        ImGui::Text(*text);
    }

    bool GUIRenderingCommands::create_collapsing_segment(const String& text, const GUITreeFlags flags)
    {
        return ImGui::CollapsingHeader(*text,flags);
    }

   

}