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
        return ImGui::CollapsingHeader(*text,(ImGuiTreeNodeFlags)flags);
    }

    bool GUIRenderingCommands::create_selectable(const String& text, const bool isSelected, const GUISelectableFlags flags, const Vector2f& size)
    {
        return ImGui::Selectable(*text, isSelected, (ImGuiSelectableFlags)flags, {size.X,size.Y});
    }

    bool GUIRenderingCommands::start_tree_node(const String& text, const GUITreeFlags flags)
    {
        return ImGui::TreeNode(*text);
    }

    void GUIRenderingCommands::finalize_tree_node()
    {
        ImGui::TreePop();
    }

    bool GUIRenderingCommands::create_menu_item(const String& text)
    {

        return ImGui::MenuItem(*text);
    }

    bool GUIRenderingCommands::start_menu(const String& text)
    {
        return ImGui::BeginMenu(*text);
    }

    void GUIRenderingCommands::finalize_menu()
    {
        ImGui::EndMenu();
    }

    bool GUIRenderingCommands::start_menu_bar()
    {
        return ImGui::BeginMenuBar();
    }

    void GUIRenderingCommands::finalize_menu_bar()
    {
        ImGui::EndMenuBar();
    }

    bool GUIRenderingCommands::start_main_menu_bar()
    {
        return ImGui::BeginMainMenuBar();
    }

    void GUIRenderingCommands::finalize_main_menu_bar()
    {
        ImGui::EndMainMenuBar();
    }



   

}