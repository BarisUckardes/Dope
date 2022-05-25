#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
	/// <summary>
	/// Editable GUI variables
	/// </summary>
	enum class DOPE_ENGINE_API GUIStyleVariableTypes
	{
        Alpha,               // float     Alpha
        DisabledAlpha,       // float     DisabledAlpha
        WindowPadding,       // ImVec2    WindowPadding
        WindowRounding,      // float     WindowRounding
        WindowBorderSize,    // float     WindowBorderSize
        WindowMinSize,       // ImVec2    WindowMinSize
        WindowTitleAlign,    // ImVec2    WindowTitleAlign
        ChildRounding,       // float     ChildRounding
        ChildBorderSize,     // float     ChildBorderSize
        PopupRounding,       // float     PopupRounding
        PopupBorderSize,     // float     PopupBorderSize
        FramePadding,        // ImVec2    FramePadding
        FrameRounding,       // float     FrameRounding
        FrameBorderSize,     // float     FrameBorderSize
        ItemSpacing,         // ImVec2    ItemSpacing
        ItemInnerSpacing,    // ImVec2    ItemInnerSpacing
        IndentSpacing,       // float     IndentSpacing
        CellPadding,         // ImVec2    CellPadding
        ScrollbarSize,       // float     ScrollbarSize
        ScrollbarRounding,   // float     ScrollbarRounding
        GrabMinSize,         // float     GrabMinSize
        GrabRounding,        // float     GrabRounding
        TabRounding,         // float     TabRounding
        ButtonTextAlign,     // ImVec2    ButtonTextAlign
        SelectableTextAlign, // ImVec2    SelectableTextAlign
	};
}