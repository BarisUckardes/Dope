#pragma once
#include <Engine/Core/Symbols.h>


namespace DopeEngine
{
	/// <summary>
	/// Supported editable color styles
	/// </summary>
	enum class DOPE_ENGINE_API GUIStyleColorTypes
	{
        Text,
        TextDisabled,
        WindowBg,              // Background of normal windows
        ChildBg,               // Background of child windows
        PopupBg,               // Background of popups, menus, tooltips windows
        Border,
        BorderShadow,
        FrameBg,               // Background of checkbox, radio button, plot, slider, text input
        FrameBgHovered,
        FrameBgActive,
        TitleBg,
        TitleBgActive,
        TitleBgCollapsed,
        MenuBarBg,
        ScrollbarBg,
        ScrollbarGrab,
        ScrollbarGrabHovered,
        ScrollbarGrabActive,
        CheckMark,
        SliderGrab,
        SliderGrabActive,
        Button,
        ButtonHovered,
        ButtonActive,
        Header,                // Header* colors are used for CollapsingHeader, TreeNode, Selectable, MenuItem
        HeaderHovered,
        HeaderActive,
        Separator,
        SeparatorHovered,
        SeparatorActive,
        ResizeGrip,
        ResizeGripHovered,
        ResizeGripActive,
        Tab,
        TabHovered,
        TabActive,
        TabUnfocused,
        TabUnfocusedActive,
        DockingPreview,        // Preview overlay color when about to docking something
        DockingEmptyBg,        // Background color for empty node (e.g. CentralNode with no window docked into it)
        PlotLines,
        PlotLinesHovered,
        PlotHistogram,
        PlotHistogramHovered,
        TableHeaderBg,         // Table header background
        TableBorderStrong,     // Table outer and header borders (prefer using Alpha=1.0 here)
        TableBorderLight,      // Table inner borders (prefer using Alpha=1.0 here)
        TableRowBg,            // Table row background (even rows)
        TableRowBgAlt,         // Table row background (odd rows)
        TextSelectedBg,
        DragDropTarget,
        NavHighlight,          // Gamepad/keyboard: current highlighted item
        NavWindowingHighlight, // Highlight window when using CTRL+TAB
        NavWindowingDimBg,     // Darken/colorize entire screen behind the CTRL+TAB window list, when active
        ModalWindowDimBg,      // Darken/colorize entire screen behind a modal window, when one is active
        COUNT
	};
}