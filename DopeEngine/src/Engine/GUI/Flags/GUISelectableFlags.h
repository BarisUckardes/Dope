#pragma once
#include <Engine/Core/Symbols.h>

namespace DopeEngine
{
    enum class DOPE_ENGINE_API GUISelectableFlags
    {
        None = 0,
        DontClosePopups = 1 << 0,   // Clicking this don't close parent popup window
        SpanAllColumns = 1 << 1,   // Selectable frame can span all columns (text will still fit in current column)
        AllowDoubleClick = 1 << 2,   // Generate press events on double clicks too
        Disabled = 1 << 3,   // Cannot be selected, display grayed out text
        AllowItemOverlap = 1 << 4    // (WIP) Hit testing to allow subsequent widgets to overlap this one
    };

    FORCEINLINE static GUISelectableFlags operator|(const GUISelectableFlags a, const GUISelectableFlags b)
    {
        return (GUISelectableFlags)((int)a | (int)b);
    }
}