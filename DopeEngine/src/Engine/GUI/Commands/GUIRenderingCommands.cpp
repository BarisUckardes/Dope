#include "GUIRenderingCommands.h"
#include <IMGUI/imgui.h>
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{
    bool GUIRenderingCommands::create_window(const String& title,bool* isOpen, const GUIWindowFlags flags) const
    {
        /*
        * Begin imgui window
        */
        return ImGui::Begin(*title, isOpen,(ImGuiWindowFlags)flags);
    }

    void GUIRenderingCommands::finalize_window() const
    {
        ImGui::End();
    }

    void GUIRenderingCommands::create_demo_window() const
    {
        ImGui::ShowDemoWindow();
    }

}