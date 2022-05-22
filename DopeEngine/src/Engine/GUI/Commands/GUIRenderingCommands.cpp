#include "GUIRenderingCommands.h"
#include <IMGUI/imgui.h>
#include <Engine/Core/ConsoleLog.h>

namespace DopeEngine
{
    void GUIRenderingCommands::create_window(const String& title,bool* isCollapsed,bool* isOpen) const
    {
        /*
        * Begin imgui window
        */
        const bool collapsed = ImGui::Begin(*title,isOpen);

        /*
        * Set collapsed state
        */
        *isCollapsed = collapsed;
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